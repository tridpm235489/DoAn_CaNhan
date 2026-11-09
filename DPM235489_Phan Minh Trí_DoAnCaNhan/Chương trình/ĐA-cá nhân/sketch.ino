#include <ESP32Servo.h>

// ========== CHÂN ==========
const int trigMo    = 5;    // HC-SR04 mở nắp
const int echoMo    = 18;
const int trigDay   = 23;   // HC-SR04 thùng đầy
const int echoDay   = 22;
const int servoPin  = 19;
const int buzzerPin = 21;
const int ledXanh   = 2;    // Đang mở nắp
const int ledDo     = 4;    // Thùng đầy

// ========== ĐỐI TƯỢNG ==========
Servo napThung;

// ========== BIẾN ==========
bool dangMo = false;
unsigned long thoiGianMo = 0;
const int KHOANG_MO = 20;          // cm - mở nắp
const int KHOANG_DAY = 10;         // cm - coi là đầy
const int THOI_GIAN_GIU_MO = 3000; // 3 giây

// ========== HÀM ĐO KHOẢNG CÁCH ==========
float doKhoangCach(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 999;
  return duration * 0.0343 / 2;
}

void setup() {
  Serial.begin(115200);

  pinMode(trigMo, OUTPUT);
  pinMode(echoMo, INPUT);
  pinMode(trigDay, OUTPUT);
  pinMode(echoDay, INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledXanh, OUTPUT);
  pinMode(ledDo, OUTPUT);

  napThung.attach(servoPin);
  napThung.write(0);                // Nắp đóng lúc đầu

  digitalWrite(ledXanh, LOW);
  digitalWrite(ledDo, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.println("=================================");
  Serial.println("  THUNG RAC THONG MINH - ESP32");
  Serial.println("=================================");
}

void loop() {
  float kcMo  = doKhoangCach(trigMo, echoMo);
  float kcDay = doKhoangCach(trigDay, echoDay);

  // ===== THÙNG ĐẦY =====
  if (kcDay < KHOANG_DAY) {
    digitalWrite(ledDo, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("!!! THUNG RAC DAY !!!");
  } else {
    digitalWrite(ledDo, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  // ===== MỞ NẮP =====
  if (kcMo < KHOANG_MO && !dangMo) {
    Serial.println(">> MO NAP");
    napThung.write(90);
    digitalWrite(ledXanh, HIGH);
    dangMo = true;
    thoiGianMo = millis();
  }

  // ===== ĐÓNG NẮP =====
  if (dangMo && (millis() - thoiGianMo >= THOI_GIAN_GIU_MO)) {
    Serial.println(">> DONG NAP");
    napThung.write(0);
    digitalWrite(ledXanh, LOW);
    dangMo = false;
  }

  Serial.print("Mo nap: ");
  Serial.print(kcMo, 1);
  Serial.print(" cm | Day: ");
  Serial.print(kcDay, 1);
  Serial.println(" cm");

  delay(200);
}