// librairies
#include <LibRobus.h>

const int gauche = 0;
const int droite = 1;
const int temps_lecture_ms = 2;

int countPulses = 0;
const float speed = 0.2;
uint8_t id_set_motors_speed;

bool state = false;


void turn(bool side, float currentSpeed);
void ramp_up(float finalSpeed, float variation, bool side);

void setup()
{
  // initialisation de RobUS et du port sériel à 9600 Bauds
  BoardInit();
  ENCODER_Reset(gauche);
  ENCODER_Reset(droite);
}

void loop()
{
  if(ROBUS_IsBumper(2) && !state){
    turn(gauche, 0.25);
    state=true;
    
  };
  if(ROBUS_IsBumper(3) && !state){
    turn(droite, 0.25);
    state=true;
  }
}

void turn(bool side, float currentSpeed){
    ENCODER_Reset(gauche);
    ENCODER_Reset(droite);
    ramp_up(currentSpeed, 4, side);
    Serial.println("ramp up done");
    if(side){
      MOTOR_SetSpeed(droite, currentSpeed);
      MOTOR_SetSpeed(gauche, -currentSpeed);
    }
    else{
      MOTOR_SetSpeed(droite, -currentSpeed);
      MOTOR_SetSpeed(gauche, currentSpeed);
    }
    int currentValueRight = ENCODER_Read(droite);
    int currentValueLeft = ENCODER_Read(gauche);
    while(currentValueRight >= 1950 || currentValueLeft >=1950){
      int currentValueRight = ENCODER_Read(droite);
      int currentValueLeft = ENCODER_Read(gauche);
      delay(10);
    }
    MOTOR_SetSpeed(gauche, 0);
    MOTOR_SetSpeed(droite, 0);
    ENCODER_Reset(gauche);
    ENCODER_Reset(droite);
    Serial.println("on arrete!!!!!!!!!!");
}

void ramp_up(float finalSpeed, float variation, bool side){
  float currentSpeed = 0;
  for (float i = 0; currentSpeed <= finalSpeed; i=i+0.01)
  {
    currentSpeed = (finalSpeed * variation)*i;

    Serial.println(currentSpeed);
    if(side){
      MOTOR_SetSpeed(droite, currentSpeed);
      MOTOR_SetSpeed(gauche, -currentSpeed);
    }
    else{
      MOTOR_SetSpeed(droite, -currentSpeed);
      MOTOR_SetSpeed(gauche, currentSpeed);
    }
    delay(10);
  }
}

