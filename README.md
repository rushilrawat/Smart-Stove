# 🍳 Smart Stove – Arduino-Powered Safe Cooking Assistant

[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue?logo=arduino)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language: C++](https://img.shields.io/badge/Made%20with-C++-brightgreen)](https://www.arduino.cc/reference/en/)

**Smart Stove** is an Arduino-based system designed to enhance kitchen safety by combining real-time cooking control with built-in hazard detection.  
It automates stove operation with sensor-based decision-making and alerts, making cooking safer, smarter, and stress-free.

Originally built in 2019, 8th grade by [Rushil Rawat](https://github.com/rushilrawat) and [Arghya Shubhshiv](https://github.com/ArghyaShubhshiv), it has since been upgraded several times for real-world use.

---

## 🧠 Features

- 🔥 **Stove Knob Automation** using Servo Motor
- 📟 **LCD Display** shows temperature, mode, and countdown timer
- 📦 **3 Cooking Modes**: Fast (10s), Medium (20s), Slow (30s)
- 📥 **EEPROM Memory** retains last mode after restart
- ⏱️ **Real-Time Countdown Display** (MM:SS format)
- 🔁 **Extend Timer** mid-cooking via button press (+10s each time)
- 🔊 **Buzzer Alerts** during last 5 seconds of cooking
- 🥛 **Milk Overflow Detection** via Ultrasonic Sensor
- 🌡️ **Overheat Monitoring** with LM35
- 💨 **Smoke and Gas Leak Detection** with MQ Sensors
- 🧱 **Modular and Commented Code** for easy customization

---

## 🛠️ Hardware Components

| Component              | Pin Used         | Function                           |
|------------------------|------------------|------------------------------------|
| Arduino Uno/Nano       | —                | Main controller                    |
| Servo Motor (SG90)     | D13              | Rotates stove knob                 |
| HC-SR04 Ultrasonic     | TRIG: D11, ECHO: D12 | Milk overflow detection        |
| LM35 Temp Sensor       | A0               | Cooking temperature monitor        |
| MQ-2 Gas Sensor        | A1               | Detects gas leakage                |
| MQ-7 Smoke Sensor      | A2               | Detects smoke                     |
| Push Button            | D9               | Cooking mode selector / extender  |
| Buzzer                 | D8               | Alerts and feedback                |
| 16x2 LCD (I2C)         | SDA/SCL          | Real-time info display             |
| EEPROM (built-in)      | —                | Saves last used mode              |

---

## 📚 Libraries Required

- [`LiquidCrystal_I2C.h`](https://github.com/johnrickman/LiquidCrystal_I2C)
- [`Servo.h`](https://www.arduino.cc/reference/en/libraries/servo/) 
- [`EEPROM.h`](https://www.arduino.cc/en/Reference/EEPROM)

---

## 🔌 Wiring Overview

- Connect LM35 to A0 (Vout → A0, VCC → 5V, GND)
- MQ-2 → A1, MQ-7 → A2
- Servo signal → D13, powered by 5V
- Button → D9 with internal pull-up
- Buzzer → D8
- HC-SR04: TRIG → D11, ECHO → D12
- LCD I2C: SDA → A4, SCL → A5 (Uno/Nano default)

---

## 🚀 Setup Instructions

1. **Connect Components**  
   Wire all sensors, button, LCD, servo, and buzzer according to the table above.

2. **Upload Code**  
   - Open `Smart_Stove.ino` in the Arduino IDE.  
   - Select your board (e.g., Uno or Nano).  
   - Upload and open Serial Monitor (optional for debugging).

3. **How to Use**  
   - On power-up, system displays last used cooking mode.  
   - Press button to cycle: OFF → FAST → MEDIUM → SLOW  
   - Cooking starts automatically based on mode  
   - LCD shows real-time temperature and countdown  
   - Press and hold button during cooking to add +10s  
   - Final 5 seconds: buzzer beeps every second  
   - If temp > 120°C, smoke or gas detected, or milk spills → Emergency shutoff

---

## 🧪 Safety Monitoring Logic

| Condition           | Sensor        | Triggered If             | Action            |
|--------------------|---------------|--------------------------|-------------------|
| Milk Overflow       | Ultrasonic    | Distance < 10cm          | Beep + Warning    |
| Overheat            | LM35 (A0)     | Temp > 120°C             | Shut off stove    |
| Gas Leak            | MQ-2 (A1)     | Analog > 400             | Shut off + alert  |
| Smoke Detected      | MQ-7 (A2)     | Analog > 400             | Shut off + alert  |

---

## 🧠 EEPROM Functionality

- Saves last selected cooking mode (FAST, MEDIUM, etc.)
- Automatically restores it on restart
- Eliminates need to re-select every time

---

## 📈 Cooking Modes

| Mode     | Time  | Ideal For                  |
|----------|-------|----------------------------|
| FAST     | 10s   | Quick boiling, steaming    |
| MEDIUM   | 20s   | Light cooking              |
| SLOW     | 30s   | Frying or longer heating   |

---

## 🛠️ Future Enhancements

- 🔋 Add battery-powered real-time clock (RTC)
- 📲 WiFi-based phone alerts for smoke/gas
- 📊 SD card logging of all cooking/safety events
- 🔒 Dual-button lockout for children

---

## 👨‍🔧 Authors & Credits

- [Rushil Rawat](https://github.com/RushilRawat)  
- [Arghya Shubhshiv](https://github.com/ArghyaShubhshiv) 
- Special thanks to **Shivam Sir** and **ATL Lab DPS Noida** for mentorship and support

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
