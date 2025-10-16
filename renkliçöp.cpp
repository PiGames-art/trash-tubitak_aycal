#include <Servo.h>

// --- Renk sensörü (TCS3200) pinleri ---
const int S0 = 4;
const int S1 = 5;
const int S2 = 6;
const int S3 = 7;
const int sensorOut = 2; // Düzeltildi: echoPin ile çakışmaması için

int redFrequency, greenFrequency, blueFrequency;

// --- Servo motorlar ---
Servo servo1;
Servo servo2;
const int servo1Pin = 10; // Düzeltildi
const int servo2Pin = 11; // Düzeltildi

// --- Ultrasonik sensör ---
const int trigPin = 9;
const int echoPin = 8;

// --- Servo açıları ---
int servo1Normal = 0;
int servo2Normal = 0;
int servo1Aktif = 90;
int servo2Aktif = 90;

// --- Mesafe eşiği (cm) ---
const int VarsayilanMesafe = 20;

void setup() {
  // Renk sensörü pinleri
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Frekans ölçeği %20
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);

  // Ultrasonik pin yönleri
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servoları başlat
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo1.write(servo1Normal);
  servo2.write(servo2Normal);
}

void loop() {
  // --- Renk oku ---
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);

  int mesafe = uzaklikOlc();

  // --- Şart kontrolü ---
  if (redFrequency < 30 && greenFrequency < 30 && blueFrequency < 30 && mesafe > 0 && mesafe < VarsayilanMesafe) {
    servo1.write(servo1Aktif);
  servo2.write(servo2Aktif);
    } else {
      servo1.write(servo1Normal);
      servo2.write(servo2Normal);
    }

    delay(200);
}

// --- Mesafe ölçüm fonksiyonu ---
int uzaklikOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long vakit = pulseIn(echoPin, HIGH);
  int mesafe = vakit * 0.034 / 2;
  return mesafe;
}
