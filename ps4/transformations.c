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
  new_image->header->width = height;
  new_image->header->height = width;
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
  new_image->header->width = height;
  new_image->header->height = width;
  return new_image;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
  if(image == NULL || image->header == NULL || image->data == NULL || factor <= 0){
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

  new_image->header->width = (int)(image->header->width * factor);
  new_image->header->height = (int)(image->header->height * factor);
  new_image->data = malloc(sizeof(struct pixel) * new_image->header->image_size);
  if(new_image->data == NULL){
    free(new_image->header);
    free(new_image);
    return NULL;
  }
  int width = image->header->width;
  int new_width = new_image->header->width;
  for(int a = 0; a < new_width; a++){
    for(int b = 0; b < new_width; b++){
      int original_i = (int)(a / factor);
      int original_j = (int)(b / factor);
      new_image->data[a * new_width + b] = image->data[original_i * width + original_j];
    }
  }
  return new_image;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
  if(image == NULL || image->header == NULL || image->data == NULL || start_y < 0 || start_x < 0 || height <= 0 || width <= 0 || start_y + height > image->header->height || start_x + width > image->header->width){
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

  new_image->header->width = width;
  new_image->header->height = height;
  new_image->data = malloc(sizeof(struct pixel) * height * width);
  if(new_image->data == NULL){
    free(new_image->header);
    free(new_image);
    return NULL;
  }
  int original_width = image->header->width;
  for(uint32_t a = 0; a < height; a++){
    for(uint32_t b = 0; b < width; b++){
      new_image->data[a * width + b] = image->data[(start_y + a) * original_width + (start_x + b)];
    }
  }
  return new_image;
}

// struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
//   if(image == NULL || image->header == NULL || image->data == NULL || colors_to_keep == NULL){
//     return NULL;
//   }
//   struct bmp_image* new_image = malloc(sizeof(struct bmp_image));
//   if(new_image == NULL){
//     return NULL;
//   }
//   new_image->header = malloc(sizeof(struct bmp_header));
//   if(new_image->header == NULL){
//     free(new_image);
//     return NULL;
//   }
//   memcpy(new_image->header, image->header, sizeof(struct bmp_header));

//   new_image->data = malloc(sizeof(struct pixel) * image->header->image_size);
//   if(new_image->data == NULL){
//     free(new_image->header);
//     free(new_image);
//     return NULL;
//   }
//   int width = image->header->width;
//   int height = image->header->height;
//   int new_size = 0;
//   for(int a = 0; a < height; a++){
//     for(int b = 0; b < width; b++){
//       struct pixel current_pixel = image->data[a * width + b];
//       char* color_ptr = strchr(colors_to_keep, current_pixel.color);
//       if(color_ptr != NULL){
//         new_image->data[new_size++] = current_pixel;
//       }
//     }
//   }
//   new_image->header->image_size = new_size;
//   new_image->header->width = new_size / height;
//   new_image->header->height = height;
//   return new_image;
// }

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    image = malloc(sizeof(*image));
    return NULL;
}