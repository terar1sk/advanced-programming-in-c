#define PRESS_DELAY 750
#define BUTTON_DURATION 2

enum BUTTON_MODE{
  STANDART,
  CHILD,
  PARENT
};

enum BUTTON_STATE{
  UNPUSHED,
  UNPRESSED_1,
  UNPRESSED_2,
  PUSHED,
  PRESS_1,
  PRESS_2,
  NONE
};

struct BUTTON{
  int pin;
  BUTTON_STATE state;
  BUTTON_MODE mode;
  long push_time;
};

BUTTON_STATE input_button(BUTTON** buttons, const int index);
BUTTON* create_answer_buttons();