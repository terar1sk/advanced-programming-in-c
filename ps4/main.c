#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "transformations.h"

struct bmp_image* read_bmp(FILE* stream);
struct pixel* read_data(FILE* stream, const struct bmp_header* header);
bool write_bmp(FILE* stream, const struct bmp_image* image);
void free_bmp_image(struct bmp_image* image);
struct bmp_image* flip_horizontally(const struct bmp_image* image);
struct bmp_image* flip_vertically(const struct bmp_image* image);
struct bmp_image* rotate_right(const struct bmp_image* image);
struct bmp_image* rotate_left(const struct bmp_image* image);
struct bmp_image* scale(const struct bmp_image* image, float factor);
struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width);
struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep);

int main(){
  const char *a = "M:/Computer/Home/prog-9313/ps4/assets/denzil.bmp";
  FILE *stream = fopen(a, "rb+");
  struct bmp_image *image = read_bmp(stream);
  if(image == NULL){
    fclose(stream);
    return 1;
  }
  image->data = read_data(stream, image->header);
  if(image->data == NULL){
    free_bmp_image(image);
    fclose(stream);
    return 1;
  }
  if(!write_bmp(stream, image)){
    free_bmp_image(image);
    fclose(stream);
    return 1;
  }
  printf("data size:%lu\n", sizeof(*image));
  printf("Done\n");

  struct bmp_image *fh = flip_horizontally(image);
  struct bmp_image *fv = flip_vertically(image);
  struct bmp_image *rr = rotate_right(image);
  struct bmp_image *rl = rotate_left(image);
  float f;
  scanf("%f\n", &f);
  struct bmp_image *scaled = scale(image, f);
  int x, y;
  scanf("%d, %d\n", &y, &x);
  struct bmp_image *cropped = crop(image, y, x, image->header->height, image->header->width);
  char ctk[4];
  scanf("%s\n", ctk);
  struct bmp_image *extracted = extract(image, ctk);

  free_bmp_image(fh);
  free_bmp_image(fv);
  free_bmp_image(rr);
  free_bmp_image(rl);
  free_bmp_image(scaled);
  free_bmp_image(cropped);
  free_bmp_image(extracted);
  free_bmp_image(image);
  fclose(stream);
  return 0;
}
