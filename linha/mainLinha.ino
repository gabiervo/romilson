#include <Servo.h>

Servo base;
Servo garraE;
Servo garraD;

float ultra=0.0;

int valLdrDireita=0;

//0 state is line movement, 1 state is box pickup
int stateManager=0;

int leituraLdrEsquerda=0;

int pA=3;
int pB=5;
int pC=9;
int pD=6;

int ldrDireita = A2;
int ldrEsquerda = A0;
int ldrFrente = A1;

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

void motorMovement(stateA1=LOW, stateA2=LOW, stateB1=LOW, stateB2=LOW){
  int stateList[4] = {stateA1, stateA2, stateB1, stateB2};
  int motorList[4] = {pA, pB, pC, pD};
  for(int i = 0; i < sizeof(stateList)/sizeof(int); i++){analogWrite(motorList[i], stateList[i]);}
}


void setup() {

  pinMode(pA, OUTPUT);
  pinMode(pB, OUTPUT);
  pinMode(pC, OUTPUT);
  pinMode(pD, OUTPUT);
  pinMode(ldrEsquerda, INPUT);
  pinMode(ldrFrente, INPUT);
  pinMode(ldrDireita, INPUT);
  Serial.begin(9600);

  delay(100);
  //valores bases para preto e branco
  valLdrDireita=analogRead(ldrDireita);
  leituraLdrEsquerda=analogRead(ldrEsquerda);
  delay(20);
  valLdrDireita=(valLDR+analogRead(ldrDireita))/2;
  leituraLdrEsquerda=(leit+analogRead(ldrEsquerda))/2;
  delay(20);
  valLdrDireita=(valLDR+analogRead(ldrDireita))/2;
  leituraLdrEsquerda=(leit+analogRead(ldrEsquerda))/2;
  delay(20);
  valLdrDireita=(valLDR+analogRead(ldrDireita))/2;
  leituraLdrEsquerda=(leit+analogRead(ldrEsquerda))/2;

}

void loop() {

  ultra=(0.01723 * readUltrasonicDistance(10, 11));

  if(analogRead(ldrDireita)>valLdrDireita){
    motorMovement(LOW, HIGH, LOW, LOW);
  }

  if(analogRead(ldrDireita)<valLdrDireita){
    motorMovement(LOW, LOW, HIGH, LOW);
  }

  if(ultra<3){
    delay(10);
    if(ultra<(0.01723 * readUltrasonicDistance(10, 11))){
      motorMovement();

      delay(200); 

      garraE.attach(7);
      garraE.write(180);

      delay(300);
      base.attach(4);
      delay(100);
      base.write(0);
      delay(500);

      motorMovement(HIGH, LOW, HIGH, LOW);
      delay(500);

      while( analogRead(ldrDireita) < valLdrDireita){
        motorMovement(HIGH, LOW, HIGH, LOW);
      }

      stateManager=1;
    }
  }

  if(stateManager==1){
    if(analogRead(ldrEsquerda)>leituraLdrEsquerda){
      motorMovement(LOW, 100, HIGH, LOW);
    }

    if(analogRead(ldrEsquerda)<leituraLdrEsquerda){
      motorMovement(LOW, HIGH, LOW, 70);
    }  
  }

}
