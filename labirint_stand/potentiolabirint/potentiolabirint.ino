#include <Servo.h>
Servo servo1;  // create Servo object to control a servo
Servo servo2;
int pot1pin = A3;  // analog pin used to connect the potentiometer
int pot2pin = A4;

int last1 = 0, last2 = 0, min1 =0, min2=0,max1=160,max2=160;
int deadband = 2;
int deadband2 = 2;
void setup() {
  Serial.begin(9600);
  servo1.attach(9);  // attaches the servo on pin 9 to the Servo object
  servo2.attach(10);

}

int readPot(int pin) {
  int sum = 0;
  for (int i = 1; i <= 4; i++) sum += analogRead(pin);
  return sum / 4;
}

void loop() {
  int p1 = map(readPot(pot1pin), 0, 1023, min1, max1);
  int p2 = map(readPot(pot2pin), 0, 1023, min2, max2);

  if (abs(p1 - last1) > deadband) { servo1.write(p1); last1 = p1; }
  if (abs(p2 - last2) > deadband2) { servo2.write(p2); last2 = p2; }
  

  // Serial.print("poz 1: ");
  // Serial.print(p1);
  // Serial.print(" Poz 2: ");
  // Serial.print(p2);
  // Serial.println(" ");
}
//miau