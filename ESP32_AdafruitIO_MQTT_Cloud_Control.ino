#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"
#define AIO_USERNAME "YOUR_ADAFRUIT_USERNAME"
#define AIO_KEY "YOUR_ADAFRUIT_IO_KEY"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe bulbControl = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/bulb-control");

#define RELAY_PIN 23
#define RELAY_ON HIGH
#define RELAY_OFF LOW

void connectWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wi-Fi Connected!");
}

void connectMQTT() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1); // wait for watchdog to reset
    }
  }
  Serial.println("MQTT Connected!");
}

void processBulbCommand(String command) {
  command.trim();
  command.toLowerCase();
  
  if (command == "1" || command == "on" || command == "bulb on" || command == "bulbon") {
    digitalWrite(RELAY_PIN, RELAY_ON);
    Serial.println("Bulb turned ON");
  } 
  else if (command == "0" || command == "off" || command == "bulb off" || command == "bulboff" || command == "of") {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    Serial.println("Bulb turned OFF");
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  connectWiFi();
  
  mqtt.subscribe(&bulbControl);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
  
  connectMQTT();
  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &bulbControl) {
      String command = (char *)bulbControl.lastread;
      Serial.print("Received command: ");
      Serial.println(command);
      processBulbCommand(command);
    }
  }
}
