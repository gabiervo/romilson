#include <Arduino.h>

#ifndef BASIC_FUNCTIONS
#define BASIC_FUNCTIONS

void motorMovement(int pA=LOW, int pB=LOW, int pC=LOW, int pD=LOW, int motorA=18, int motorB=19, int motorC=20, int motorD=21);
int getUltrasonicDist(int trigPin, int echoPin);

#endif

