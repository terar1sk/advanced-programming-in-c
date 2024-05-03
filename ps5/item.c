#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h" 


struct item* create_item(char* name, char* description, unsigned int properties){
  if(name == NULL || description == NULL || strlen(name) < 1 || strlen(description) < 1){
    return NULL;
  }
  else{
    struct item *new_item = calloc(1, sizeof(struct item));
    char *new_name = malloc(strlen(name) + 1);
    char *new_description = malloc(strlen(description) + 1);
    strcpy(new_name, name);
    strcpy(new_description, description);
    new_item->name = new_name;
    new_item->description = new_description;
    new_item->properties = properties;
    return new_item;
  }
}

struct item* destroy_item(struct item* item){
  if(item!=NULL){
    free(item);
	item=NULL;
  }
  return NULL;
}