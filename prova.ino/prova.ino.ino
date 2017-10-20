#include "function.h"

void setup()
{
  //Pin mode
  pinMode(REDLED, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(GREEN3, OUTPUT);
  
  turn_leds_off();

  pinMode(POTENTIOMETER, INPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);

  Serial.begin(9600);

  init_variables();

  attachInterrupt(digitalPinToInterrupt(BUTTON1), start_game, HIGH);
  Serial.println("Welcome to Follow the Light!");
}

void loop() {
  switch (phase)
  {
    case 0:                 /*Waiting phase*/
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
