#include "function.h"
#define BUTTON0 A0
#define BUTTON1 A1
#define BUTTON2 A2
#define POT     A3

#define LED0    8 /*LED BUTTON 0*/
#define LED1    9 /*LED BUTTON 1*/
#define LED2    10 /*LED BUTTON 2*/
#define LED3    11 /*LED ROSSO X INIT */

void setup() {

  /*Definisco i pin di input dei bottoni e del potenziometro */
  pinMode(BUTTON0, INPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(POT, INPUT);

  /*Definisco i pin di output dei led */
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  /*Inizialmente i 3 led sono spenti */
  digitalWrite(LED0,LOW);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);

  int level = 0; /* variabile extern che abbiamo nel .c */
  int tempo_imm = velocity_conversion(/*Leggiamo da potenziometro la velocità */);

}

void loop() {

  if(level == 0) {
    welcome();

    /*Facciamo lampeggiare led 3 */

    generate_sequence(); /*dentro al file .c */

  }
  if(level > 0 && digitalRead(LED3,HIGH))
  {
    start(); /*Nel .c */
    generate_sequence(); /*dentro al file .c */
   show_sequence();
   insert_sequence();
  }
}


}
void show_sequence()
{
  digitalWrite(LED0,LOW);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW)
  /*IN base alla sequenza accendo o spengo i led giusti */
  for (int i = 0; i < level; i++)
  {
    digitalWrite(sequence[i], HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(tempo_imm);
  }

}





void insert_sequence(){
  int flag = 0;
  for (int i = 0; i< level ; i++){
    flag = 0;

    if(digitalRead(BUTTON0) == LOW){
      /*Controllo se il bottone 0 non è stato premuto */
      digitalWrite(LED0,HIGH);
      current_sequence[i]=LED0;
      flag=1;
      if(current_sequence[i] != sequence[i]){
        wrong_sequence();
        return;
      }
      digitalWrite(LED0,LOW);
    }

    /*Reiterare per altri due bottoni */



    }
  }
}
