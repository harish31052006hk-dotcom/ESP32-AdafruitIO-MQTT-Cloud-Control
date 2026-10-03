# ESP32 Adafruit IO Cloud Control

### Task 2 — MQTT Cloud Dashboard with Relay Control

> A cloud-connected IoT automation project controlling a high-voltage AC bulb using an ESP32, Adafruit IO, and MQTT via a relay module.

---

## 📌 Overview
Moving beyond local HTTP servers, this project utilizes a cloud-based MQTT broker (Adafruit IO) to enable global remote control of an AC bulb. The ESP32 subscribes to a specific cloud feed and triggers an electromechanical relay on GPIO 23 to switch high voltage securely.

## 🎯 Objectives
- Establish an MQTT connection between the ESP32 and Adafruit IO.
- Subscribe to the `bulb-control` feed.
- Process incoming MQTT payloads ("ON", "OFF", "1", "0").
- Safely trigger a 5V relay module via GPIO 23 to control a 230V AC bulb.

## 🧠 Concepts Covered
- Cloud Computing in IoT
- Publish/Subscribe Architecture
- MQTT Protocol (Port 1883)
- Adafruit IO Dashboards
- Electromechanical Relays and High Voltage Isolation

## 🏗️ System Architecture
1. **Cloud Interface**: Adafruit IO Dashboard toggle switch.
2. **Broker**: Adafruit IO MQTT Server (io.adafruit.com).
3. **Client (ESP32)**: Subscribed to the `bulb-control` feed over Wi-Fi.
4. **Hardware**: ESP32 outputs a control signal on GPIO 23 to the Relay IN pin.
5. **Actuator**: Relay closes/opens the 230V AC circuit to the Bulb.

## 🔧 Hardware
- ESP32 Development Board
- 5V Relay Module
- 230V AC Bulb
- Jumper Wires
- Breadboard

## 💻 Software
- Arduino IDE (C++)
- `WiFi.h` library
- `Adafruit_MQTT.h` and `Adafruit_MQTT_Client.h` libraries

## ⚙️ Implementation
The ESP32 firmware authenticates with the Wi-Fi network and the Adafruit IO MQTT broker using placeholder credentials. It remains in a listening loop using `MQTT_ping()` and `readSubscription()`. When a message arrives on `bulb-control`, the code parses it. A value of `1` pulls GPIO 23 HIGH, closing the relay, while a `0` pulls it LOW.

## 🧪 Testing
- Verified successful Wi-Fi and MQTT connection via the Serial Monitor.
- Used the Adafruit IO web dashboard to toggle the switch.
- Confirmed that the physical relay clicked and the AC bulb toggled corresponding to the cloud dashboard state in real-time.

## 🛠️ Challenges & Fixes
- **MQTT Disconnections**: The ESP32 would occasionally drop the MQTT connection. A reconnect loop logic (`MQTT_connect()`) was implemented to handle network instability automatically.
- **Relay Logic**: Discovered that some relay modules are active-low. Adjusted the `HIGH`/`LOW` logic in the ESP32 firmware to match the specific relay hardware.

## 📚 Learning Outcomes
- Understood the difference between Local (HTTP) vs Cloud (MQTT) Control.
- Mastered the configuration of cloud dashboards and data feeds.
- Learned to safely interface microcontrollers with AC voltage using relays.

## 💭 Reflection
Transitioning to MQTT opened up significant possibilities. Unlike the local web server, this implementation allows the bulb to be controlled from anywhere in the world, showcasing the true power of cloud IoT.

## 🔗 Project Information
- **Developer**: Harish Kumaran
- **Course**: ProtoSem
- **Module**: Week 7 IoT Lab

## 🏁 Conclusion
The MQTT Cloud Control system operates reliably, providing instant global access to physical hardware. This sets the stage for further integration with third-party automation tools like IFTTT and Google Assistant.
