#include "function.h"

int brightness;
int fade_amount;
/*Game information*/
int phase;
int sequence[MAX_LEVEL];
int level;
bool game_over;
int score;
int game_speed;
int wrong_sequence_flag;
int base_speed;

//Time to complete the level, it should be multiplied by level to have more time for longer levels
long game_over_timer;

int dt_gameover;
int start_delay;
int anti_bouncing_delay;

/*Used to avoid phase being a global variable*/
int get_phase() {
  return phase;
}

/*Used to avoid phase being a global variable*/
void set_phase(int new_phase) {
  phase = new_phase;
}

/*Setting pin mode and base values*/
void init_hardware() {
  pinMode(REDLED, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(GREEN3, OUTPUT);
  
  turn_leds_off();

  pinMode(POTENTIOMETER, INPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);

}

void init_variables() {
  set_phase(0);
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
  
}

/*REDLED is pulsing*/
void pulse_step()
{
 analogWrite(REDLED, brightness);
 brightness += fade_amount;
 if(brightness == MAX_BRIGHTNESS || brightness == MIN_BRIGHTNESS)
 {
   fade_amount =- fade_amount;
 }
 delay(PULSE_DELAY);
}

/*Start game, going from waiting phase to game phase*/
void start_game()
{
    detachInterrupt(digitalPinToInterrupt(BUTTON1));
    set_phase(1);
    analogWrite(REDLED,0);
    game_over = false;
    game_speed = map(analogRead(POTENTIOMETER),0,1023,1,10);
    Serial.println("Ready!");
    delay(start_delay);
}

/*Show the sequence turning on and off the three green leds*/
void show_sequence()
{
  digitalWrite(REDLED, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW);
  for (int i = 0; i < level ;i++)
  {
    digitalWrite(sequence[i],HIGH);
    delay(base_speed/game_speed);
    digitalWrite(sequence[i], LOW);
    delay(base_speed/game_speed);
  }
}

/*Generate the sequence adding for each new level the last number*/
void generate_sequence()
{
  if(level < MAX_LEVEL){
  randomSeed(analogRead(A1)); //in this way is really random!!!
  int numero_sequenza = (int)random(GREEN1,GREEN3+1);
  sequence[level] = numero_sequenza;
  level++;
  } else
  {
    you_win();
  }
}

/*Ask the player to push the right button to guess the sequence*/
void get_sequence()
{
  wrong_sequence_flag = 0;
  bool waiting = false;
  unsigned long initial_time = millis();

  for (int i = 0; i < level; i++)
  {
    wrong_sequence_flag = 0;
    while(wrong_sequence_flag == 0)
    {
      for(int j = 0; j < NUMBER_OF_LEDS; j++) {
        if (digitalRead(BUTTON1 + j) == HIGH) {
          if (led_guess(GREEN1 + j, i) == false) {
            return;
          }
          waiting = true;
        }
    }
    if(waiting)
      {
        delay(anti_bouncing_delay);
        waiting = false;
      }
      if (millis() - initial_time >= game_over_timer * level)
      {
        wrong_sequence();
        return;
      }
    }
  }
  if(game_over)
  {
    return;
  }
  right_sequence();
}

/*Check if the player has pushed the right button*/
bool led_guess(int led, int i)
{
  digitalWrite(led, HIGH);
  wrong_sequence_flag = 1;
  if (led != sequence[i])
  {
    wrong_sequence();
    return false;
  }
   digitalWrite(led, LOW);
   return true;
}

/*The level is incremented*/
void right_sequence()
{
  score += level;
}

/*End of the game with a depressing sentence. Waiting phase*/
void wrong_sequence()
{
  Serial.print("Game over, you lost at a very simple game!-Score: ");
  Serial.println(score * game_speed);
  reset_game();
}

/*End of the game with a nice sentence. Waiting phase*/
void you_win()
{
  Serial.print("You win, nobody has a good memory like yours!-Score: ");
  Serial.println(score*game_speed);
  turn_leds_off();
  analogWrite(REDLED, MAX_BRIGHTNESS);
  digitalWrite(GREEN1, HIGH);
  delay(base_speed);
  digitalWrite(GREEN2, HIGH);
  delay(base_speed);
  digitalWrite(GREEN3, HIGH);
  delay(base_speed);
  reset_game();

}

/*Enables the game to be restarted*/
void reset_game()
{
  score = 0;
  set_phase(0);
  game_over = true;
  level = 0;
  turn_leds_off();
  analogWrite(REDLED, MAX_BRIGHTNESS);
  delay(dt_gameover);
  analogWrite(REDLED, MIN_BRIGHTNESS);
  EIFR = 0x01;
  attachInterrupt(digitalPinToInterrupt(BUTTON1), start_game, HIGH);
}

/*Obviusly turns the leds off*/
void turn_leds_off()
{
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW);
}
