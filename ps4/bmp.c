#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp.h"

unsigned short R2(FILE *fp){
  unsigned short reply = 0;
  unsigned char cb[2];
  fread(cb, 1, 2, fp);
  for(int a = 1; a >= 0; a--){
    reply = (reply << 8) | (unsigned short)cb[a];
  }
  return reply;
}

unsigned int R4(FILE *fp){
  unsigned int reply = 0;
  unsigned char cb[4];
  fread(cb, 1, 4, fp);
  for(int a = 3; a >= 0; a--){
    reply = (reply << 8) | (unsigned int)cb[a];
  }
  return reply;
}

struct bmp_header* read_bmp_header(FILE* stream){
  if(stream == NULL){
    return NULL;
  }
  struct bmp_header* header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
  if(header == NULL){
    return NULL;
  }
  header->type = R2(stream);
  header->size = R4(stream);
  header->reserved1 = R2(stream);
  header->reserved2 = R2(stream);
  header->offset = R4(stream);
  header->dib_size = R4(stream);
  header->width = R4(stream);
  header->height = R4(stream);
  header->planes = R2(stream);
  header->bpp = R2(stream);
  header->compression = R4(stream);
  header->image_size = R4(stream);
  header->x_ppm = R4(stream);
  header->y_ppm = R4(stream);
  header->num_colors = R4(stream);
  header->important_colors = R4(stream);
  return header;
}

struct bmp_image* read_bmp(FILE* stream){
  if(stream == NULL){
    return NULL;
  }
  struct bmp_header* header = read_bmp_header(stream);
  if(header == NULL){
    fprintf(stderr, "Error: This is not a BMP file.\n");
    return NULL;
  }
  struct bmp_image* image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
  if(image == NULL){
    free(header);
    return NULL;
  }
  image->header = header;
  char* imageData = (char*)read_data(stream, header);
  if(imageData == NULL){
    fprintf(stderr, "Error: Corrupted BMP file.\n");
    free(header);
    free(image);
    return NULL;
  }
  image->data = (struct pixel *)imageData;
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
  fseek(stream, header->offset, SEEK_SET);
  size_t image_size = header->size - header->offset;
  struct pixel* pixels = (struct pixel*)malloc(image_size);
  if(pixels == NULL){
    return NULL;
  }
  fread(pixels, sizeof(struct pixel), image_size / sizeof(struct pixel), stream);
  return pixels;
}

void free_bmp_image(struct bmp_image* image){
  if(image){
    free(image->data);
    free(image->header);
    free(image);
  }
}
