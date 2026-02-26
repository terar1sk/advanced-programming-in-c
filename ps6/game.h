#include "button.h"
#include "render.h"


enum GAME_STATE{
  PLAYING,
  LOSE,
  WIN
};


enum GAME_MODE{
  SET_GUESS,
  CHECK_HISTORY
};


struct GAME{
  int guess_mode;
  char* guess;
  char** history;
  int try_check;
  int try_current;
  BUTTON* buttons;
  GAME_STATE state;
  GAME_MODE mode;
};


void init_pins();
bool ask_player(const char* text);
void game_buttons_logic(struct GAME* game, const char* secret);
void enter_button_logic(struct GAME* game, const char* secret);
void check_guess_limits(struct GAME* game);
struct GAME* create_game();
void destroy_game(struct GAME* game);
void check_game_state(struct GAME* game, const char* secret);