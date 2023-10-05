// librairies
#include <LibRobus.h>

const int gauche = 0;
const int droite = 1;
const int temps_lecture_ms = 2;

int countPulses = 0;
const float speed = 0.2;
uint8_t id_set_motors_speed;

bool state = false;


void set_motors_speed(uint8_t encoder);
void ramp_up(float finalSpeed, float variation, bool side);
void ramp_down(float finalSpeed, float variation);
void DC_Motor_Encoder();

void setup()
{
  // initialisation de RobUS et du port sériel à 9600 Bauds
  BoardInit();
  ENCODER_Reset(gauche);
  ENCODER_Reset(droite);
  SOFT_TIMER_SetCallback(id_set_motors_speed, *set_motors_speed);
  SOFT_TIMER_SetDelay(id_set_motors_speed,temps_lecture_ms);
  SOFT_TIMER_Enable(id_set_motors_speed);
  // exemple de remise à zéro du compteur
}

void loop()
{
  SOFT_TIMER_Update();
  if(ROBUS_IsBumper(2) && !state){
    state = true;
    
    ENCODER_Reset(gauche);
    ENCODER_Reset(droite);
    ramp_up(speed, 4, droite);
    Serial.println("ramp up done");
    MOTOR_SetSpeed(gauche, -speed);
    MOTOR_SetSpeed(droite, speed);
  };
  if(ROBUS_IsBumper(3) && !state){
    state = true;
    ENCODER_Reset(gauche);
    ENCODER_Reset(droite);
    ramp_up(speed, 4, gauche);
    Serial.println("ramp up done");
    MOTOR_SetSpeed(gauche, speed);
    MOTOR_SetSpeed(droite, -speed);

  }
}

void set_motors_speed(uint8_t encoder){
  int currentValueRight = ENCODER_Read(droite);
  int currentValueLeft = ENCODER_Read(gauche);
  if(currentValueRight >= 1950 || currentValueLeft >=1950){
    Serial.println(ENCODER_Read(gauche)); 
    MOTOR_SetSpeed(gauche, 0);
    MOTOR_SetSpeed(droite, 0);
   /*
    ramp_down(speed, 4);
   */
    Serial.println(ENCODER_Read(gauche));
    ENCODER_Reset(gauche);
    ENCODER_Reset(droite);
    Serial.println("on arrete!!!!!!!!!!");
    state= false;
  }
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

void ramp_down(float finalSpeed, float variation){
  float currentSpeed = 0;
  for (float i = 0; currentSpeed >= 0; i=i+0.01)
  {
    currentSpeed = -(variation * finalSpeed)*i + finalSpeed;
    Serial.println(currentSpeed);
    Serial.println(finalSpeed);
    Serial.println(i);

    MOTOR_SetSpeed(droite, currentSpeed);
    MOTOR_SetSpeed(gauche, -currentSpeed);
    delay(10);
  }
}
