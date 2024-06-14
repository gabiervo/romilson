#include <Arduino.h>
#include "basicFunctions.h"

void motorMovement(int pA=LOW, int pB=LOW, int pC=LOW, int pD=LOW, int motorA=18, int motorB=19, int motorC=20, int motorD=21){
   int powerList[4] = {pA, pB, pC, pD};
   int motorList[4] = {motorA, motorB, motorC, motorD};

   for(int i = 0; i < sizeof(powerList)/sizeof(int); i++){

      if(powerList[i] == LOW or powerList[i] == HIGH){
         digitalWrite(motorList[i], powerList[i]);
      }
      else{
         analogWrite(motorList[i], powerList[i]);
      }

   }

}

int getUltrasonicDist(int trigPin, int echoPin){
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);

   float duration = pulseIn(echoPin, HIGH);
   float distance = (duration*.0343)/2;

   return distance;
}
