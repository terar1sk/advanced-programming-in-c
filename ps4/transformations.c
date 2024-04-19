#include <stdlib.h>
#include <stdio.h>
#include "transformations.h"
#include "bmp.h"
#include <string.h>

struct bmp_image* flip_horizontally(const struct bmp_image* image){
  image = malloc(sizeof(*image));
  return NULL;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
  image = malloc(sizeof(*image));
  return NULL;
}

struct bmp_image* rotate_right(const struct bmp_image* image){
  image = malloc(sizeof(*image));
  return NULL;
}

struct bmp_image* rotate_left(const struct bmp_image* image){
  image = malloc(sizeof(*image));
  return NULL;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
  image = malloc(sizeof(*image));
  return NULL;
}

struct bmp_image* crop(const struct bmp_image* image, const int start_y, const int start_x, const int height, const int width){
  image = malloc(sizeof(*image));
  return NULL;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
  image = malloc(sizeof(*image));
  return NULL;
}