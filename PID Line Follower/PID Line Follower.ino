#include <QTRSensors.h> //Does this work ??

QTRSensors qtr;
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

//Motor Driver Varible and Connections
int in1 = 8;
int in2 = 7;
int en1 = 9;
int in3 = 5;
int in4 = 4;
int en2 = 3;

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
  pinMode(in1, OUTPUT)
  pinMode(in2, OUTPUT)
  pinMode(en1, OUTPUT)
  pinMode(in3, OUTPUT)
  pinMode(in4, OUTPUT)
  pinMode(en2, OUTPUT)
  /////
}

void loop() {
  // put your main code here, to run repeatedly:

}

void forward_movement(int speedA, speedB){
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
