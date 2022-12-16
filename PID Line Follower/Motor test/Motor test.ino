int in1 = 8;
int in2 = 7;
int en1 = 9;
int in3 = 5;
int in4 = 4;
int en2 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en2, OUTPUT);
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, LOW);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, LOW);
  // analogWrite(en1, LOW);
  // analogWrite(en2, LOW);
  // digitalWrite(13, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(en1, 200);
  analogWrite(en2, 200);

}
