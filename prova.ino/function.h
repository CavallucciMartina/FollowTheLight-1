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

/*Used to avoid phase being a global variable*/
int get_phase();

/*Used to avoid phase being a global variable*/
void set_phase(int new_phase);

/*Setting pin mode and base values*/
void init_hardware();

/*Initialization of game variables*/
void init_variables();

/*REDLED is pulsing*/
void pulse_step();

/*Start game, going from waiting phase to game phase*/
void start_game();

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

/*Turns on the three leds, with a delay in-between*/
void win_animation();

#endif
