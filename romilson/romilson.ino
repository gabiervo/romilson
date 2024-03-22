#include <Servo.h>
#define TRIG 11;
#define ECHO 12;

const int ldr1 = A0;
const int ldr2 = A2;

Servo servoD;
Servo servoE;

Servo servoG;

const int motorA1 = 3;
const int motorA2 = 5;

const int motorB1 = 6;
const int motorB2 = 9;

void mov(int leitura){
  if(leitura > 0){

    if(leitura > 120){
      analogWrite(motorB2, leitura/2);
      }
    else{
      digitalWrite(motorB2, LOW);
    }

      analogWrite(motorA1, leitura);
      digitalWrite(motorB1, LOW);

    }

    else{

      if(abs(leitura) > 120){
        analogWrite(motorA2, leitura/2);
      }

      else{
        digitalWrite(motorB2, LOW);
      }

        analogWrite(motorB1, abs(leitura));
        digitalWrite(motorA1, LOW);
      }
  }


void setup(){
  servoD.attach(8);
  servoE.attach(7);
  servoG.attach(4);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
}

void loop(){


}
