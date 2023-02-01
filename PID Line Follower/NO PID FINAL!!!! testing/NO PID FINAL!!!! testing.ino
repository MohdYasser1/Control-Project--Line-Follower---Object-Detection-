#include <RedBot.h>
#include <Ultrasonic.h>


int right_c = 0;
int center = 0;
int left_c = 0;
int left_m = 0;

void right();
void Stop ();
void left();
void forward();
void back();
void left_rev_m();
void turn_obs(int distance);
void left_t();
void right_t();
void forward_t();


void turn_obs(int distance);

//Straight Line Speed [0 --> 255]
int baseSpeedValue = 70;
//Max Speed [0 --> 255]
int maxSpeed = 85;
//Max reverse Speed [0 --> -255]
int reverseSpeed = -165;

RedBotSensor left_sen = RedBotSensor(A0);   

RedBotSensor left_sen_c = RedBotSensor(A1);   
RedBotSensor center_sen = RedBotSensor(A2); 
RedBotSensor right_sen_c = RedBotSensor(A3);


#define en2 9
#define in3 8
#define in4 7
//motor b
#define en1 3
#define in1 5
#define in2 4
int lineStandard = 800;

float Kp = 0.095;
float Ki = 0;
float Kd = 0;
int lastError = 0;


// TRIGGER = 12
// ECHO = 13
Ultrasonic ultrasonic (12, 13);
int distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  Serial.println("IR Sensor Readings:: ");
  delay(1000);

}

void loop() {
  distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  if(distance == 0){
    distance = 100;
  }
  Serial.println(distance);

  if(distance <= 20){
    turn();
  }

  // put your main code here, to run repeatedly:
  if(left_sen_c.read() < lineStandard && right_sen_c.read() < lineStandard && center_sen.read() < lineStandard)
  {//right
    center = 1;
    right_c = 1;
    left_c = 1;
    forward();
  }
  else if(left_sen_c.read() < lineStandard && center_sen.read() < lineStandard)
  {//right
    center = 1;
    right_c = 0;
    left_c = 1;
    right();
  }
  else if(right_sen_c.read() < lineStandard && center_sen.read() < lineStandard)
  {//right
    center = 1;
    right_c = 1;
    left_c = 0;
    left();
  }
  else if(left_sen_c.read() < lineStandard)
  {//right
    center = 0;
    right_c = 0;
    left_c = 1;
    right_rev();
  }
  else if(right_sen_c.read() < lineStandard)
  {//left
    center = 0;
    right_c = 1;
    left_c = 0;
    left_rev();
  }
  else if(center_sen.read() < lineStandard)
  {//right
    center = 1;
    right_c = 0;
    left_c = 0;
    forward();
  }
  else if(left_sen.read() < lineStandard)
  {//right
    center = 0;
    right_c = 0;
    left_c = 0;
    left_m = 1;
    right_rev();
  }

  //data_sheet
  // if the line is under the right sensor, adjust relative speeds to turn to the right
  // if(right_sen.read() < lineStandard)
  // {//left
  // right_m = 1;
  // }
  //data_sheet
  // if the line is under the left sensor, adjust relative speeds to turn to the left
  // if(left_sen.read() < lineStandard)
  // {//right
  // left_m = 1;
  // }
  // int num_of_sensors_on = right_m + right_c + center + left_c + left_m;
  int num_of_sensors_on = right_c + center + left_c;
  int error = (center*0 + right_c *1000  + left_c*(-1000))/num_of_sensors_on;
    // PID_control(error); 
  delay(0);  // add a delay to decrease sensitivity.


}
void PID_control(int error){
  int P = error;
  int I = error + I;
  int D = error - lastError;
  lastError = error;

  int motorSpeedChange = P * Kp + I * Ki + D * Kd;
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
///////////////////////////////////////////////////////////////////////// HERE WE GO 

void right_rev() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 80); ////rev1
  analogWrite(en2, 80);////fwd1
  Serial.print("RIGHT");
}
void left_rev() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(en1, 80);///fwd2
  analogWrite(en2, 80);//rev2
  Serial.print("LEFT");
}
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 85);//fwd_base
  analogWrite(en2, 85);//fwd_base
}
void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 100);//speedup1
  analogWrite(en2, 65);//speeddwn1
  Serial.print("RIGHT");
}
void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 65);//speeddwn2
  analogWrite(en2, 100);//speedup2
  Serial.print("LEFT");
}
///////////////////////////////////////////////////////////////////////////////////////
void left_rev_m() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(en1, 80);
  analogWrite(en2, 150);
  Serial.print("LEFT");
}
void turn_obs(int distance){
  if(distance <= 10){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(en1, 80);
      analogWrite(en2, 200);
     delay(10000);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(en1, 200);
      analogWrite(en2, 80);
      delay(10000);
  }
}
void turn(){
  Serial.println("turn Right");
  left_t();
  delay(150);
  forward_t();
  delay(500);
  right_t();
  delay(500);
  while (right_sen_c.read() >= lineStandard && center_sen.read() >= lineStandard && left_sen_c.read() >= lineStandard && left_sen.read() >= lineStandard){
    forward();
  }
}
void left_t() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(en1, 200);
  analogWrite(en2, 200);
  Serial.print("LEFT");}
void right_t() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 200);
  analogWrite(en2, 200);
  Serial.print("RIGHT");
}
void forward_t() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 200);
  analogWrite(en2, 200);
}




