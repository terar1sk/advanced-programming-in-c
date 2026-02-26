#include "lcd_wrapper.h"
#include "mastermind.h"
#include "game.h"

int main(){
  init();

  init_pins();

  //setup
  lcd_init();
  Serial.begin(9600);
  
  //loop
  start_title();
  do{
    bool is_repeat = ask_player("Nums will\nrepeat?");
    char* code = generate_code(is_repeat, 4);
    Serial.println(code);
    play_game(code);
    free(code);
  } while(ask_player("Play\nagain?"));

  lcd_print_at(0, 0, "See you later!");
  delay(1000);
  lcd_clear();
  return 0;
}