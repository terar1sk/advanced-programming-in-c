#include <Arduino.h>
#include "render.h"
#include "mastermind.h"
#include "lcd_wrapper.h"
#include "game.h"


void print_guess(const char* guess);
void render_reds();
void render_blues();
void render_empty_history();


void print_ui(struct GAME* game, const char* secret){
  print_guess(game->guess);
  if(game->try_current > 0){
    render_history(secret, game->history, game->try_check);
  }
  else{
    render_empty_history();
  }
}


void render_empty_history(){
  lcd_print_at(0, 0, "00:");
  lcd_set_cursor(4, 0);
  for(int i = 0; i < 4; i++){
    lcd_print("x");
  }
}


void show_game_result(struct GAME* game){
  switch(game->state){
  case WIN:
    render_win_leds();
    lcd_print_at(0, 0, "You win!"); 
    break;
  case LOSE:
    render_lose_leds();
    lcd_print_at(0, 0, "You lose...");
    break;
  }
  delay(1000);
}


void lcd_printf(const char* text){
  for(int x = 0, y = 0, ind = 0; ind < strlen(text); ind++, x++){
    if(text[ind] == '\n'){
      y++;
      ind++;
      x = 0;
    }
    char symbol[] = " ";
    symbol[0] = text[ind];
    lcd_print_at(x, y, symbol);
  }
}


void print_guess(const char* guess){
  lcd_print_at(0, 1, "Guess:  ");
  lcd_print_at(9, 1, guess);
}


void start_loading(){
  lcd_print_at(0, 0, "Let's start..");
  lcd_print_at(0, 1, "[______________]");
  for(int i = 1; i < 15; i++){
    lcd_print_at(i, 1, "=");
    switch(i){
    case 3: digitalWrite(LED_RED_1, 1); break;
    case 6: digitalWrite(LED_RED_2, 1); break;
    case 9: digitalWrite(LED_RED_3, 1); break;
    case 12: digitalWrite(LED_RED_4, 1); break;
    }
    delay(150);
  }
  lcd_clear();
  turn_off_leds();
}


void start_title(){
  lcd_clear();
  lcd_print_at(0, 0, "Welcome to");
  lcd_print_at(0, 1, "Mastermind!");
  delay(1500);

  lcd_clear();
  lcd_print_at(0, 0, "Guess my secret");
  lcd_print_at(0, 1, "combination.");
  delay(2500);

  lcd_clear();
}


void render_reds(){
  digitalWrite(LED_RED_1, 1);
  digitalWrite(LED_RED_2, 1);
  digitalWrite(LED_RED_3, 1);
  digitalWrite(LED_RED_4, 1);
}


void render_lose_leds(){
  for(int i = 0; i < 3; i++){
    turn_off_leds();
    delay(100);
    render_reds();
    delay(100);
  }
  turn_off_leds();
}


void render_blues(){
  digitalWrite(LED_BLUE_1, 1);
  digitalWrite(LED_BLUE_2, 1);
  digitalWrite(LED_BLUE_3, 1);
  digitalWrite(LED_BLUE_4, 1);
}


void render_win_leds(){
  for(int i = 0; i < 3; i++){
    turn_off_leds();
    delay(100);
    render_blues();
    delay(100);
  }
  turn_off_leds();
}