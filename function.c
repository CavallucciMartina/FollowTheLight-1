#include "function.h"

const int MAX_LEVEL = 50; /*Massima numero di sequenze da indovinare*/
 extern int sequence[MAX_LEVEL];/*Vettore in cui memorizziamo il numero di Bottone da premere*/
int current_sequence[MAX_LEVEL];/*Vettore di sequenze digitate da utente con bottoni*/
extern int level = 0; /*Livello al quale si trova l'utente, se è al livello zero dovrà partire la prima fase di inizio */
int velocity = 0; /* Inizialmente la velocità settata dal potenziometro sarà a 0 o a quella settata */
int score = 0; /*Inizialmente il punteggio parte da 0 */

void welcome(int current_velocity){
  score = 0
  printf("welcome to the follow the light\n", );
  level ++;
  velocity = current_velocity;

}
void generate_sequence {
  randomSeed(millis());
    sequence[level]= random(8-11);/* faccio scegliere casualmente i led */

  }
}
int velocity_conversion()
{
  /*Convertiamo valore potenziometro iin velocità led */
}
