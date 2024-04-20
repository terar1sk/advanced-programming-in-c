#include <stdlib.h>
#include <stdio.h>
#include "transformations.h"
#include "bmp.h"
#include <string.h>

struct bmp_image* flip_horizontally(const struct bmp_image* image){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
  if(new_image == NULL){
    return NULL;
  }
  new_image->header = malloc(sizeof(struct bmp_header));
  if(new_image->header == NULL){
    free(new_image);
    return NULL;
  }
  memcpy(new_image->header, image->header, sizeof(struct bmp_header));

  new_image->data = malloc(sizeof(struct pixel) * image->header->image_size);
  if(new_image->data == NULL){
    free(new_image->header);
    free(new_image);
    return NULL;
  }
  int width = image->header->width;
  int height = image->header->height;
  for(int a = 0; a < height; a++){
    for(int b = 0; b < width; b++){
      new_image->data[a * width + b] = image->data[a * width + (width - b - 1)];
    }
  }
  return new_image;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
    if(new_image == NULL){
      return NULL;
    }
    new_image->header = malloc(sizeof(struct bmp_header));
    if(new_image->header == NULL){
      free(new_image);
      return NULL;
    }
    memcpy(new_image->header, image->header, sizeof(struct bmp_header));

    new_image->data = malloc(sizeof(struct pixel) * image->header->image_size);
    if(new_image->data == NULL){
      free(new_image->header);
      free(new_image);
      return NULL;
    }
    int width = image->header->width;
    int height = image->header->height;
    for(int a = 0; a < height; a++){
      for(int b = 0; b < width; b++){
        new_image->data[a * width + b] = image->data[(height - a - 1) * width + b];
      }
    }
  return new_image;
}

struct bmp_image* rotate_right(const struct bmp_image* image){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
    if(new_image == NULL){
      return NULL;
    }
    new_image->header = malloc(sizeof(struct bmp_header));
    if(new_image->header == NULL){
      free(new_image);
      return NULL;
    }
    memcpy(new_image->header, image->header, sizeof(struct bmp_header));

    new_image->header->width = image->header->height;
    new_image->header->height = image->header->width;
    new_image->data = malloc(sizeof(struct pixel) * image->header->image_size);
    if(new_image->data == NULL){
      free(new_image->header); 
      free(new_image);
      return NULL;
    }
    int width = image->header->width;
    int height = image->header->height;
    for(int a = 0; a < height; a++){
      for(int b = 0; b < width; b++){
        new_image->data[b * height + (height - a - 1)] = image->data[a * width + b];
      }
    }
    new_image->header->image_size = sizeof(struct pixel) * width * height;
  return new_image;
}

struct bmp_image* rotate_left(const struct bmp_image* image){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
  if(new_image == NULL){
    return NULL;
  }
  new_image->header = malloc(sizeof(struct bmp_header));
  if(new_image->header == NULL){
    free(new_image);
    return NULL;
  }
  memcpy(new_image->header, image->header, sizeof(struct bmp_header));
  new_image->header->width = image->header->height;
  new_image->header->height = image->header->width;

  new_image->data = malloc(sizeof(struct pixel) * image->header->image_size);
  if(new_image->data == NULL){
    free(new_image->header); 
    free(new_image);
    return NULL;
  }
  int width = image->header->width;
  int height = image->header->height;
  for(int a = 0; a < height; a++){
    for(int b = 0; b < width; b++){
      new_image->data[(width - b - 1) * height + a] = image->data[a * width + b];
    }
  }
  new_image->header->image_size = sizeof(struct pixel) * width * height;
  return new_image;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
  if(image == NULL || image->header == NULL || image->data == NULL || factor <= 0){
    return NULL;
  }
  int new_width = (int)(image->header->width * factor);
  int new_height = (int)(image->header->height * factor);
  struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
  if(new_image == NULL){
    return NULL;
  }
  new_image->header = malloc(sizeof(struct bmp_header));
  if(new_image->header == NULL){
    free(new_image);
    return NULL;
  }
  memcpy(new_image->header, image->header, sizeof(struct bmp_header));

  new_image->header->width = new_width;
  new_image->header->height = new_height;
  new_image->header->image_size = sizeof(struct pixel) * new_width * new_height;
  new_image->data = malloc(new_image->header->image_size);
  if(new_image->data == NULL){
    free(new_image->header);
    free(new_image);
    return NULL;
  }
  int original_width = image->header->width;
  for(int a = 0; a < new_height; a++){
    for(int b = 0; b < new_width; b++){
      int original_x = (int)(b / factor);
      int original_y = (int)(a / factor);
      new_image->data[a * new_width + b] = image->data[original_y * original_width + original_x];
    }
  }
  return new_image;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  if(start_x >= image->header->width || start_y >= image->header->height || width == 0 || height == 0){
    return NULL;
  }
  struct bmp_image* cropped_image = malloc(sizeof(struct bmp_image));
  if(cropped_image == NULL){
    return NULL;
  }
  cropped_image->header = malloc(sizeof(struct bmp_header));
  if(cropped_image->header == NULL){
    free(cropped_image);
    return NULL;
  }
  memcpy(cropped_image->header, image->header, sizeof(struct bmp_header));

  cropped_image->header->width = width;
  cropped_image->header->height = height;
  cropped_image->header->image_size = sizeof(struct pixel) * width * height;
  cropped_image->data = malloc(sizeof(struct pixel) * width * height);
  if(cropped_image->data == NULL){
  free(cropped_image->header);
    free(cropped_image);
    return NULL;
  }
  for(uint32_t a = 0; a < height; a++){
    for(uint32_t b = 0; b < width; b++){
      cropped_image->data[a * width + b] = image->data[(start_y + a) * image->header->width + start_x + b];
    }
  }
  return cropped_image;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
  if(image == NULL || image->header == NULL || image->data == NULL || colors_to_keep == NULL){
    return NULL;
  }
  int width = image->header->width;
  int height = image->header->height;
  int original_size = width * height;
  struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
  if(new_image == NULL){
    return NULL;
  }
  new_image->header = malloc(sizeof(struct bmp_header));
  if(new_image->header == NULL){
    free(new_image);
    return NULL;
  }
  memcpy(new_image->header, image->header, sizeof(struct bmp_header));

  int new_size = 0;
  for(int a = 0; a < original_size; a++){
    if(strchr(colors_to_keep, 'b') != NULL){
      new_size++;
    }
    if(strchr(colors_to_keep, 'g') != NULL){
      new_size++;
    }
    if(strchr(colors_to_keep, 'r') != NULL){
      new_size++;
    }
  }
  new_image->data = malloc(sizeof(struct pixel) * new_size);
  if(new_image->data == NULL){
    free(new_image->header);
    free(new_image);
    return NULL;
  }
  int new_index = 0;
  for(int a = 0; a < original_size; a++){
    struct pixel current_pixel = image->data[a];
    if(strchr(colors_to_keep, 'b') != NULL){
      new_image->data[new_index].blue = current_pixel.blue;
      new_index++;
    }
    if(strchr(colors_to_keep, 'g') != NULL){
      new_image->data[new_index].green = current_pixel.green;
      new_index++;
    }
    if(strchr(colors_to_keep, 'r') != NULL){
      new_image->data[new_index].red = current_pixel.red;
      new_index++;
    }
  }
  new_image->header->image_size = new_size;
  new_image->header->width = new_size / height;
  return new_image;
}
