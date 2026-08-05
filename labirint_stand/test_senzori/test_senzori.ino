
const int startsensor = A1;
const int finishsensor = A0;

int start = 0;
int finish = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  start = analogRead(startsensor);
  finish = analogRead(finishsensor);
  Serial.print("Start: ");
  Serial.print(start);
  Serial.print(" Finish: ");
  Serial.println(finish);
  delay(100);
}
