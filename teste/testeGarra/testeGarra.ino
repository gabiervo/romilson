#include <Servo.h>

//pinos

Servo servoDir;
Servo servoEsq;
Servo servoGran;



void pickup(){
  delay(500);
  servoGran.write(130);
  delay(500);
  servoDir.write(90);
}

void deliver(){
  servoGran.write(0);
  delay(200);
  servoDir.write(0);
  servoEsq.write(0);
}

void setup(){
  servoGran.attach(4);
  servoGran.write(0);
  
  delay(500);
  
  servoDir.attach(8);
  
  servoDir.write(180);
  delay(500);
}
void loop(){
  pickup();
}
