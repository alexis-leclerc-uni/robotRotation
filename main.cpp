#include <Arduino.h>
#include <LibRobus.h>

void setup(){
  BoardInit();
  MOTOR_SetSpeed(0, 0.5);
  MOTOR_SetSpeed(1, 0.5);
  delay(1000);
  MOTOR_SetSpeed(0, -1);
  MOTOR_SetSpeed(1, -1);
  delay(500);
}
