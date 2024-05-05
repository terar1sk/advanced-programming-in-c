#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "room.h"
#include "command.h"
#include "backpack.h"
#include "parser.h"
#include "container.h"
#include "game.h"
#include "world.h"


struct container_node {
    struct item* item;
    struct container_node* next;
};

void play_game(struct game* game){
  while(game->state == PLAYING){
    char input[INPUT_BUFFER_SIZE];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    struct command* command = parse_input(game->parser, input);
    if(command != NULL){
      execute_command(game, command);
      if(game->state == GAMEOVER || game->state == RESTART){
        break;
      }
    }
    else{
      printf("Try again.\n");
    }
  }
}

struct game* create_game(){
  struct game * game = calloc(1, sizeof(struct game));
  game->state = PLAYING;
  game->world = create_world();
  game->current_room = game->world->room;
  game->backpack = create_backpack(10);
  game->parser = create_parser();
  return game;
}

struct game* destroy_game(struct game* game){
  game->parser=destroy_parser(game->parser);
  game->world=destroy_world(game->world);
  game->current_room=destroy_room(game->current_room);
  game->backpack=destroy_backpack(game->backpack);
  free(game);
  return NULL;
}

void execute_command(struct game* game, struct command* command){
  if(command == NULL){
    return;
  }
  if(strcmp(command->name, "GO") == 0){
    if(strcmp(command->groups[1], "NORTH") == 0 && game->current_room->north != NULL){
      game->current_room = game->current_room->north;
      show_room(game->current_room);
    } 
    else if(strcmp(command->groups[1], "SOUTH") == 0 && game->current_room->south != NULL){
      game->current_room = game->current_room->south;
      show_room(game->current_room);
    }
    else if(strcmp(command->groups[1], "EAST") == 0 && game->current_room->east != NULL){
      game->current_room = game->current_room->east;
      show_room(game->current_room);
    }
    else if(strcmp(command->groups[1], "WEST") == 0 && game->current_room->west != NULL){
      game->current_room = game->current_room->west;
      show_room(game->current_room);
    }
    else{
      printf("You cant go.\n");
    }
  }
  else if(strcmp(command->name, "RESTART") == 0){
    game->state = RESTART;
  }
  else if(strcmp(command->name, "QUIT") == 0){
    game->state = GAMEOVER;
  }
  else{
    printf("Unknown command.\n");
  }
}