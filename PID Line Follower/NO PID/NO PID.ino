/*created by Mostafa Zaghloul with a helper library called RedBot.h you can find 
 * it on this link https://github.com/sparkfun/RedBot 
 *--------------------------- thanks a million --------------------------------- 
 *you can find me on 
 *FaceBook::https://www.facebook.com/mostafa.zaghlol3
 *Twitter::https://twitter.com/Mostafazaghlul
 *to Contact for hardware or software questions 
 */
#include <RedBot.h>
#include <Ultrasonic.h>

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

Ultrasonic ultrasonic (12, 13);



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
   forward();
  }
  else if(right_sen.read() < lineStandard)
  {//left
  left_rev_max();
  }
  else if(right_sen_c.read() < lineStandard)
  {//left
  left_rev();
  }
  //data_sheet
  // if the line is under the right sensor, adjust relative speeds to turn to the right
  //data_sheet
  // if the line is under the left sensor, adjust relative speeds to turn to the left
  else if(left_sen.read() < lineStandard)
  {//right
  right_rev_max();
  }

  else if(left_sen_c.read() < lineStandard)
  {//right
  right_rev();
  }
  //data_sheet
  // if all sensors are on black or up in the air, stop the motors.
  // otherwise, run motors given the control speeds above.
  if((left_sen.read() < lineStandard) && (center_sen.read() < lineStandard) && (right_sen.read() < lineStandard) )
  {
    //stop
    Stop ();
  }
  else
  {
  //any dir
    forward();
  }
  delay(0);  // add a delay to decrease sensitivity.
}

void right_rev() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 120);
  analogWrite(en2, 120);
  Serial.print("RIGHT");
  Serial.println();
}
void right_rev_max() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 150);
  analogWrite(en2, 120);
  Serial.print("RIGHT");
  Serial.println();
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 0);
  analogWrite(en2, 80);
  Serial.print("RIGHT");
  Serial.println();
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
  analogWrite(en1, 80);
  analogWrite(en2, 0);
  Serial.print("LEFT");
  Serial.println();
}
void left_rev() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(en1, 120);
  analogWrite(en2, 120);
  Serial.print("LEFT");
  Serial.println();
}
void left_rev_max() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(en1, 120);
  analogWrite(en2, 150);
  Serial.print("LEFT");
  Serial.println();
}


void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 80);
  analogWrite(en2, 80);
}
void back(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(en1, 100);
  analogWrite(en2, 100);
}