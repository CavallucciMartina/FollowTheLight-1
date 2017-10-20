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

  phase = 0;
  brightness = 0;
  fade_amount = 5;
  level = 0;
  score=0;
  game_speed = 1;
  base_speed = 500;

  game_over_timer = 5000;
  dt_gameover = 2000;
  start_delay = 1000;
  anti_bouncing_delay = 250;
  
  attachInterrupt(digitalPinToInterrupt(BUTTON1), startGame, HIGH);
  Serial.println("Welcome to Follow the Light!");
}

void loop() {
  switch (phase)
  {
    case 0:                 /*Waiting phase*/
      pulseStep();
      break;
    case 1:                 /*Gaming phase*/
      generate_sequence();
      show_sequence();
      get_sequence();
      break;
    default: break;
  }
}
