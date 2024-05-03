#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "command.h"
#include "item.h"
#include "container.h"


struct container* create_container(struct container* first, enum container_type type, void* entry){
	if(entry==NULL){
		return NULL;
	}
	if(first==NULL){
		struct container* temp=calloc(1,sizeof(struct container));
		temp->type=type;
		if(type==TEXT){
			temp->text=entry;
		}
		if(type==ROOM){
			temp->room=entry;
		}
		if(type==COMMAND){
			temp->command=entry;
		}
		if(type==ITEM){
			temp->item=entry;
		}
		temp->next=NULL;
		return temp;
	}
	else{
		first->next=create_container(first->next,type,entry);
		return first;
	}
}

struct container* destroy_containers(struct container* first){
	if(first->next!=NULL){
		first->next=destroy_containers(first->next);
	}
	if(first->type==COMMAND){
		first->command=destroy_command(first->command);
	}
	if(first->type==ITEM){
		first->item=destroy_item(first->item);
	}
	if(first->type==ROOM){
		first->room=destroy_room(first->room);
	}
	if(first->type==TEXT){
		free(first->text);
	}
	free(first);
	first=NULL;
	return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name){
	if(first == NULL || name == NULL || *name == '\0'){
		return NULL;
	}
	struct container* temp=first;
	while(temp!=NULL){
		if(temp->type==ROOM){
			if(!strcmp(temp->room->name,name)){
				return temp->room;
			}
		}
		if(temp->type==ITEM){
			if(!strcmp(temp->item->name,name)){
				return temp->item;
			}
		}
		if(temp->type==COMMAND){
			if(!strcmp(temp->command->name,name)){
				return temp->command;
			}
		}
		if(temp->type==TEXT){
			if(!strcmp(temp->text,name)){
				return temp->text;
			}
		}
		temp=temp->next;
	}
	return NULL;
}

struct container* remove_container(struct container *first, void *entry){
  if(first == NULL || entry == NULL){
    return NULL;
	}
  return NULL;
}