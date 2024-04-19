#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "transformations.h"

struct pixel* read_data(FILE* stream, const struct bmp_header* header);

int main(){
  const char *a = "M:/Computer/Home/prog-9313/ps4/assets/denzil.bmp";
  FILE *stream = fopen(a,"rb+");
  struct bmp_image *image = read_bmp(stream);
  if(image == NULL){
    return 1;
  }
  image->data = read_data(stream, image->header);
  if(image->data == NULL){
    free_bmp_image(image);
    return 1;
  }
  if(write_bmp(stream,image)){
    free_bmp_image(image);
  }
  else{
    free_bmp_image(image);
    return 1;
  }
  fclose(stream);
  return 0;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){
  if(stream == NULL || header == NULL){
    return NULL;
  }
  struct pixel *pixel = malloc(sizeof(struct pixel) * header->height * header->width);
  if(pixel == NULL){
    return NULL;
  }
  fseek(stream, header->size, SEEK_SET);
  fread(pixel, sizeof(struct pixel), header->image_size, stream);
  return pixel;
}
