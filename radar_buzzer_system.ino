#include <Servo.h>
#include <LiquidCrystal.h>
const int buzzer = 8;
int trigPin = 7; int echoPin = 6; long duration; int distance; Servo servo;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzer, HIGH);
  servo.attach(9);
  lcd.begin(16, 2);
}

void loop() {
  left();
  right();
}

void left() {

  for (int pos = 0; pos <= 180; pos += 1) {
    distance = echoloop();
    lcd.clear();
    if (distance < 175) {
      lcd.setCursor(0, 0);
      lcd.print("distance");
      lcd.setCursor(9, 0);
      lcd.print(distance);
      lcd.setCursor(14, 0);
      lcd.print("cm");
      lcd.setCursor(0, 1);
      lcd.print("Angle");
      lcd.setCursor(6, 1);
      lcd.print(pos);
      lcd.setCursor(10, 1);
      lcd.print("degree");
    }
    if (distance < 50) {
      tone(buzzer, 500);
      delay(250);
      noTone(buzzer);
      delay(250);

      tone(buzzer, 500);
      delay(250);
      noTone(buzzer);
      delay(250);
    }
    else {
      servo.write(pos);
      Serial.print(distance);
      Serial.print(" ");
    }
    digitalWrite(buzzer, HIGH);
    Serial.println(distance);
    delay(50);
  }
}

void right() {
  for (int pos = 180; pos >= 0; pos -= 1) {
    distance = echoloop();
    lcd.clear();
    if (distance < 175) {
      lcd.setCursor(0, 0);
      lcd.print("distance");
      lcd.setCursor(9, 0);

      lcd.print(distance);
      lcd.setCursor(14, 0);
      lcd.print("cm");
      lcd.setCursor(0, 1);
      lcd.print("Angle");
      lcd.setCursor(6, 1);
      lcd.print(pos);
      lcd.setCursor(10, 1);
      lcd.print("degree");
    }
    if (distance < 50) {
      tone(buzzer, 500);
      delay(250);
      noTone(buzzer);
      delay(250);
      tone(buzzer, 500);
      delay(250);
      noTone(buzzer);
      delay(250);
    }
    else {
      servo.write(pos);

      Serial.print(distance);
    }
    digitalWrite(buzzer, HIGH);
    Serial.println(distance);
    delay(50);
  }
}

int echoloop() {
  long duration, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = duration / 29 / 2;
  return cm;
}
