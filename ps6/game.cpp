#include <Arduino.h>
#include "game.h"
#include "mastermind.h"
#include "history.h"
#include "lcd_wrapper.h"


bool check_win(const char* secret, const char* guess);
void set_guess(struct GAME* game, const char* secret);
void check_history(struct GAME* game, const char* secret);
void reset_guess(struct GAME* game);


void check_history(struct GAME* game, const char* secret){
  lcd_print_at(3, 0, "<");
  lcd_print_at(8, 0, ">");
  set_try_from_history(game);
  if(input_button(&game->buttons, 1) == UNPUSHED){
    lcd_print_at(3, 0, " ");
    lcd_print_at(8, 0, "  ");
    game->mode = SET_GUESS;
  }
}


void set_guess(struct GAME* game, const char* secret){
  lcd_print_at(8, 1, "<");
  lcd_print_at(13, 1, ">");
  for(int i = 0; i < 4; i++){
    if(game->buttons[i + 1].mode == CHILD){
      continue;
    }
    switch(input_button(&game->buttons, i + 1)){
    case PRESS_1:
      game->guess_mode *= -1;
    case PUSHED:
      lcd_set_cursor(9 + i, 0);
      switch(game->guess_mode){
      case 1: lcd_print("+"); break;
      case -1: lcd_print("-"); break;
      }
      break;
    case UNPUSHED:
      game->guess[i] += game->guess_mode;
    case UNPRESSED_1:  
      lcd_print_at(9, 0, "    ");
      break;
    case PRESS_2:
      game->guess_mode *= -1;
      lcd_print_at(9 + i, 0, "*");
      break;
    case UNPRESSED_2:
      lcd_print_at(9 + i, 0, " ");
      game->mode = CHECK_HISTORY;
      lcd_print_at(8, 1, " ");
      lcd_print_at(13, 1, " ");
      break;
    }
  }
}


void init_pins(){
  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
  pinMode(BTN_ENTER_PIN, INPUT);

  pinMode(LED_BLUE_1, OUTPUT);
  pinMode(LED_BLUE_2, OUTPUT);
  pinMode(LED_BLUE_3, OUTPUT);
  pinMode(LED_BLUE_4, OUTPUT);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);

  pinMode(A1, OUTPUT);
}


void game_buttons_logic(struct GAME* game, const char* secret){
  switch(game->mode){
  case SET_GUESS: set_guess(game, secret); break;
  case CHECK_HISTORY: check_history(game, secret); break;
  }
}


bool ask_player(const char* text){
  lcd_clear();
  lcd_printf(text);
  lcd_print_at(11, 0, "1.YES");
  lcd_print_at(11, 1, "2.NO");
  BUTTON* buttons = create_answer_buttons();
  bool answer = true;
  bool any_push = false;
  while(true){
    if(input_button(&buttons, 1) == PUSHED){
      answer = true;
      any_push = true;
      lcd_print_at(10, 0, ">");
      lcd_print_at(10, 1, " ");
    }
    if(input_button(&buttons, 2) == PUSHED){
      answer = false;
      any_push = true;
      lcd_print_at(10, 0, " ");
      lcd_print_at(10, 1, ">");
    }
    if(input_button(&buttons, 0) == PUSHED && any_push){
      break;
    }
  }
  lcd_clear();
  free(buttons);
  return answer;
}


void reset_guess(struct GAME* game){
  for(int i = 0; i < 4; i++) {
    game->guess[i] = '0';
  }
}


void enter_button_logic(struct GAME* game, const char* secret){
  switch(input_button(&game->buttons, 0)){
  case UNPUSHED:
    save_guess_in_history(game);
    check_game_state(game, secret);
    reset_guess(game);
    break;
  case PRESS_2:
    save_guess_in_history(game);
    check_game_state(game, secret);
    game->state = (game->state != WIN) ? LOSE : WIN;
    break;
  }
}


bool check_win(const char* secret, const char* guess){
  for(int i = 0; i < 4; i++){
    if(secret[i] != guess[i]){
      return false;
    }
  }
  return true;
}


void check_guess_limits(struct GAME* game){
  for(int i = 0; i < 4; i++){
    game->guess[i] = (game->guess[i] > '9') ? '0' : game->guess[i];
    game->guess[i] = (game->guess[i] < '0') ? '9' : game->guess[i];
  }
}

struct GAME* create_game(){
  struct GAME* game = calloc(1, sizeof(struct GAME));
  game->guess = calloc(5, sizeof(char));
  for(int i = 0; i < 4; i++){
    game->guess[i] = '0';
  }

  game->history = calloc(10, sizeof(char*));
  game->try_check = 0;
  game->try_current = 0;
  game->buttons = calloc(5, sizeof(BUTTON));
  game->guess_mode = 1;
  
  game->buttons[0].pin = BTN_ENTER_PIN;
  game->buttons[1].pin = BTN_1_PIN;
  game->buttons[2].pin = BTN_2_PIN;
  game->buttons[3].pin = BTN_3_PIN;
  game->buttons[4].pin = BTN_4_PIN;

  game->state = PLAYING;
  return game;
}


void destroy_game(struct GAME* game){
  free(game->guess);
  for(int i = 0; i < 10; i++){
    if(game->history[i] != NULL){
      free(game->history[i]);
    }
  }
  free(game->history);
  free(game->buttons);
  free(game);
}


void check_game_state(struct GAME* game, const char* secret){
  if(check_win(secret, game->guess)){
    game->state = WIN;
  }
  else if(game->try_current >= 10){
    game->state = LOSE;
  }
}