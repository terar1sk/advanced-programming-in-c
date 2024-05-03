#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "room.h"


struct room* get_room(struct container* world, char* name);

struct container* create_world(){
  struct room * room_one = create_room("Main", "Main room");
  struct container * container = create_container(NULL, ROOM, room_one);
  return container;
}

struct container* add_room_to_world(struct container* world, struct room* room){
  if(room != NULL){
    if(world != NULL){
      if(get_room(world, room->name) != NULL){
        return NULL;
      }
    }
    return create_container(world, ROOM, room);
  }
  else{
    return NULL;
  }
}

struct container* destroy_world(struct container* world){
  if(world != NULL){
    struct container * first = world;
    while(world != NULL && world->room != NULL){
      destroy_room(world->room);
      world = world->next;
    }
    destroy_containers(first);
  }
  return NULL;
}

struct room* get_room(struct container* world, char* name){
  if(world != NULL && name != NULL){
    return get_from_container_by_name(world, name);
  }
  else{
    return NULL;
  }
}