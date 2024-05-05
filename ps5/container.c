#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "command.h"
#include "item.h"
#include "container.h"

char* strdup(const char* str){
	size_t len = strlen(str) + 1;
  char* copy = malloc(len);
  if(copy == NULL){
    return NULL;
  }
  memcpy(copy, str, len);
  return copy;
}

struct container* create_container(struct container* first, enum container_type type, void* entry){
	if(entry == NULL){
  	return NULL;
  }
  struct container* new_container = calloc(1, sizeof(struct container));
  if(new_container == NULL){
    exit(EXIT_FAILURE);
  }
  new_container->type = type;
  switch(type){
  	case ROOM:
    	new_container->room = entry;
      break;
    case ITEM:
      new_container->item = entry;
      break;
    case COMMAND:
      new_container->command = entry;
      break;
    case TEXT:
      new_container->text = strdup((char*)entry);
      if(new_container->text == NULL){
        exit(EXIT_FAILURE);
      }
      break;
  }
	if(first == NULL){
    return new_container;
  }
	struct container* temp = first;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new_container;
  return first;
}

struct container* destroy_containers(struct container* first){
	if(first == NULL){
		return NULL;
  }
  struct container* current = first;
  struct container* next;
  while(current != NULL){
    next = current->next;
		switch(current->type){
    	case ROOM:
      	destroy_room(current->room);
      	break;
    	case ITEM:
        destroy_item(current->item);
        break;
      case COMMAND:
        destroy_command(current->command);
        break;
      case TEXT:
        free(current->text);
        break;
    }
    free(current);
    current = next;
  }
  return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name){
	if(first == NULL || name == NULL || *name == '\0'){
		return NULL;
	}
	struct container* temp = first;
	while(temp != NULL){
		if(temp->type == ROOM && temp->room != NULL && strcmp(temp->room->name, name) == 0){
      return temp->room;
    }
    if(temp->type == ITEM && temp->item != NULL && strcmp(temp->item->name, name) == 0){
      return temp->item;
    }
    if(temp->type == COMMAND && temp->command != NULL && strcmp(temp->command->name, name) == 0){
      return temp->command;
    }
  	if(temp->type == TEXT && temp->text != NULL && strcmp(temp->text, name) == 0){
      return temp->text;
  	}
		temp = temp->next;
	}
	return NULL;
}

struct container* remove_container(struct container *first, void *entry){
	if(first == NULL || entry == NULL){
    return first;
  }
  struct container* current = first;
  struct container* prev = NULL;
  while(current != NULL){
    if((current->room == entry && current->type == ROOM) || (current->item == entry && current->type == ITEM) || (current->command == entry && current->type == COMMAND) || (strcmp(current->text, (char*)entry) == 0 && current->type == TEXT)){
      if(prev == NULL){
        first = current->next;
      }
			else{
        prev->next = current->next;
      }
      free(current);
      break;
    }
    prev = current;
    current = current->next;
	}
	return first;
}