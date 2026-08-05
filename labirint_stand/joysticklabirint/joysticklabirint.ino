#include <Servo.h>
Servo servoX, servoY;

const int startsensor= A1;
const int finishsensor= A0;
int start = 0;
int finish = 0;
const int joyXpin = A2, joyYpin = A3;
const int buzzer = 8;
const int sda_oled = A4;
const int scl_oled  = A5;

const int posMin = 0, posMax = 160;
const int center = 512;
const int deadzone = 40;
const float speed = 0.40;

float posX = 80, posY = 80;    // start centered; use float for smooth accumulation
int lastWriteX = -1, lastWriteY = -1;

int readAxis(int pin) {
  long sum = 0;
  for (int i = 0; i < 4; i++) sum += analogRead(pin);
  return sum/4;
}

float axisVelocity(int raw) {
  int offset = raw - center;
  if (abs(offset) < deadzone) return 0;

  return offset * speed / 100.0;
}

void setup() {
  Serial.begin(9600);
  servoX.attach(9);
  servoY.attach(10);
}

void loop() {
  start = analogRead(startsensor);
  finish = analogRead(finishsensor);

  posX += axisVelocity(analogRead(joyXpin));
  posY += axisVelocity(analogRead(joyYpin));

  posX = constrain(posX, posMin, posMax);
  posY = constrain(posY, posMin, posMax);

  int wx = (int)posX, wy = (int)posY;
  if (wx != lastWriteX) { servoX.write(wx); lastWriteX = wx; }
  if (wy != lastWriteY) { servoY.write(wy); lastWriteY = wy; }

  Serial.print("X: "); Serial.print(analogRead(joyXpin));
  Serial.print(" Y: "); Serial.print(analogRead(joyYpin));
  Serial.print(" Start: "); Serial.print(start);
  Serial.print(" Finish: "); Serial.println(finish);

  delay(15);
}