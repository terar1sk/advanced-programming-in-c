#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp.h"

unsigned short R2(FILE *fp){
  unsigned short reply = 0;
  unsigned char cb[2];
    int a;
    fread(cb, 1, 2, fp);
    for(a = 1; a >= 0; a--){
        reply = (reply << 8) | (unsigned short) cb[a];
    }
  return reply;
}

unsigned int R4(FILE *fp){
  unsigned int reply = 0;
  unsigned char cb[4];
    int a;
    fread(cb, 1, 4, fp);
    for(a = 3; a >= 0; a--){
      reply = (reply << 8) | (unsigned int) cb[a];
    }
  return reply;
}

struct bmp_header* read_bmp_header(FILE* stream){
  if(stream == NULL){
    return NULL;
  }
  struct bmp_header *header = malloc(sizeof(struct bmp_header));
  if(header == NULL){
    return NULL;
  }
  header->size = (unsigned int) R4(stream);
  header->width = (int) R4(stream);
  header->height = (int) R4(stream);
  header->planes = (unsigned short) R2(stream);
  header->compression = (unsigned int) R4(stream);
  header->image_size = (unsigned int) R4(stream);
  header->x_ppm = (int) R4(stream);
  header->y_ppm = (int) R4(stream);
  header->num_colors = (unsigned int) R4(stream);
  header->important_colors = (unsigned int) R4(stream);
  return header;
}

struct bmp_image* read_bmp(FILE* stream){
  struct bmp_header *header = read_bmp_header(stream);
  if(header == NULL){
    fprintf(stdout,"Error: Corrupted BMP file.\n");
    return NULL;
  }
  else if(header->type != 0x424D){
    fprintf(stdout,"Error: This is not a BMP file.\n");
    free(header);
    return NULL;
  }
  struct bmp_image *image = malloc(sizeof(struct bmp_image));
  if(image == NULL){
    free(header);
    return NULL;
  }
  image->header = header;
  image->data = malloc(sizeof(struct pixel) * header->image_size);
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
  fwrite(image->header, sizeof(struct bmp_header), 1, stream);
  fwrite(image->data, sizeof(struct pixel), image->header->image_size, stream);
  return true;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){
  if(stream == NULL || header == NULL){
    return NULL;
  }
  struct pixel *pixel = malloc(sizeof(struct pixel) * header->height * header->width);
  if(pixel == NULL){
    return NULL;
  }
  return pixel;
}

void free_bmp_image(struct bmp_image* image){
  if(image){
    free(image->data);
    free(image->header);
    free(image);
  }
}
