/*created by Mostafa Zaghloul with a helper library called RedBot.h you can find 
 * it on this link https://github.com/sparkfun/RedBot 
 *--------------------------- thanks a million --------------------------------- 
 *you can find me on 
 *FaceBook::https://www.facebook.com/mostafa.zaghlol3
 *Twitter::https://twitter.com/Mostafazaghlul
 *to Contact for hardware or software questions 
 */
#include <RedBot.h>

//Straight Line Speed [0 --> 255]
int baseSpeedValue = 80;
//Max Speed [0 --> 255]
int maxSpeed = 170;
//Max reverse Speed [0 --> -255]
int reverseSpeed = -80;

int right_m, right_c, center, left_c, left_m = 0;

void right();
void Stop ();
void left();
void forward();
void back();

RedBotSensor left_sen = RedBotSensor(A0);   
RedBotSensor left_sen_c = RedBotSensor(A1);   
RedBotSensor center_sen = RedBotSensor(A2); 
RedBotSensor right_sen_c = RedBotSensor(A3);  
RedBotSensor right_sen = RedBotSensor(A4);  
//data_sheet
// constants that are used in the code. lineStandard is the level to detect 
// if the sensor is on the line or not. If the sensor value is greater than this
// the sensor is above a DARK line.
//
// SPEED sets the nominal speed
//motor A
#define en2 9
#define in3 8
#define in4 7
//motor b
#define en1 3
#define in1 5
#define in2 4
int lineStandard = 800;

//PID parameters
float Kp = 0.6;
float Ki = 0.0000;
float Kd = 0.0;

int lastError = 0;



void setup()
{ pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  Serial.begin(9600);
  Serial.println("IR Sensor Readings:: ");
  delay(1000);
}

void loop()
{
  // Serial.print(left_sen.read());
  // Serial.print("\t");  
  // Serial.print(center_sen.read());
  // Serial.print("\t"); 
  // Serial.print(right_sen.read());
  // Serial.println();
//data_sheet
  // if on the line drive left and right at the same speed (left is CCW / right is CW)
  if(center_sen.read() < lineStandard)
  {//right
   center = 1;
  }
  else if(right_sen_c.read() < lineStandard)
  {//left
    right_c = 1;
  }
  //data_sheet
  // if the line is under the right sensor, adjust relative speeds to turn to the right
  else if(right_sen.read() < lineStandard)
  {//left
  right_m = 1;
  }
  //data_sheet
  // if the line is under the left sensor, adjust relative speeds to turn to the left
  else if(left_sen_c.read() < lineStandard)
  {//right
  left_c = 1;
  }
  else if(left_sen.read() < lineStandard)
  {//right
  left_m = 1;
  }
  int num_of_sensors_on = right_m + right_c + center + left_c + left_m;
  int error = (center*0 + right_c *1000 + right_m *2000 + left_c*(-1000)+left_m*(-2000))/num_of_sensors_on;
  PID_control(error); 
  right_m, right_c, center, left_c, left_m = 0;
  delay(0);  // add a delay to decrease sensitivity.

}

void PID_control(int error){
  int P = error;
  int I = error + I;
  int D = error - lastError;
  lastError = error;

  int motorSpeedChange = P * Kp + I * Ki + D * Kp;
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
  Serial.print("Speed A:");
  Serial.print(speedA);
  Serial.print("          SpeedB:");
  Serial.print(speedB);
  Serial.println();
}



void right_rev() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 80);
  analogWrite(en2, 180);
  Serial.print("RIGHT");
}
void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 150);
  analogWrite(en2, 200);
  Serial.print("RIGHT");
}

void Stop () {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(en1, 0);
  analogWrite(en2, 0);

}
void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 200);
  analogWrite(en2, 150);
  Serial.print("LEFT");}
void left_rev() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(en1, 180);
  analogWrite(en2, 80);
  Serial.print("LEFT");
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 100);
  analogWrite(en2, 100);
}
void back(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(en1, 100);
  analogWrite(en2, 100);
}