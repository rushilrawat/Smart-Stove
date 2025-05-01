# 🔥 Smart Stove - Arduino-Based Intelligent Cooking System

An Arduino-powered Smart Stove that makes your cooking safer and smarter with sensors for temperature, gas, smoke, and milk overflow detection — designed and originally built by Rushil Rawat and Arghya Shubhshiv in 8th grade, now upgraded for modern kitchens. Special Thanks to Shivan Sir who helped us with the initial code back in 2019.

---

## 🍲 Smart-Stove  
**An Automation in Our Daily Lives, in Food**

A Smart Stove project to automate the process of our most important need: **Food.**  
Created by: **Rush Rawat** and **Arghya**

### 🌱 Humble Beginnings  
The first version was made in **August 2019** during an interschool event, where we demonstrated it live and won **first prize**. It was one of our **first robotics competitions back in 8th grade**.  
Since then, we’ve won several awards — but this stove still remains very close to our hearts.  

### 🙏 Special Thanks  
We’d like to thank **Shivam Sir** for his guidance and support, and the **ATL Lab of DPS Noida** for fostering innovation.  

- 👨‍💻 Rushil Rawat: [GitHub Profile](https://github.com/RushilRawat/)  
- 👨‍💻 Arghya Shubhshiv: [GitHub Profile](https://github.com/ArghyaShubhshiv/)  

---

## 🚀 Features

- 🥛 **Milk Overflow Detection** (Ultrasonic Sensor)
- 🌡️ **Overheat Protection** (LM35 Temp Sensor)
- 💨 **Smoke Detection** (MQ-7 Sensor)
- 🧪 **Gas Leak Detection** (MQ-2 Sensor)
- 🔊 **Buzzer Alarms** for critical events
- 🔁 **3 Cooking Modes** (Fast, Medium, Slow) via Button
- ⏰ **Auto Shutoff Timer**
- 📟 **LCD Display** shows temperature, mode, and alerts
- 🔐 **Servo-Controlled Knob** for switching stove ON/OFF
- 💾 **EEPROM Support** (Future ready)

---

## 🧰 Hardware Components

| Component              | Description                         |
|------------------------|-------------------------------------|
| Arduino Uno/Nano       | Main controller                     |
| Servo Motor (SG90)     | Controls stove knob                 |
| HC-SR04                | Ultrasonic sensor for milk          |
| LM35                   | Temperature sensor                  |
| MQ-2                   | Gas leak detector                   |
| MQ-7                   | Smoke detector                      |
| 16x2 LCD (I2C)         | Real-time status display            |
| Buzzer                 | Alert system                        |
| Pushbutton             | Switch between cooking modes        |
| LEDs (Optional)        | Visual indicators (Red/Green)       |
| Jumper wires, breadboard, power supply |

---

## 📷 Images

> 📸 

---

## 🗂️ File Structure

```
Smart_Stove/
├── Smart_Stove.ino Arduino code
├── README.md # This file
├── schematic.png # Wiring diagram (Fritzing)
├── images/ # Prototype pictures
```


---

## 🛠️ Setup Instructions

1. **Wiring**:
   - Follow the `schematic.png` or wiring table above.
   - Connect all sensors and modules to the correct pins.

2. **Upload**:
   - Open `Smart_Stove.ino` in Arduino IDE.
   - Choose your board (e.g., Arduino Uno).
   - Upload and power on.

3. **Operate**:
   - Press button to cycle through modes.
   - Stove turns off automatically based on timer or alerts.

---

## 📦 Future Improvements

- 🔋 RTC module for clock-based cooking
- 📱 Bluetooth or WiFi alerts via phone
- 📈 Data logging to SD card or cloud
- 🗣️ Voice alerts using DFPlayer

---

## 📜 License

This project is licensed under the MIT License.

