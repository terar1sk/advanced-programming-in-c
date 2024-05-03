#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "room.h"
#include "item.h"
#include "container.h"
#include "command.h"
#include "backpack.h"
#include "game.h"
#include "parser.h"

int main(){
struct backpack* create_backpack(const int capacity);
struct backpack* destroy_backpack(struct backpack* backpack);
bool add_item_to_backpack(struct backpack* backpack, struct item* item);
void delete_item_from_backpack(struct backpack* backpack, struct item* item);
struct item* get_item_from_backpack(const struct backpack* backpack, char* name);
struct command* create_command(char* name, char* description, char* pattern, size_t nmatch);
struct command* destroy_command(struct command* command);
struct container* create_container(struct container* first, enum container_type type, void* entry);
struct container* destroy_containers(struct container* first);
void* get_from_container_by_name(struct container *first, const char *name);
struct container* remove_container(struct container *first, void *entry);
void play_game(struct game* game);
struct game* create_game();
struct game* destroy_game(struct game* game);
void execute_command(struct game* game, struct command* command);
struct item* create_item(char* name, char* description, unsigned int properties);
struct item* destroy_item(struct item* item);
struct parser* create_parser();
struct parser* destroy_parser(struct parser* parser);
struct command* parse_input(struct parser* parser, char* input);
struct room* create_room(char *name, char *description);
struct room* destroy_room(struct room* room);
void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west);
void show_room(const struct room* room);
void delete_item_from_room(struct room* room, struct item* item);
void add_item_to_room(struct room* room, struct item* item);
struct item* get_item_from_room(const struct room* room, const char* name);
struct container* create_world();
struct container* add_room_to_world(struct container* world, struct room* room);
struct container* destroy_world(struct container* world);
struct room* get_room(struct container* world, char* name);
}
