#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

/* ================== CONFIGURATION ================== */
#define BOT_TOKEN "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID   "YOUR_TELEGRAM_CHAT_ID"

WiFiMulti wifiMulti;
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

/* ================== PIN DEFINITIONS ================== */
const int pirPin    = 23;
const int doorPin   = 14;
const int flamePin  = 25;
const int gasPin    = 4;
const int soundPin  = 35;
const int buzzerPin = 27;

#define SOUND_THRESHOLD 2300

/* ================== LCD SETUP ================== */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ================== TIMING ================== */
unsigned long lastWiFiCheck = 0;

void setup() {
  Serial.begin(115200);

  // Initialize Pins
  pinMode(pirPin, INPUT_PULLDOWN);
  pinMode(doorPin, INPUT_PULLUP);
  pinMode(flamePin, INPUT_PULLDOWN);
  pinMode(gasPin, INPUT_PULLDOWN);
  pinMode(soundPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Initialize LCD
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("System Starting");
  delay(1000);
  lcd.clear();

  /* -------- WiFi Setup -------- */
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("YOUR_WIFI_SSID_1", "YOUR_WIFI_PASSWORD_1");
  wifiMulti.addAP("YOUR_WIFI_SSID_2", "YOUR_WIFI_PASSWORD_2");

  Serial.println("Connecting to WiFi...");

  unsigned long startAttemptTime = millis();
  while (wifiMulti.run() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected");
    lcd.print("WiFi Connected");
  } else {
    Serial.println("\nWiFi Failed");
    lcd.print("WiFi Failed");
  }

  client.setInsecure();
  delay(1000);
  lcd.clear();
}

void loop() {
  // Keep WiFi connection alive
  if (millis() - lastWiFiCheck > 5000) {
    wifiMulti.run();
    lastWiFiCheck = millis();
  }

  bool isAlert = false;

  /* -------- PIR SENSOR -------- */
  if (digitalRead(pirPin) == HIGH) {
    isAlert = true;
    if (WiFi.status() == WL_CONNECTED)
      bot.sendMessage(CHAT_ID, "🚶 Alert: PIR Motion Detected!", "");
  }

  /* -------- DOOR SENSOR -------- */
  if (digitalRead(doorPin) == HIGH) {
    isAlert = true;
    if (WiFi.status() == WL_CONNECTED)
      bot.sendMessage(CHAT_ID, "🚪 Alert: Door Opened!", "");
  }

  /* -------- FLAME SENSOR -------- */
  if (digitalRead(flamePin) == HIGH) {
    isAlert = true;
    if (WiFi.status() == WL_CONNECTED)
      bot.sendMessage(CHAT_ID, "🔥 Alert: Flame Detected!", "");
  }

  /* -------- GAS SENSOR -------- */
  if (digitalRead(gasPin) == HIGH) {
    isAlert = true;
    if (WiFi.status() == WL_CONNECTED)
      bot.sendMessage(CHAT_ID, "💨 Alert: Gas Leak Detected!", "");
  }

  /* -------- SOUND SENSOR -------- */
  if (analogRead(soundPin) > SOUND_THRESHOLD) {
    isAlert = true;
    if (WiFi.status() == WL_CONNECTED)
      bot.sendMessage(CHAT_ID, "🔊 Alert: High Noise Level!", "");
  }

  // Trigger Buzzer if any sensor is active
  if (isAlert) {
    digitalWrite(buzzerPin, HIGH);
    delay(1500);
    digitalWrite(buzzerPin, LOW);
  }

  /* -------- LCD UPDATE -------- */
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P:"); lcd.print(digitalRead(pirPin) ? "Y " : "N ");
  lcd.print("D:"); lcd.print(digitalRead(doorPin) ? "Y " : "N ");
  lcd.print("F:"); lcd.print(digitalRead(flamePin) ? "Y" : "N");

  lcd.setCursor(0, 1);
  lcd.print("G:"); lcd.print(digitalRead(gasPin) ? "Y " : "N ");
  lcd.print("S:"); lcd.print(analogRead(soundPin) > SOUND_THRESHOLD ? "Y" : "N");

  delay(300);
}
