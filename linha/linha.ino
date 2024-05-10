#include <Servo.h>
#define TRIG 11
#define ECHO 12

const int ldrLeft = A2;
const int ldrFrente = A1;
const int ldrRight = A0;

Servo servoLeft;
Servo servoRight;
Servo bigServo;

const int motorA1 = 3;
const int motorA2 = 5;

const int motorB1 = 6;
const int motorB2 = 9;

int leftReadLdr = 0;
int rightReadLdr = 0;


void setup(){
  pinMode(ldrLeft, INPUT);
  pinMode(ldrRight, INPUT);
  pinMode(ldrFrente, INPUT);   

  //servoLeft.attach(7);
  //servoRight.attach(8);
  //bigServo.attach(4);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
}

void loop(){
  leftReadLdr = analogRead(ldrLeft);
  rightReadLdr = analogRead(ldrRight);  

  if(leftReadLdr > 950){
      digitalWrite(motorB1, HIGH);
      analogWrite(motorA1, 70);
   }
   else{
    digitalWrite(motorA1, HIGH);
    analogWrite(motorB1, 70);
   }
}
