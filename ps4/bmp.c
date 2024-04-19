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
  struct bmp_header *header;
  unsigned int headersize;
  int width;
  int height;
  unsigned short planes;
  unsigned int compression;
  unsigned int size_image;
  int x_ppm;
  int y_ppm;
  unsigned int c_u;
  unsigned int c_i;
  headersize = (unsigned int) R4(stream);
  width = (int) R4(stream);
  height = (int) R4(stream);
  planes = (unsigned short) R2(stream);
  compression = (unsigned int) R4(stream);
  size_image = (unsigned int) R4(stream);
  x_ppm = (int) R4(stream);
  y_ppm = (int) R4(stream);
  c_u = (unsigned int) R4(stream);
  c_i = (unsigned int) R4(stream);

  char file_type[3] = {'\0', '\0', '\0'};
  unsigned int fs;
  unsigned short booked;
  unsigned short armored;
  unsigned long bs;
  fread(&file_type, 1, 2, stream);
  fs = (unsigned int) R4(stream);
  fread(&booked, 2, 1, stream);
  fread(&armored, 2, 1, stream);
  bs = (unsigned long) R4(stream);
  header = (struct bmp_header*) malloc(sizeof(struct bmp_header));
  header->size = fs;
  header->reserved1 = booked;
  header->reserved2 = armored;
  header->offset = bs;
  header->size = headersize;
  header->width = width;
  header->height = height;
  header->planes = planes;
  header->compression = compression;
  header->image_size = size_image;
  header->x_ppm = x_ppm;
  header->y_ppm = y_ppm;
  header->num_colors = c_u;
  header->important_colors = c_i;
  return header;
}

struct bmp_image* read_bmp(FILE* stream){
  struct bmp_header *header = read_bmp_header(stream);
  struct pixel *pixel = read_data(stream, header);
  struct bmp_image *image;
  image = malloc(sizeof(struct bmp_image*));
  if(header == NULL){
    fprintf(stdout,"Error: Corrupted BMP file.\n");
    return NULL;
  }
  else if(header->type != 0x424D){
    fprintf(stdout,"Error: This is not a BMP file.\n");
    return NULL;
  }
  image->data = malloc(sizeof(*image->data) * image->header->image_size);
  return image;
}

bool write_bmp(FILE* stream, const struct bmp_image* image){
  if(stream == NULL || image == NULL){
    return false;
  }
  fwrite(image, sizeof(image->header->size),1,stream);
  fwrite(image->data, sizeof(image->data), 1,stream);
  return true;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){
  if(stream == NULL){
    return NULL;
  }
  if(header == NULL){
    return NULL;
  }
  struct pixel *pixel = malloc(header->height * header->width);
  return pixel;
}

void free_bmp_image(struct bmp_image* image){
  if(image){
    free(image->data);
    free(image);
  }
}

