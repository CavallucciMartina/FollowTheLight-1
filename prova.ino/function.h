#ifndef __FUNCTION__H
#define __FUNCTION__H

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define REDLED 9
#define GREEN1 10
#define GREEN2 11
#define GREEN3 12
#define POTENTIOMETER A0
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define PULSE_DELAY 50
#define MAX_LEVEL 5
#define NUMBER_OF_LEDS 3


#include "Arduino.h"

/*Red led's information*/
extern int brightness;
extern int fade_amount;
/*Game information*/
extern int phase;
extern int sequence[MAX_LEVEL];
extern int level;
extern bool game_over;
extern int score;
extern int game_speed;
extern int wrong_sequence_flag;
extern int base_speed;
//Time to complete the level, it should be multiplied by level to have more time for longer levels
extern long game_over_timer;

extern int dt_gameover;
extern int start_delay;
extern int anti_bouncing_delay;

/*REDLED is pulsing*/
void pulseStep();

/*Start game, going from waiting phase to game phase*/
void startGame();

/*Show the sequence turning on and off the three green leds*/
void show_sequence();

/*Generate the sequence adding for each new level the last number*/
void generate_sequence();

/*Ask the player to push the right button to guess the sequence*/
void get_sequence();

/*Check if the player has pushed the right button*/
bool led_guess(int led, int i);

/*The level is incremented*/
void right_sequence();

/*End of the game with a depressing sentence. Waiting phase*/
void wrong_sequence();

/*End of the game with a nice sentence. Waiting phase*/
void you_win();

/*Enables the game to be restarted*/
void reset_game();

/*Obviusly turns the leds off*/
void turn_leds_off();

#endif
