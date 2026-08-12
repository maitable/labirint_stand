#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo servoX, servoY;

#define oled 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int startsensor = A1;
const int finishsensor = A0;
int start = 0;
int finish = 0;
const int joyXpin = A2, joyYpin = A3;
const int buzzer = 8;
const int sda_oled = A4;
const int scl_oled = A5;

const int posMin = 0, posMax = 180;
const int center = 512;
const int deadzone = 40;
const float speed = 1.20;

const int thresh = 120;
bool started = false;
bool win = false;
bool played_start = false;
bool win_start = false;

float posX = 80, posY = 80;
int lastWriteX = -1, lastWriteY = -1;

String state = "WELCOME";

unsigned long conditionTimer = 0;
unsigned long lastCheck = 0;
unsigned long lastDraw = 0;

int readAxis(int pin) {
  long sum = 0;
  for (int i = 0; i < 4; i++) sum += analogRead(pin);
  return sum / 4;
}

float axisVelocity(int raw, unsigned long dt, bool invert = false) {
  int offset = raw - center;
  if (abs(offset) < deadzone) return 0;
  float v = offset * speed / 100.0 * (dt / 15.0);
  return invert ? -v : v;
}

void writestate(String text) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print(text);
  display.setCursor(0, 50);
  display.print(conditionTimer / 1000);
  display.display();
}

void setup() {
  Serial.begin(115200);
  servoX.attach(9);
  servoY.attach(10);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Wire.setClock(400000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.print(state);
  display.display();

  lastCheck = millis();
}

void loop() {
  unsigned long now = millis();
  unsigned long delta = now - lastCheck;
  lastCheck = now;

  digitalWrite(buzzer, HIGH);
  start = analogRead(startsensor);
  finish = analogRead(finishsensor);

  if (start <= thresh) { started = true; win = false; state = "STARTED"; conditionTimer = 0; }
  if (finish <= thresh && started) { win = true; started = false; state = "FINISHED"; }
  if (start <= thresh || finish <= thresh) digitalWrite(buzzer, LOW);
  if (started && !win) conditionTimer += delta;

  int rawX = analogRead(joyXpin);
  int rawY = analogRead(joyYpin);

  posX += axisVelocity(rawX, delta, true);
  posY += axisVelocity(rawY, delta, true);

  posX = constrain(posX, posMin, posMax);
  posY = constrain(posY, posMin, posMax);

  int wx = (int)posX, wy = (int)posY;
  if (wx != lastWriteX) { servoX.write(wx); lastWriteX = wx; }
  if (wy != lastWriteY) { servoY.write(wy); lastWriteY = wy; }

  Serial.print("X: "); Serial.print(rawX);
  Serial.print(" Y: "); Serial.print(rawY);
  Serial.print(" Start: "); Serial.print(start);
  Serial.print(" Finish: "); Serial.print(finish);
  Serial.print(" Started? "); Serial.print(started);
  Serial.print(" Won? "); Serial.print(win);
  Serial.print(" Timer: "); Serial.println(conditionTimer / 1000);

  if (now - lastDraw >= 100) { writestate(state); lastDraw = now; }
}