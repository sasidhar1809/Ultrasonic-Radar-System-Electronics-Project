#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = 8;

long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(12);
}

void loop() {
  for (int i = 0; i <= 180; i++) {
    myServo.write(i);
    delay(10);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance <= 20) {
      siren(); /
    } else {
      digitalWrite(buzzerPin, LOW); 
    }
  }

  for (int i = 180; i > 0; i--) {
    myServo.write(i);
    delay(10);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance <= 20) {
      siren();
      digitalWrite(buzzerPin, LOW); 
    }
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void siren() {
  for (int i = 1000; i <= 2000; i += 100) { 
    tone(buzzerPin, i); 
    delay(10);
  }
  for (int i = 2000; i >= 1000; i -= 100) { 
    tone(buzzerPin, i); 
    delay(10);
  }
  noTone(buzzerPin);
}
