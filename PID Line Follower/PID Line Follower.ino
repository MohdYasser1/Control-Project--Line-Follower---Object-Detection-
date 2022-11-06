#include <QTRSensors.h> //Does this work ??

QTRSensors qtr;
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

//Straight Line Speed
int baseSpeedValue = 150;

//Motor Driver Varible and Connections
int in1 = 8;
int in2 = 7;
int en1 = 9;
int in3 = 5;
int in4 = 4;
int en2 = 3;
/////

//PID parameters
int Kp = 0.07;
int Ki = 0;
int Kd = 0.7;

int lastError = 0;

void setup() {
  // put your setup code here, to run once:

  //Sensor pins
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4}, SensorCount);
  //////

  //Calibration mode 10-Seconds
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration
  //////////

  //Motor Driver Pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en2, OUTPUT);
  /////
}

void loop() {
  // put your main code here, to run repeatedly:

}

void PID_control(){
  //To get a position from (0 --> 4000)
  uint16_t positionLine = qtr.readLineBlack(sensorValues);

  int error = 2000 - positionLine; 

  int P = error;
  int I = error + I;
  int D = lastError - error;
  lastError = error;

  int motorSpeedChange = P * Kp + I * Ki + D * Kp;

  //Changing speed of both motor
  //Turning Left and Right
  int motorSpeedA = baseSpeedValue + motorSpeedChange;
  int motorSpeedB = baseSpeedValue + motorSpeedChange;

  if (motorSpeedA > 255){
    motorSpeedA = 255;
  }
  if (motorSpeedB > 255){
    motorSpeedB = 255;
  }
  if (motorSpeedA < -75){
    motorSpeedA = -75;
  }
  if (motorSpeedA < -75){
    motorSpeedA = -75;
  }
  forward_movement(motorSpeedA, motorSpeedB);
}

void forward_movement(int speedA, int speedB){
if (speedA < 0){ //If we want to reverse
  speedA = 0 - speedA;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
else{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

if (speedB < 0){//If we want to reverse
  speedB = 0 - speedB;
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
else{
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

  analogWrite(en1, speedA);

  analogWrite(en2, speedB);
}
