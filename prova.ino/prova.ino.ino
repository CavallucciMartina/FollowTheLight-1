#include "function.h"

void setup()
{
  init_hardware();
  Serial.begin(9600);

  init_variables();

  attachInterrupt(digitalPinToInterrupt(BUTTON1), start_game, HIGH);
  Serial.println("Welcome to Follow the Light!");
}

void loop() {
  switch (get_phase())
  {
    case 0:                 /*Waiting phase*/
      change_fade_amount();
      pulse_step();
      break;
    case 1:                 /*Gaming phase*/
      generate_sequence();
      show_sequence();
      get_sequence();
      break;
    default: break;
  }
}
