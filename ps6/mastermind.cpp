#include <Arduino.h>
#include "mastermind.h"
#include "lcd_wrapper.h"
#include "history.h"
#include "game.h"
#include "render.h"


void play_game(char* secret){
  lcd_clear();
  start_loading();
  struct GAME* game = create_game();

  while(game->state == PLAYING){
    game_buttons_logic(game, secret);
    check_guess_limits(game);
    print_ui(game, secret);
    enter_button_logic(game, secret);
  }
  lcd_clear();
  show_game_result(game);
  lcd_clear();
  game->try_check = 0;
  look_at_history(game, secret);
  destroy_game(game);
}


char* generate_code(bool repeat, int length){
   randomSeed(analogRead(A2));

   if(length < 1){
      return NULL;
   }

   if(!repeat && length > 10){
      return NULL;
   }

   char* code = (char*)calloc(length + 1, sizeof(char));

   for(int i = 0; i < length; i++){
      char let;
      do {
         let = (char)(random((int)'0', (int)'9' + 1));
      } while(!repeat && strchr(code, let));
      code[i] = let;
   }

   return code;
}


void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b){
  bool mask[] = {true, true, true, true};
  *peg_a = 0;
  *peg_b = 0;
  for(size_t i = 0; i < strlen(guess); i++){
    if(guess[i] == secret[i]){
      (*peg_a)++;
      mask[i] = false;
    }
  }
  
  for(size_t i = 0; i < strlen(guess); i++){
    for(size_t j = 0; j < strlen(guess); j++){
      if(mask[j] && guess[i] == secret[j]){
      	mask[j] = false;
        (*peg_b)++;
      }
    }
  }
}


void render_leds(const int peg_a, const int peg_b){
  turn_off_leds();
  switch (peg_a){
  case 4: digitalWrite(LED_RED_4, 1);
  case 3: digitalWrite(LED_RED_3, 1);
  case 2: digitalWrite(LED_RED_2, 1);
  case 1: digitalWrite(LED_RED_1, 1);
  }

  if(peg_b > 0){
    int shift_b = 1 + peg_a;

    switch(shift_b){
    case 1: 
      if(peg_a + peg_b >= 1) digitalWrite(LED_BLUE_1, 1);
    case 2:
      if(peg_a + peg_b >= 2) digitalWrite(LED_BLUE_2, 1);
    case 3: 
      if(peg_a + peg_b >= 3) digitalWrite(LED_BLUE_3, 1);
    case 4: 
      if(peg_a + peg_b == 4) digitalWrite(LED_BLUE_4, 1);
    }
  }
}


void turn_off_leds(){
   digitalWrite(LED_RED_1, 0);
   digitalWrite(LED_RED_2, 0);
   digitalWrite(LED_RED_3, 0);
   digitalWrite(LED_RED_4, 0);
   digitalWrite(LED_BLUE_1, 0);
   digitalWrite(LED_BLUE_2, 0);
   digitalWrite(LED_BLUE_3, 0);
   digitalWrite(LED_BLUE_4, 0);
}


void render_history(char* secret, char** history, const int entry_nr){
  lcd_set_cursor(0, 0);
  switch(entry_nr) {
  case 0: lcd_print("01:"); break;
  case 1: lcd_print("02:"); break;
  case 2: lcd_print("03:"); break;
  case 3: lcd_print("04:"); break;
  case 4: lcd_print("05:"); break;
  case 5: lcd_print("06:"); break;
  case 6: lcd_print("07:"); break;
  case 7: lcd_print("08:"); break;
  case 8: lcd_print("09:"); break;
  case 9: lcd_print("10:"); break;
  }
  lcd_print_at(4, 0, history[entry_nr]);
  int peg_a;
  int peg_b;
  get_score(secret, history[entry_nr], &peg_a, &peg_b);
  turn_off_leds();
  render_leds(peg_a, peg_b);
}