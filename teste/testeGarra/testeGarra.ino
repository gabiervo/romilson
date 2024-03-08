#include <Servo.h>

//pinos

Servo servoDir;
Servo servoEsq;
Servo servoGran;



void pickup(bool isDir){
  if(isDir){
    servoDir.write(180);
    delay(200);    
  }
  else{
    servoEsq.write(180);
    delay(200);
  }
  servoGran.write(0);
  delay(200);
}

void deliver(){
  servoGran.write(180);
  delay(200);
  servoDir.write(0);
  servoEsq.write(0);
}

void setup(){
  servoGran.attach(4);
  servoDir.attach(8);
  servoEsq.attach(7);
  Serial.begin(9600);
  servoDir.write(0);
  servoGran.write(180);
  servoEsq.write(0);
}
void loop(){
 pickup(true);
 deliver();
 delay(10000000);

}
