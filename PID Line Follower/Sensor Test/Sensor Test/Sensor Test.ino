#include <RedBot.h>

int right_m = 0;
int right_c = 0;
int center = 0;
int left_c = 0;
int left_m = 0;
RedBotSensor left_sen = RedBotSensor(A0);   
RedBotSensor left_sen_c = RedBotSensor(A1);   
RedBotSensor center_sen = RedBotSensor(A2); 
RedBotSensor right_sen_c = RedBotSensor(A3);  
RedBotSensor right_sen = RedBotSensor(A4);  
int lineStandard = 800;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  if(center_sen.read() < lineStandard)
  {//right
   center = 1;
  }
  if(right_sen_c.read() < lineStandard)
  {//left
    right_c = 1;
  }
  //data_sheet
  // if the line is under the right sensor, adjust relative speeds to turn to the right
  if(right_sen.read() < lineStandard)
  {//left
  right_m = 1;
  }
  //data_sheet
  // if the line is under the left sensor, adjust relative speeds to turn to the left
  if(left_sen_c.read() < lineStandard)
  {//right
  left_c = 1;
  }
  if(left_sen.read() < lineStandard)
  {//right
  left_m = 1;
  }
  Serial.print(left_m);
  Serial.print(left_c);
  Serial.print(center);
  Serial.print(right_c);
  Serial.print(right_m);
  Serial.println();
  right_m = 0;
right_c = 0;
center = 0;
left_c = 0;
left_m = 0;

}
