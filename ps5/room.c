#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "room.h"
#include "item.h"
#include "container.h"

struct room* create_room(char *name, char *description){
  if(name == NULL || description == NULL || strlen(name) < 1 || strlen(description) < 1){
    return NULL;
  }
  struct room *room = calloc(1, sizeof(struct room));
  if(room == NULL){
    return NULL;
  }
  room->name = malloc(strlen(name) + 1);
  if(room->name == NULL){
    free(room);
    return NULL;
  }
  strcpy(room->name, name);
  room->description = malloc(strlen(description) + 1);
  if(room->description == NULL){
    free(room->name);
    free(room);
    return NULL;
  }
  strcpy(room->description, description);
  room->north = NULL;
  room->south = NULL;
  room->east = NULL;
  room->west = NULL;
  room->items = NULL;
  return room;
}

struct room* destroy_room(struct room* room){
  if(room != NULL){
    free(room->name);
    free(room->description);
    free(room);
  }
  return NULL;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
  if(north != NULL){
    room->north = north;
  }
  // if(room != north){
  //   room->north = north;
  // }

  if(east != NULL){
    room->east = east;
  }
  // if(room != east){
  //   room->east = east;
  // }

  if(west != NULL){
    room->west = west;
  }
  // if(room != west){
  //   room->west = west;
  // }

  if(south != NULL){
    room->south = south;
  }
  // if(room != south){
  //   room->south = south;
  // }
}

void show_room(const struct room* room){
  printf("Name: %s\n", room->name);
  printf("Description: %s\n", room->description);
  printf("East: %s\n", (const char *) room->east);
  printf("West: %s\n", (const char *) room->west);
  printf("North: %s\n", (const char *) room->north);
  printf("South: %s\n", (const char *) room->south);
}

void delete_item_from_room(struct room* room, struct item* item){
  if(item!=NULL){
    if(room!=NULL){
      room->items=remove_container(room->items,item);
    }
  }
}

void add_item_to_room(struct room* room, struct item* item){
  if(item!=NULL){
    if(room!=NULL){
      room->items=create_container(room->items,ITEM,item);
    }
  }
}

struct item* get_item_from_room(const struct room* room, const char* name){
  if(room == NULL || name == NULL){
    return NULL;
  }
  return get_from_container_by_name(room->items, name);
}



