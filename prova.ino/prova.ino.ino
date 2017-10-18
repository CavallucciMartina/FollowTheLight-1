#include "TimerOne.h"
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define REDLED 9
#define GREEN1 10
#define GREEN2 11
#define GREEN3 12
#define POTENZIOMETRO A0
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define PULSE_DELAY 50
#define MAX_LEVEL 5

int brightness;
int fadeAmount;
int phase;
int sequence[MAX_LEVEL];
int level;
int flag;
bool gameOver;
int score;
int velocity;

long Timer = 5000;
void setup() {

  pinMode(REDLED, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(GREEN3, OUTPUT);

  turnLedsOff();

  pinMode(POTENZIOMETRO, INPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);

  Serial.begin(9600);

  phase = 0;
  brightness=0;
  fadeAmount = 5;
  level = 0;
  score=0;

  attachInterrupt(digitalPinToInterrupt(2), change, HIGH);
  velocity = 1;

  Serial.println("Welcome to Follow the Light!");
}

void loop() {

  switch (phase) {
    case 0:
      pulseStep();
      break;
    case 1:
      generate_sequence();
      showSequence();
      get_sequence();
      break;
    default: break;
  }

}

void pulseStep() {

 analogWrite(REDLED,brightness);
 brightness +=fadeAmount;
 if(brightness == MAX_BRIGHTNESS || brightness == MIN_BRIGHTNESS) {
   fadeAmount = -fadeAmount;
 }
 delay(PULSE_DELAY);
}
void change(){
    detachInterrupt(digitalPinToInterrupt(2));
    phase = 1;
    analogWrite(REDLED,0);
    gameOver=false;
    velocity=map(analogRead(POTENZIOMETRO),0,1023,1,10);
    Serial.println("Game started!\nVelocità impostata: ");
    Serial.print(velocity);
    Serial.print("   Valore potenziometro: ");
    Serial.println(analogRead(POTENZIOMETRO));
    delay(500);
}
void showSequence()
{

  digitalWrite(REDLED, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW);
  Serial.print("Mostra sequenza: ");
  for (int i = 0; i < level ;i++)
  {
    Serial.print(sequence[i]);
    Serial.print(" ");
    digitalWrite(sequence[i],HIGH);
    delay(500/velocity);
    digitalWrite(sequence[i], LOW);
    delay(500/velocity);
  }
  Serial.println();
}
void generate_sequence()
{
  if(level<MAX_LEVEL){
  Serial.print("Genera sequenza: ");
  randomSeed(analogRead(0)); //in this way is really random!!!
  int numero_sequenza=(int)random(10,13);
  Serial.println(numero_sequenza);
  sequence[level] = numero_sequenza;
  level++;
  } else{
    you_win();
  }
}
void get_sequence()
{
  flag = 0; //this flag indicates if the sequence is correct
  bool waiting = false;
  Serial.print("Livello: ");
  Serial.println(level);


  unsigned long initialTime = millis();

  //Timer1.initialize(Timer*level);
  //Timer1.attachInterrupt(wrong_sequence);

  for (int i = 0; i < level; i++)
  {
    flag = 0; //TODO: togliere?
    while(flag == 0)
    {
      if (digitalRead(BUTTON1) == HIGH) {
        if (ledGuess(GREEN1, i) == false) {
          return;
        }
         waiting=true;
      }
      if (digitalRead(BUTTON2) == HIGH) {
        if (ledGuess(GREEN2, i) == false) {
          return;
        }
         waiting=true;
      }
      if (digitalRead(BUTTON3) == HIGH) {
        if (ledGuess(GREEN3, i) == false) {
          return;
        }
         waiting=true;
      }
      if(waiting){
        delay(500);
         waiting=false;
      }
      if (millis()-initialTime >= Timer*level) {
        wrong_sequence();
        return;
      }
    }
  }
  if(gameOver){
    return;
  }
  right_sequence();
}

bool ledGuess(int led, int i)
{
  digitalWrite(led, HIGH);
  flag = 1;
  if (led != sequence[i])
  {
    wrong_sequence();
    return false;
  }
   digitalWrite(led, LOW);
   return true;
}

void right_sequence()
{

  Serial.println("Sequenza indovinata\nProssima sequenza in arrivo...\n");
  score+=level;

}

void wrong_sequence()
{
  Serial.print("Hai perso!\nIl tuo punteggio finale è: ");
  Serial.println(score*velocity);
  score=0;
  phase=0;
  gameOver=true;
  level=0;
  turnLedsOff();
  analogWrite(REDLED, 255);
  delay(500);
  analogWrite(REDLED, 0);

  EIFR=0x01;
  attachInterrupt(digitalPinToInterrupt(2), change, HIGH);

}

void you_win()
{
  Serial.print("Hai vinto!\nIl tuo punteggio finale è: ");
  Serial.println(score*velocity);
  score=0;
  phase=0;
  gameOver=true;
  level=0;
  turnLedsOff();
  analogWrite(REDLED, 255);
  delay(500);
  analogWrite(REDLED, 0);

  EIFR=0x01;
  attachInterrupt(digitalPinToInterrupt(2), change, HIGH);

}

void turnLedsOff() {
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW);

}
