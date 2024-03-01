#include <Arduino.h>
#include <Servo.h>

Servo braco;
Servo garra;

float ultra=0.0;

int vezesVistaCaixa=0;

int tempin=0;

int pegar=139;

int ldrReadRight=0;

//ldr da esquerda
float ldrReadLeft=0.0;

int gabsno=0;

int oi=0;

//vsf = vai ser feliz(:

//mudanca de protocolo
int stateMode=0;

int alturimo=70;

void movimentoGarra(){
  pegar=20;
  //movimento garra braco
  garra.attach(7);
  garra.write(0);
  delay(500);
  braco.attach(6);

  while(pegar<140){
    braco.write(pegar);
    pegar += 1;
    delay(10);
  }

  pinMode(6,INPUT);
  garra.write(180);
  delay(1000);
  braco.attach(6);
  delay(100);
  pegar=90;
  braco.write(pegar);
  delay(300);
  while(pegar>20){
    braco.write(pegar);
    pegar -= 2;
    delay(40);
  } 
  pegar=20;
  delay(500);
  pinMode(6,INPUT);
  garra.attach(8);  
}


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
  return pulseIn(echoPin, HIGH) * 0.01723;
}


void moveRobot(int param1, int param2, int param3, int param4){
  analogWrite(3, param1);
  analogWrite(4, param2);
  analogWrite(5, param3);
  analogWrite(9, param4);
  //analogWrite(13, param1);
}


//pins ldr
int ldrRight = A1;
int ldrLeft = A5;


void setup() {

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(ldrRight, INPUT);
  pinMode(ldrLeft, INPUT);
  Serial.begin(9600);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  braco.write(20);

  delay(100);
  ldrReadRight=analogRead(ldrRight);
  delay(200);
  gabsno=200;
  delay(500);
  ldrReadLeft=analogRead(A5);
  delay(20);
  ldrReadLeft=(ldrReadLeft+analogRead(A5))/2;
  delay(20);
  ldrReadLeft=(ldrReadLeft+analogRead(A5))/2;
  ldrReadLeft=ldrReadLeft*0.6;

  delay(300);

  digitalWrite(9, LOW); 
  analogWrite(5, 255);
  digitalWrite(4, LOW);
  analogWrite(3, 255);

  delay(600);

}

void loop() {

  ultra = readUltrasonicDistance(10, 11);

  if((stateMode==0)or(stateMode==2)){
    //movimento basico, leitura ldr

    if(((analogRead(ldrRight))>(ldrReadRight))){
      digitalWrite(9, LOW); 
      analogWrite(5,240);
      digitalWrite(4, LOW);
      analogWrite(3, 255);
    }


    if((analogRead(ldrRight))<ldrReadRight){
      digitalWrite(9, LOW); 
      analogWrite(5, 255);
      analogWrite(4, 0);
      analogWrite(3, 40);
    }

    if(((analogRead(A5))<ldrReadLeft) and ((analogRead(ldrRight))>(ldrReadRight))){
      digitalWrite(9, LOW); 
      analogWrite(5, 80);
      analogWrite(4, 0);
      analogWrite(3, 255);
    }

    if(oi==0){
      if((ultra<15) and (ultra>13)){
        vezesVistaCaixa++;
        delay(10);
      }
      if((ultra<13)or(ultra>15)){
        vezesVistaCaixa=0;  
      }
    }

    if(oi==1){
      if((ultra<16.5) and (ultra>14)){
        vezesVistaCaixa++;
        delay(10);
      }
      if((ultra<14) or (ultra>16.5)){
        vezesVistaCaixa=0;  
      }
    }

    if(vezesVistaCaixa>2){
      //parar
      digitalWrite(3, LOW); 
      digitalWrite(4, LOW); 
      digitalWrite(5, LOW);
      digitalWrite(9, LOW); 
      delay(200);

      if(oi==1){
        //virada para esquerda (alinhar com caixa)
        while(readUltrasonicDistance(10, 11)<17.5){
          moveRobot(0, 0, 100, 100);
        }
        moveRobot(0, 0, 0, 0);  
        delay(200);
      }

      if((stateMode==0)){
        movimentoGarra();
      } 
      moveRobot(0, 0, 0, 0);
      //mexe garra
      delay(300);
      moveRobot(0, 0, 0, 0); 
      delay(400);
      //comeca percurso para tras
      digitalWrite(5, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
      delay(700);

      while(!(analogRead(ldrRight)>ldrReadRight*1.13)){
        digitalWrite(5, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
      }
      if(stateMode==0){
        stateMode=1;
      }
    }
  }
  //stateMode 1 acaba

  if(stateMode==1){
  if((analogRead(A5))>ldrReadLeft){
  analogWrite(3, 240); 
  digitalWrite(9, LOW);
  analogWrite(5, 255);
  digitalWrite(4, LOW);
  }

  if((analogRead(A5))<ldrReadLeft){
  analogWrite(3, 255);
  digitalWrite(9, LOW);
  analogWrite(5, 60);
  digitalWrite(4, LOW);
  }

  if(((analogRead(A5))>ldrReadLeft)and((analogRead(ldrRight))<ldrReadRight)){
  digitalWrite(9, LOW); 
  analogWrite(5, 255);
  analogWrite(4, 0);
  analogWrite(3, 80);
  }


  if((analogRead(A3)>gabsno)){
    digitalWrite(3, LOW); 
    digitalWrite(9, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);  
    delay(200);

    if(oi==1){
      digitalWrite(3, LOW); 
      digitalWrite(9, LOW);
      analogWrite(5, 255);
      digitalWrite(4, LOW); 
      delay(350);  
      digitalWrite(3, LOW); 
      digitalWrite(9, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);  
  delay(200);
  }
  braco.attach(6);
  garra.attach(7);
  while(pegar<120){
  braco.write(pegar);
  pegar += 1;
  delay(10);
  }
  pinMode(6,INPUT);
  delay(500);
  garra.write(0);
  delay(300);
  braco.attach(6);
  while(pegar>20){
  braco.write(pegar);
  pegar=pegar-1;
  delay(10);
  }
  delay(300);
  pinMode(6,INPUT);
  delay(700);
  garra.attach(8);
  pinMode(7,INPUT);
  if(oi==1){
  delay(100000000000);  
  }
  tempin=600;
  }

  if((tempin>500) and (stateMode==1)){
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  delay(200);  
  while((analogRead(ldrRight))<(ldrReadRight)){
  digitalWrite(5, HIGH); 
  digitalWrite(9, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  }
  delay(500);
  while((analogRead(ldrRight))<(ldrReadRight*1.1)){
    digitalWrite(5, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
  }
  digitalWrite(5, LOW); 
  digitalWrite(9, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  delay(100);
  stateMode=0;
  vezesVistaCaixa=0;
  tempin=0;
  pegar=139;
  oi=1;
  }

  }

}
