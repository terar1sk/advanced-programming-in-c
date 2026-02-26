#include <Arduino.h>
#include "lcd_wrapper.h"
#include "mastermind.h"
#include "history.h"
#include "game.h"


void check_back_move(struct GAME* game);
void check_forward_move(struct GAME* game);
void check_copy_history(struct GAME* game);


void look_at_history(struct GAME* game, const char* secret){
  lcd_print_at(0, 1, "Your history..");
  lcd_print_at(9, 0, "[    ]");
  lcd_print_at(10, 0, secret);
  while(input_button(&game->buttons, 0) != UNPUSHED){
    set_try_from_history(game);
    render_history(secret, game->history, game->try_check);
  }
  lcd_clear();
  turn_off_leds();
}


void save_guess_in_history(struct GAME* game){
  game->history[game->try_current] = calloc(5, sizeof(char));
  for(int i = 0; i < 4; i++){
    game->history[game->try_current][i] = game->guess[i];
  }
  game->try_check = game->try_current;
  game->try_current++;
}

void set_try_from_history(struct GAME* game){
  check_back_move(game);
  check_forward_move(game);
  check_copy_history(game);
}


void check_copy_history(struct GAME* game){
  if(input_button(&game->buttons, 4) == PUSHED && game->try_current > 0){
    for(int i = 0; i < strlen(game->guess); i++){
      game->guess[i] = game->history[game->try_check][i];
    }
  }
}


void check_forward_move(struct GAME* game){
  if(input_button(&game->buttons, 3) == PUSHED && game->try_check < game->try_current - 1){
    game->try_check++;
  }
}


void check_back_move(struct GAME* game){
  if(input_button(&game->buttons, 2) == PUSHED && game->try_check > 0){
    game->try_check--;
  }
}