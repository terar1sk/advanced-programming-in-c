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
  if(write_bmp(stream,image)){
    free_bmp_image(image);
  }
  printf("data size:%lu\n", sizeof(*image));
  printf("Done\n");

  struct bmp_image *fh;
  if(image != NULL){
    fh = flip_horizontally(image);
  }
  else{
    return 0;
  }
  struct bmp_image *fv = flip_vertically(image);
  struct bmp_image *rr = rotate_right(image);
  struct bmp_image *rl = rotate_left(image);
  float f;
  scanf("%f\n", &f);
  struct bmp_image *scaled = scale(image,f);
  int x,y;
  scanf("%d, %d\n", &y,&x);
  struct bmp_image *trimmed = crop(image, y,x,image->header->height,image->header->width);
  char ck;
  scanf("%s\n", &ck);
  struct bmp_image *produced = extract(image,&ck);
  free(fh);
  free(fv);
  free(rr);
  free(rl);
  free(scaled);
  free(trimmed);
  free(produced);

  free_bmp_image(image);
  return 0;
}

