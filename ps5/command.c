#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "command.h"


struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
  if(name != NULL && description != NULL && strlen(name) > 0 && strlen(description) > 0){
    struct command * new_command = calloc(1, sizeof(struct command));
    char *new_name = malloc(strlen(name) + 1);
    char *new_description = malloc(strlen(description) + 1);
    strcpy(new_name, name);
    strcpy(new_description, description);
    new_command->name = new_name;
    new_command->description = new_description;
    if(nmatch){
      new_command->nmatch = nmatch;
    }
    if(pattern != NULL){
      regex_t regex;
      regcomp(&regex, pattern, 0);
      new_command->preg = regex;
    }
    return new_command;
  }
  else{
    return NULL;
  }
}

struct command* destroy_command(struct command* command){
  if(command!=NULL){
    if(command->name!=NULL){
      free(command->name);
    }
	if(command->description!=NULL){
	  free(command->description);
	}
	regfree(&command->preg);
	free(command);
  }
  return NULL;
}