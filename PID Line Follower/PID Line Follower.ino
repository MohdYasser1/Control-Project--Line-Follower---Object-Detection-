#include <QTRSensors.h> //Does this work ??

QTRSensors qtr;
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

//Straight Line Speed [0 --> 255]
int baseSpeedValue = 100;
//Max Speed [0 --> 255]
int maxSpeed = 90;
//Max reverse Speed [0 --> -255]
int reverseSpeed = -80;

//Motor Driver Varible and Connections
int in3 = 8;
int in4 = 7;
int en2 = 9;
int in1 = 5;
int in2 = 4;
int en1 = 3;
/////

//PID parameters
float Kp = 0.5;
float Ki = 0.0000;
float Kd = 0.0;

int lastError = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(en1, LOW);
  analogWrite(en2, LOW);
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Sensor pins
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4}, SensorCount);
  //////

  //Calibration mode 10-Seconds
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration
  //////////

  //   // print the calibration minimum values measured when emitters were on
  // Serial.begin(9600);
  // for (uint8_t i = 0; i < SensorCount; i++)
  // {
  //   Serial.print(qtr.calibrationOn.minimum[i]);
  //   Serial.print(' ');
  // }
  // Serial.println();

  // // print the calibration maximum values measured when emitters were on
  // for (uint8_t i = 0; i < SensorCount; i++)
  // {
  //   Serial.print(qtr.calibrationOn.maximum[i]);
  //   Serial.print(' ');
  // }
  // Serial.println();
  // Serial.println();
  delay(1000);



  //Motor Driver Pins
  /////
}

void loop() {
  
    // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 5000 (for a white line, use readLineWhite() instead)
  // uint16_t position = qtr.readLineBlack(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line
  // position
  // for (uint8_t i = 0; i < SensorCount; i++)
  // {
  //   Serial.print(sensorValues[i]);
  //   Serial.print('\t');
  // }
  // Serial.println(position);

  delay(250);

  // put your main code here, to run repeatedly:
  PID_control();
  // Serial.print(qtr.readLineBlack(sensorValues));

}

void PID_control(){
  //To get a position from (0 --> 4000)
  uint16_t positionLine = qtr.readLineBlack(sensorValues);
  // Serial.print(qtr.readLineBlack(sensorValues));
  // Serial.println();

  int formula = 4*positionLine -6000;
  // Serial.print(formula);
  // Serial.println();
  int error = 2000 - formula; 
  // Serial.print(error);
  // Serial.println();
  int P = error;
  int I = error + I;
  int D = error - lastError;
  lastError = error;

  int motorSpeedChange = P * Kp + I * Ki + D * Kd;

  //Changing speed of both motor
  //Turning Left and Right
  int motorSpeedA = baseSpeedValue + motorSpeedChange;
  int motorSpeedB = baseSpeedValue - motorSpeedChange;

  if (motorSpeedA > maxSpeed){
    motorSpeedA = maxSpeed;
  }
  if (motorSpeedB > maxSpeed){
    motorSpeedB = maxSpeed;
  }
  if (motorSpeedA < reverseSpeed){
    motorSpeedA = reverseSpeed;
  }
  if (motorSpeedB < reverseSpeed){
    motorSpeedB = reverseSpeed;
  }
  // Serial.println(motorSpeedA);
  // Serial.println(motorSpeedB);
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
