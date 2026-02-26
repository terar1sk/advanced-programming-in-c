#include <Arduino.h>
#include "button.h"
#include "mastermind.h"


void reset_parent_button(BUTTON** buttons);
void set_parent_button(BUTTON** buttons, const int index);
BUTTON_STATE check_push(BUTTON** buttons, const int index, long* current_time);
BUTTON_STATE check_unpushed(BUTTON** buttons, const int index);
BUTTON_STATE check_press(BUTTON** buttons, const int index, const long current_time, const int duration);
BUTTON_STATE check_unpressed(BUTTON** buttons, const int index, const int duration);


void reset_parent_button(BUTTON** buttons){
  for(int i = 1; i <= 4; i++){
    (*buttons)[i].mode = STANDART;
  }
}


void set_parent_button(BUTTON** buttons, const int index){
  if((*buttons)[index].mode == CHILD){
    return;
  }

  (*buttons)[index].mode = PARENT;
  for(int i = 1; i <= 4; i++){
    if(i == index){
      continue;
    }
    (*buttons)[i].mode = CHILD;
  }
}


BUTTON_STATE check_push(BUTTON** buttons, const int index, long* current_time){
  *current_time = millis();
  if(digitalRead((*buttons)[index].pin) && (*buttons)[index].state == UNPUSHED){
    (*buttons)[index].state = PUSHED;
    (*buttons)[index].push_time = *current_time;
    set_parent_button(buttons, index);
    return PUSHED;
  }
  return NONE;
}


BUTTON_STATE check_unpushed(BUTTON** buttons, const int index){
  if(!digitalRead((*buttons)[index].pin) && (*buttons)[index].state == PUSHED){
    (*buttons)[index].state = UNPUSHED;
    reset_parent_button(buttons);
    return UNPUSHED;
  }
  return NONE;
}


BUTTON_STATE check_press(BUTTON** buttons, const int index, const long current_time, const int duration){
  if((*buttons)[index].state == (PUSHED + duration) && current_time - (*buttons)[index].push_time >= (PRESS_DELAY * (duration + 1))){
    (*buttons)[index].state = PRESS_1 + duration;
    return PRESS_1 + duration;
  }
  return NONE;
}


BUTTON_STATE check_unpressed(BUTTON** buttons, const int index, const int duration){
  if(!digitalRead((*buttons)[index].pin) && (*buttons)[index].state == PRESS_1 + duration){
    (*buttons)[index].state = UNPUSHED;
    reset_parent_button(buttons);
    return UNPRESSED_1 + duration;
  }
  return NONE;
}


BUTTON* create_answer_buttons(){
  BUTTON* buttons = calloc(3, sizeof(BUTTON));
  buttons[0].pin = BTN_ENTER_PIN;
  buttons[1].pin = BTN_1_PIN;
  buttons[2].pin = BTN_2_PIN;
  return buttons;
}


BUTTON_STATE input_button(BUTTON** buttons, const int index){
  long current_time;
  if(check_push(buttons, index, &current_time) != NONE){
    return PUSHED;
  }
  else if(check_unpushed(buttons, index) != NONE){
    return UNPUSHED;
  }
  else{
    for(int duration = 0; duration < BUTTON_DURATION; duration++){
      if(check_press(buttons, index, current_time, duration) != NONE){
        return PRESS_1 + duration;
      }
      else if(check_unpressed(buttons, index, duration) != NONE){
        return UNPRESSED_1 + duration;
      }
    }
  }
  return NONE;
}