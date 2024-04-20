#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp.h"

// unsigned short R2(FILE *fp){
//   unsigned short reply = 0;
//   unsigned char cb[2];
//     int a;
//     fread(cb, 1, 2, fp);
//     for(a = 1; a >= 0; a--){
//         reply = (reply << 8) | (unsigned short) cb[a];
//     }
//   return reply;
// }

// unsigned int R4(FILE *fp){
//   unsigned int reply = 0;
//   unsigned char cb[4];
//     int a;
//     fread(cb, 1, 4, fp);
//     for(a = 3; a >= 0; a--){
//       reply = (reply << 8) | (unsigned int) cb[a];
//     }
//   return reply;
// }

struct bmp_header* read_bmp_header(FILE* stream){
  if(stream == NULL){
    return NULL;
  }
  struct bmp_header *header = malloc(sizeof(struct bmp_header));
  if(header == NULL){
    return NULL;
  }
  if(fread(header, sizeof(struct bmp_header), 1, stream) != 1){
        free(header);
        return NULL;
    }
    return header;
}

struct bmp_image* read_bmp(FILE* stream){
  if(stream == NULL){
    return NULL;
  }
  struct bmp_header* header = read_bmp_header(stream);
  if(header == NULL){
    return NULL;
  }
  if(header->type != 0x4D42){
    free(header);
    return NULL;
  }
  struct bmp_image* image = malloc(sizeof(struct bmp_image));
  if(image == NULL){
    free(header);
    return NULL;
  }
  image->header = header;
  image->data = read_data(stream, header);
  if(image->data == NULL){
    free(header);
    free(image);
    return NULL;
  }
  return image;
}

bool write_bmp(FILE* stream, const struct bmp_image* image){
  if(stream == NULL || image == NULL){
    return false;
  }
  if(fwrite(image->header, sizeof(struct bmp_header), 1, stream) != 1){
    return false;
  }
  if(fwrite(image->data, sizeof(struct pixel), image->header->image_size, stream) != image->header->image_size){
    return false;
  }
  return true;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){
  if(stream == NULL || header == NULL){
    return NULL;
  }
  size_t image_size = header->image_size;
  struct pixel* pixels = malloc(image_size);
  if(pixels == NULL){
    return NULL;
  }
  if(fread(pixels, sizeof(struct pixel), image_size, stream) != image_size){
    free(pixels);
    return NULL;
  }
  return pixels;
}

void free_bmp_image(struct bmp_image* image){
  if(image){
    free(image->data);
    free(image->header);
    free(image);
  }
}
