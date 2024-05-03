#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>
#include "container.h"
#include "command.h"
#include "parser.h"


struct parser* create_parser(){
  struct parser * parser = calloc(1, sizeof(parser));
  parser->commands = create_container(NULL, COMMAND, create_command("SEVER", "SEVER", "(\\s*[sS][eE][vV][eE][rR]\\s*)", 1));
  create_container(parser->commands, COMMAND, create_command("JUH", "JUH", "\\s*[jJ][uU][hH]]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("VYCHOD", "VYCHOD", "\\s*[vV][yY][cC][hH][oO][dD]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("ZAPAD", "ZAPAD", "\\s*[zZ][aA][pP][aA][dD]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("POUZI", "POUZI", "\\s*[pP][oO][uU][zZ][iI]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("PRESKUMAJ", "PRESKUMAJ", "\\s*[pP][rR][eE][sS][kK][uU][mM][aA][jJ]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("NAHRAJ", "NAHRAJ", "\\s*[nN][aA][hH][rR][aA][jJ]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("ULOZ", "ULOZ", "\\s*[uU][lL][oO][zZ]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("KONIEC", "KONIEC", "\\s*[kK][oO][nN][iI][eE][cC]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("ROZHLIADNI SA", "ROZHLIADNI SA", "\\s*[rR][oO][zZ][hH][lL][iI][aA][dD][nN][iI][ ][sS][aA]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("PRIKAZY", "PRIKAZY", "\\s*[pP][rR][iI][kK][aA][zZ][yY]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("VERZIA", "VERZIA", "\\s*[vV][eE][rR][zZ][iI][aA]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("RESTART", "RESTART", "\\s*[rR][eE][sS][tT][aA][rR][tT]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("O HRE", "O HRE", "\\s*[oO][ ][hH][rR][eE]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("VEZMI", "VEZMI", "\\s*[vV][eE][zZ][mM][iI]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("POLOZ", "POLOZ", "\\s*[pP][oO][lL][oO][zZ]\\s*", 1));
  create_container(parser->commands, COMMAND, create_command("INVENTAR", "INVENTAR", "\\s*[iI][nN][vV][eE][nN][tT][aA][rR]\\s*", 1));
  parser->history = create_container(NULL, COMMAND, create_command("Start", "Start game", "(Start)", 0));
  return parser;
}

struct parser* destroy_parser(struct parser* parser){
  if(parser->commands!=NULL){
    parser->commands=destroy_containers(parser->commands->next);
  }
  if(parser->history==NULL){
    parser->history=destroy_containers(parser->history->next);
  }
  free(parser);
  return NULL;
}

struct command* parse_input(struct parser* parser, char* input){
  if(parser == NULL || input == NULL || strlen(input) < 1){
    return NULL;
  }
  else{
    while(parser->commands != NULL && parser->commands->command != NULL){
      if(regexec(&parser->commands->command->preg, input, 0, NULL, REG_ICASE) != REG_NOMATCH){
        return parser->commands->command;
      }
      parser->commands = parser->commands->next;
    }
    return NULL;
  }
}