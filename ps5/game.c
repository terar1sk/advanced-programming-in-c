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

void play_game(struct game* game){
  game->state = PLAYING;
  while(game->state == PLAYING){
    game->state = GAMEOVER;
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

}
