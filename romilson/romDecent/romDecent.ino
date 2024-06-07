#include <Servo.h>
#define NUM_OF_CHECKS_FOR_DEPOSIT 4

Servo base;
Servo garraE;
Servo garraD;

float ultra=0.0;

int valLDR=0;

int Iervola=0;

int vez=0;

int leit=0;

int paro=0;

float mult=0.75;

float seg=0.9;

int CalmaLa=0;

int pA=3;
int pB=5;
int pC=9;
int pD=6;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
   pinMode(triggerPin, OUTPUT);  // Clear the trigger
   digitalWrite(triggerPin, LOW);
   delayMicroseconds(2);
   // Sets the trigger pin to HIGH state for 10 microseconds
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerPin, LOW);
   pinMode(echoPin, INPUT);
   // Reads the echo pin, and returns the sound wave travel time in microseconds
   return pulseIn(echoPin, HIGH);
}

void motorMovement(int stateA1=LOW, int stateA2=LOW, int stateB1=LOW, int stateB2=LOW){
   int stateList[4] = {stateA1, stateA2, stateB1, stateB2};
   int motorList[4] = {pA, pB, pC, pD};
   for(int i = 0; i < sizeof(stateList)/sizeof(int); i++){analogWrite(motorList[i], stateList[i]);}
}


void setup() {

   pinMode(pA, OUTPUT);
   pinMode(pB, OUTPUT);
   pinMode(pC, OUTPUT);
   pinMode(pD, OUTPUT);
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);
   pinMode(A2, INPUT);
   Serial.begin(9600);

   //essa parte inteira serve só p média mds do céu
   delay(100);

   valLDR=analogRead(A2);
   leit=analogRead(A0);
   paro=analogRead(A1);

   int *valList = new int[3] {leit, paro, valLDR};
   int *pinList = new int[3] {A0, A1, A2};
   for(int y = 0; y < 3; y++){
      for(int j = 0; j < 3; j++){
         delay(20);
         valList[j] = ( valList[j] + analogRead(pinList[j]) ) / 2;
      }
   }
   delete[] valList;
   delete[] pinList;
}

void loop() {

   ultra=(0.01723 * readUltrasonicDistance(10, 11));

   Serial.println(analogRead(A1));

   if(analogRead(A2)>valLDR){
      motorMovement(LOW, HIGH, 230, LOW);
   }

   if(analogRead(A2)<valLDR){
      motorMovement(LOW, 30, HIGH, LOW);
   }

   if((analogRead(A2)>valLDR)and(analogRead(A0)<leit*mult)){
      motorMovement(LOW, HIGH, 50, LOW);
   }

   if(CalmaLa==0){
      if(ultra<25){
         base.attach(4);
         base.write(65);
         CalmaLa=1;    
      }
   }

   if(ultra<5){
      delay(10);
      motorMovement(LOW, HIGH, 255, LOW);
      delay(100);

      //reset motors
      motorMovement();
      delay(200); 

      base.attach(4);
      delay(100);
      base.write(80);
      delay(200);

      if(vez==0){
         garraE.attach(7);
         garraE.write(180);
         delay(300);
      }

      if(vez==2){
         garraD.attach(8);
         garraD.write(0);
         delay(300);
      }

      base.write(0);
      delay(500);
      motorMovement(HIGH, LOW, LOW, 220);

      delay(500); 
      motorMovement(HIGH, LOW, HIGH, LOW);

      delay(1000);
      while(analogRead(A2)<valLDR){
         motorMovement(HIGH, LOW, HIGH, LOW);
      }
      Iervola=1;
      base.attach(13);
   }

   if(Iervola==1){

      if(analogRead(A0)>leit*seg){
         motorMovement(LOW, 30, HIGH, LOW);
      }

      if(analogRead(A0)<leit*seg){
         motorMovement(LOW, HIGH, 30, LOW);
      } 

   }
}
