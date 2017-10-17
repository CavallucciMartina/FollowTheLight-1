

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define REDLED 9
#define GREEN1 10
#define GREEN2 11
#define GREEN3 12
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define PULSE_DELAY 10


int brightness;
int fadeAmount;
int phase;
int sequence[100];
int level= 0;
int your_sequence[100];

void setup() {

  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW);

  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);

  pinMode(REDLED, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(GREEN3, OUTPUT);

  Serial.begin(9600);

  phase = 0;
  brightness=0;
  fadeAmount = 5;
  attachInterrupt(0, change, HIGH);
  int velocity = 1000;

}

void loop() {

  switch (phase) {
    case 0:
      pulseStep();
      level ++;
      break;
      case 1:
        generate_sequence();
    showSequence();
    get_sequence();
    break;
    default: break;
  }

  noInterrupts();
  int buttonState = digitalRead(BUTTON1);
  interrupts();
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
    phase = 1;
    analogWrite(REDLED,0);

}
void showSequence()
{

  digitalWrite(REDLED, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW);
  for (int i = 0; i < level ;i++)
  {
    digitalWrite(sequence[i],HIGH);
    delay(20);
    digitalWrite(sequence[i], LOW);
    delay(20);
  }
}
void generate_sequence()
{
  randomSeed(millis()); //in this way is really random!!!

  for (int i = 0; i < level; i++)
  {
      sequence[i] = random(GREEN1,GREEN3);
  }
  Serial.println(sequence[0]);
}
void get_sequence()
{
  int flag = 0; //this flag indicates if the sequence is correct
  Serial.println(level);
  for (int i = 0; i < level; i++)
  {
    flag = 0;
    while(flag == 0)
    {
        if (digitalRead(BUTTON1) == HIGH)
        {
          digitalWrite(GREEN1, HIGH);
          flag = 1;
          if (GREEN1 != sequence[i])
          {
            wrong_sequence();
            return;
           }
           digitalWrite(GREEN1, LOW);
         }

         /*if (digitalRead(BUTTON2) == HIGH)
         {
            digitalWrite(GREEN2, HIGH);

            flag = 1;

          if (GREEN2 != sequence[i])
          {
             wrong_sequence();
            return;
          }
          digitalWrite(GREEN2, LOW);
         }

          if (digitalRead(BUTTON3) == HIGH)
          {
              digitalWrite(GREEN3, HIGH);
             ;
             flag = 1;

          if (GREEN3 != sequence[i])
          {
             wrong_sequence();
            return;
          }
          digitalWrite(GREEN3 LOW);
          }

      }*/
}
right_sequence();
}

}
void right_sequence()
{

  Serial.println("  hai vinto!");
    if (level < 100);
    level++;

}

void wrong_sequence()
{
Serial.println("  hai perso!");
phase=0;

}
