#include <QTRSensors.h> //Does this work ??
QTRSensors qtr;

//Motor Driver Varible and Connections
int in1 = 8;
int in2 = 7;
int en1 = 9;
int in3 = 5;
int in4 = 4;
int en2 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT)
  pinMode(in2, OUTPUT)
  pinMode(en1, OUTPUT)
  pinMode(in3, OUTPUT)
  pinMode(in4, OUTPUT)
  pinMode(en2, OUTPUT)

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
