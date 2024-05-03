#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "backpack.h"
#include "container.h"


struct backpack* create_backpack(const int capacity){
  struct backpack * new_back_pack = calloc(1, sizeof(struct backpack));
  new_back_pack->capacity = capacity;
  return new_back_pack;
}

struct backpack* destroy_backpack(struct backpack* backpack){
  if(backpack != NULL){
    free(backpack);
  }
  return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item){
	if(backpack==NULL){
		return false;
	}
	if(item==NULL || backpack->capacity==backpack->size){
		return false;
	}
	backpack->items=create_container(backpack->items,ITEM,item);
	backpack->size++;
	return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
	backpack->items=remove_container(backpack->items,item);
	backpack->size--;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
  if(backpack != NULL && backpack->items != NULL && name != NULL && strlen(name) > 0){
    return get_from_container_by_name(backpack->items, name);
  }
  else{
    return NULL;
  }
}
