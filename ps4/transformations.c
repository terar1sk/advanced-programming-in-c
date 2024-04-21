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
  struct bmp_image* rotated_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
  if(rotated_image == NULL){
    return NULL;
  }
  rotated_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
  if(rotated_image->header == NULL){
    free(rotated_image);
    return NULL;
  }
  *(rotated_image->header) = *(image->header);
  uint32_t temp = rotated_image->header->width;
  rotated_image->header->width = rotated_image->header->height;
  rotated_image->header->height = temp;
  size_t image_size = rotated_image->header->size - rotated_image->header->offset;
  rotated_image->data = (struct pixel*)malloc(image_size);
  if(rotated_image->data == NULL){
    free(rotated_image->header);
    free(rotated_image); 
    return NULL;
  }
  for(uint32_t row = 0; row < image->header->height; row++){
    for(uint32_t col = 0; col < image->header->width; col++){
      uint32_t new_row = col;
      uint32_t new_col = image->header->height - row - 1;
      rotated_image->data[new_row * rotated_image->header->width + new_col] = image->data[row * image->header->width + col];
    }
  }
  return rotated_image;
}

struct bmp_image* rotate_left(const struct bmp_image* image){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  struct bmp_image* rotated_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
  if(rotated_image == NULL){
    return NULL;
  }
  rotated_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
  if(rotated_image->header == NULL){
    free(rotated_image);
    return NULL;
  }
  *(rotated_image->header) = *(image->header);
  uint32_t temp = rotated_image->header->width;
  rotated_image->header->width = rotated_image->header->height;
  rotated_image->header->height = temp;
  size_t image_size = rotated_image->header->size - rotated_image->header->offset;
  rotated_image->data = (struct pixel*)malloc(image_size);
  if(rotated_image->data == NULL){
    free(rotated_image->header);
    free(rotated_image);
    return NULL;
  }
  for(uint32_t row = 0; row < image->header->height; row++){
    for(uint32_t col = 0; col < image->header->width; col++){
      uint32_t new_row = image->header->width - col - 1;
      uint32_t new_col = row;
      rotated_image->data[new_row * rotated_image->header->width + new_col] = image->data[row * image->header->width + col];
    }
  }
  return rotated_image;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
  if(image == NULL || factor <= 0.0f){
    return NULL;
  }
  uint32_t new_width = (uint32_t)(image->header->width * factor);
  uint32_t new_height = (uint32_t)(image->header->height * factor);
  struct bmp_image* scaled_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
  if(scaled_image == NULL){
    return NULL;
  }
  scaled_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
  if(scaled_image->header == NULL){
    free(scaled_image);
    return NULL;
  }
  *(scaled_image->header) = *(image->header);
  scaled_image->header->width = new_width;
  scaled_image->header->height = new_height;
  uint32_t new_image_size = new_width * new_height;
  scaled_image->data = (struct pixel*)malloc(new_image_size * sizeof(struct pixel));
  if(scaled_image->data == NULL){
    free(scaled_image->header);
    free(scaled_image);
    return NULL;
  }
  return scaled_image;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  if(start_y >= image->header->height || start_x >= image->header->width || height == 0 || width == 0 || start_y + height > image->header->height || start_x + width > image->header->width){
    return NULL;
  }
  struct bmp_image* cropped_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
  if(cropped_image == NULL){
    return NULL;
  }
  cropped_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
  if(cropped_image->header == NULL){
    free(cropped_image);
    return NULL;
  }
  *(cropped_image->header) = *(image->header); 
  cropped_image->header->height = height;
  cropped_image->header->width = width;
  cropped_image->header->image_size = height * width * sizeof(struct pixel);
  cropped_image->header->size = cropped_image->header->offset + cropped_image->header->image_size;
  cropped_image->data = (struct pixel*)malloc(cropped_image->header->image_size);
  if(cropped_image->data == NULL){
    free(cropped_image->header);
    free(cropped_image);
    return NULL;
  }
  for(uint32_t y = 0; y < height; y++){
    for(uint32_t x = 0; x < width; x++){
      cropped_image->data[y * width + x] = image->data[(start_y + y) * image->header->width + (start_x + x)];
    }
  }
  return cropped_image;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
  if(image == NULL || image->header == NULL || image->data == NULL){
    return NULL;
  }
  if(colors_to_keep == NULL || strlen(colors_to_keep) == 0 || strlen(colors_to_keep) > 3){
    return NULL;
  }
  struct bmp_image* extracted_image = (struct bmp_image*)malloc(sizeof(struct bmp_image));
  if(extracted_image == NULL){
    return NULL;
  }
  extracted_image->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
  if(extracted_image->header == NULL){
    free(extracted_image);
    return NULL;
  }
  *(extracted_image->header) = *(image->header);
  extracted_image->header->image_size = image->header->width * image->header->height * sizeof(struct pixel);
  extracted_image->header->size = extracted_image->header->offset + extracted_image->header->image_size;
  extracted_image->data = (struct pixel*)malloc(extracted_image->header->image_size);
  if(extracted_image->data == NULL){
    free(extracted_image->header);
    free(extracted_image);
    return NULL;
  }
  for(uint32_t a = 0; a < image->header->height; a++){
    for(uint32_t b = 0; b < image->header->width; b++){
      uint32_t index = a * image->header->width + b;
      if(strchr(colors_to_keep, 'b') != NULL){
        extracted_image->data[index].blue = image->data[index].blue;
      }
      if(strchr(colors_to_keep, 'g') != NULL){
        extracted_image->data[index].green = image->data[index].green;
      }
      if(strchr(colors_to_keep, 'r') != NULL){
        extracted_image->data[index].red = image->data[index].red;
      }
    }
  }
  return extracted_image;
}
