# ESP32 Adafruit IO MQTT Cloud Control

### Task 2 — MQTT Cloud Dashboard with Relay Control

---

## Task Overview
Moving beyond local HTTP servers, this project utilizes a cloud-based MQTT broker (Adafruit IO) to enable global remote control of an AC bulb. The ESP32 subscribes to a specific cloud feed and triggers an electromechanical relay on GPIO 23 to switch high voltage securely.

## Problem / Purpose
Local web servers are restricted to devices on the same Wi-Fi network. The purpose of this task is to achieve global reach by utilizing the publish/subscribe MQTT protocol, allowing hardware to be controlled from anywhere in the world.

## Objectives
- Establish an MQTT connection between the ESP32 and Adafruit IO.
- Subscribe to the `bulb-control` feed.
- Safely trigger a 5V relay module via GPIO 23 to control a 230V AC bulb.
- Handle automatic MQTT reconnections.

## Concepts Covered
- Cloud Computing in IoT
- MQTT Publish/Subscribe Architecture
- HTTP vs MQTT protocols
- Adafruit IO Dashboards
- High Voltage Isolation via Relays

## System Architecture

```text
[ Adafruit IO Dashboard ] 
           |
       (MQTT Pub)
           v
    [ MQTT Broker ]
           |
       (MQTT Sub)
           v
       [ ESP32 ] --(GPIO 23)--> [ Relay Module ] --> [ 230V AC Bulb ]
```

## Data Flow
1. User toggles a dashboard block on Adafruit IO.
2. Adafruit IO publishes the state (`1` or `0`) to the `bulb-control` feed.
3. The ESP32, subscribed to the feed, receives the MQTT payload.
4. The ESP32 firmware parses the payload and sets GPIO 23 HIGH or LOW.
5. The relay mechanically switches the AC circuit.

## Hardware
| Component | Description |
|-----------|-------------|
| ESP32 Development Board | IoT microcontroller |
| 5V Relay Module | Electromechanical switch for high voltage isolation |
| 230V AC Bulb & Holder | Physical actuator |
| Jumper Wires | For breadboard connections |

## Software & Technologies
| Technology | Role |
|------------|------|
| Arduino IDE | Firmware development |
| Adafruit IO | Cloud dashboard and MQTT broker |
| `Adafruit_MQTT.h` | MQTT client library |

## Wiring & Hardware Connections
| ESP32 Pin | Component Connection |
|-----------|----------------------|
| 5V (VIN) | Relay VCC |
| GND | Relay GND |
| GPIO 23 | Relay IN (Signal) |

## Configuration
Placeholder credentials are used in the firmware to ensure security:
```cpp
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"
#define AIO_USERNAME "YOUR_AIO_USERNAME"
#define AIO_KEY "YOUR_AIO_KEY"
```

## Implementation Workflow
The firmware establishes Wi-Fi, then connects to `io.adafruit.com` on Port 1883. It explicitly subscribes to the `bulb-control` topic. In the main loop, it continuously listens for incoming packets and sends periodic keep-alive pings.

## Source Code Explanation
- `MQTT_connect()`: A robust while-loop that attempts to reconnect if the broker drops the connection.
- `readSubscription()`: Parses incoming MQTT payloads. If the payload equals `1`, the relay is triggered ON. If `0`, it is turned OFF.

## Testing
- Verified Wi-Fi and MQTT connection via the Serial Monitor.
- Used the Adafruit IO web dashboard to toggle the switch.
- Confirmed that the physical relay clicked and the AC bulb toggled corresponding to the cloud dashboard state in real-time.

## Evidence
- *Note: Video and photographic evidence of the relay switching the AC bulb are preserved in the ProtoSem weekly report.*

## Challenges & Fixes
- **MQTT Disconnections**: The ESP32 would occasionally drop the MQTT connection due to network latency. A reconnect loop logic was implemented to handle network instability automatically.
- **Relay Logic**: Discovered that some relay modules are active-low. Adjusted the `HIGH`/`LOW` logic in the ESP32 firmware to match the specific relay hardware.

## Key Learnings
- Understood the difference between synchronous HTTP and asynchronous MQTT.
- Mastered the configuration of cloud dashboards and data feeds.
- Learned to safely interface microcontrollers with AC voltage using relays.

## Future Improvements
- Add a physical push-button to allow local manual overrides that sync back to the cloud dashboard.

## Reflection
Transitioning to MQTT opened up significant possibilities. Unlike the local web server, this implementation allows the bulb to be controlled from anywhere in the world, showcasing the true power of cloud IoT.

## Project Links
- [Task 2 Implementation Code](./ESP32_AdafruitIO_MQTT_Cloud_Control.ino)
- Developer: Harish Kumaran (ProtoSem Week 7)

## Conclusion
The MQTT Cloud Control system operates reliably, providing instant global access to physical hardware. This sets the stage for further integration with third-party automation tools.
