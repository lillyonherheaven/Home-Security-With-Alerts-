![Banner](home%20security%20banner.jpeg)
# 🏠 Smart Home Security System (ESP32)

An integrated home security system based on the **ESP32** microcontroller. It monitors the home environment using multiple sensors and sends real-time alerts via **Telegram**.

## 🚀 Features
* **Instant Alerts:** Sends Telegram notifications immediately when a threat is detected.
* **Comprehensive Monitoring:** Tracks motion, door status, fire, gas leaks, and loud noises.
* **Local Display:** 16x2 LCD screen showing the real-time status of all sensors.
* **Audible Alarm:** An active buzzer triggers automatically during any security breach.
* **Multi-Network Support:** Uses `WiFiMulti` to connect to multiple pre-configured networks for maximum uptime.

## 🛠 Hardware Components
* **Microcontroller:** ESP32
* **Display:** LCD I2C (16x2)
* **Sensors:**
  * **PIR Motion Sensor:** For movement detection.
  * **Magnetic Reed Switch:** For door/window monitoring.
  * **Flame Sensor:** For fire detection.
  * **MQ Gas Sensor:** For gas leak detection.
  * **Sound Sensor:** For high-noise or breaking-glass detection.
* **Alarm:** Active Buzzer.

## 🔌 Pinout Configuration
| Component | ESP32 Pin |
|-----------|-----------|
| PIR Sensor| GPIO 23    |
| Door Pin  | GPIO 14    |
| Flame Pin | GPIO 25    |
| Gas Pin   | GPIO 4     |
| Sound Pin | GPIO 35    |
| Buzzer    | GPIO 27    |
| LCD SDA   | GPIO 21    |
| LCD SCL   | GPIO 22    |

## 💻 Setup & Installation
1. Install the following libraries in Arduino IDE or PlatformIO:
   * `UniversalTelegramBot`
   * `LiquidCrystal_I2C`
   * `WiFi` & `WiFiClientSecure`
2. Open the `main.cpp` or `.ino` file.
3. Replace `YOUR_TELEGRAM_BOT_TOKEN` and `YOUR_TELEGRAM_CHAT_ID` with your actual credentials.
4. Add your WiFi credentials in the `wifiMulti.addAP` function.
5. Upload the code to your ESP32 board.
![Final Project Shape](final%20project%20shape.jpeg)
