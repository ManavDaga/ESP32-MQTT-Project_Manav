# Code Explanation

This document explains the working of the ESP32 MQTT Greenhouse Monitoring System.

---

# Program Workflow

The program performs the following tasks:

1. Connects the ESP32 to a Wi-Fi network.
2. Connects to the HiveMQ MQTT broker.
3. Subscribes to an MQTT command topic.
4. Initializes the SCD41 CO₂ sensor.
5. Reads CO₂, temperature, and humidity every 5 seconds.
6. Converts the sensor data into JSON format.
7. Publishes the JSON data to the MQTT broker.
8. Listens for incoming MQTT commands and controls the onboard LED.

---

# Header Files

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SensirionI2cScd4x.h>
```

### WiFi.h

Provides all Wi-Fi related functions such as connecting the ESP32 to a wireless network.

### PubSubClient.h

Provides MQTT communication functions such as connecting to the broker, publishing messages and subscribing to topics.

### ArduinoJson.h

Used to create JSON objects before sending sensor data over MQTT.

### Wire.h

Implements I2C communication used by the SCD41 sensor.

### SensirionI2cScd4x.h

Provides functions for communicating with the Sensirion SCD41 CO₂ sensor.

---

# Global Variables

```cpp
#define LED_PIN 15
```

Defines GPIO 15 as the LED output pin.

```cpp
const char* WIFI_ID
const char* WIFI_PASSWORD
```

Stores the Wi-Fi credentials.

```cpp
const char* mqtt_server
```

Stores the MQTT broker address.

```cpp
WiFiClient espClient;
```

Creates a TCP client used by MQTT.

```cpp
PubSubClient client(espClient);
```

Creates the MQTT client using the Wi-Fi connection.

```cpp
SensirionI2cScd4x scd4x;
```

Creates the SCD41 sensor object.

```cpp
unsigned long lastMsg
```

Stores the last sensor publishing time.

---

# setup_wifi()

Purpose:

Connects the ESP32 to the configured Wi-Fi network.

Working:

- Prints the Wi-Fi name on the Serial Monitor.
- Starts the Wi-Fi connection.
- Continuously checks whether the ESP32 has connected.
- Displays the assigned IP address after a successful connection.

---

# reconnect()

Purpose:

Reconnects the ESP32 to the MQTT broker whenever the connection is lost.

Working:

- Attempts to connect using the client ID **ESP32_Manav**.
- If successful, subscribes to the topic:

```
greenhouse/command
```

- If unsuccessful, waits for 2 seconds before trying again.

---

# callback()

Purpose:

Processes every MQTT message received by the ESP32.

Working:

1. Receives the MQTT topic and message.
2. Converts the received byte array into a String.
3. Prints the received message on the Serial Monitor.
4. Checks whether the command is:

```
blink led
```

5. If the command matches:
   - Blinks the LED 25 times.
   - Leaves the LED ON after blinking.

---

# setup()

Purpose:

Runs once after the ESP32 powers on.

Functions performed:

- Starts Serial communication.
- Connects to Wi-Fi.
- Configures the MQTT broker.
- Registers the callback function.
- Starts I2C communication.
- Initializes the SCD41 sensor.
- Starts periodic CO₂ measurements.
- Configures the LED pin as an output.
- Turns the LED ON.

---

# loop()

Purpose:

Runs continuously throughout the execution of the program.

Working:

### MQTT Connection

Checks whether MQTT is connected.

If disconnected, the ESP32 reconnects automatically.

---

### MQTT Processing

```cpp
client.loop();
```

Processes incoming MQTT messages.

Without this function, the ESP32 cannot receive subscribed messages.

---

### Sensor Reading

Every 5 seconds:

- Checks whether new sensor data is available.
- Reads:

  - CO₂ concentration
  - Temperature
  - Humidity

---

### JSON Creation

Creates the following JSON object:

```json
{
  "temperature": 25.6,
  "humidity": 61.2,
  "co2": 650
}
```

---

### MQTT Publish

Publishes the JSON data to:

```
manav/greenhouse/data
```

The publish result is printed on the Serial Monitor.

---

# MQTT Topics

## Published Topic

```
manav/greenhouse/data
```

Contains:

- Temperature
- Humidity
- CO₂ concentration

---

## Subscribed Topic

```
greenhouse/command
```

Accepted command:

```
blink led
```

---

# Overall Program Execution

```
Power ON
      ↓
Initialize Hardware
      ↓
Connect Wi-Fi
      ↓
Connect MQTT Broker
      ↓
Subscribe Topic
      ↓
Initialize CO₂ Sensor
      ↓
Read Sensor Data
      ↓
Create JSON
      ↓
Publish MQTT Data
      ↓
Wait for Commands
      ↓
Execute LED Command
      ↓
Repeat Forever
```

---

# Key Features

- ESP32-based IoT application
- Wi-Fi communication
- MQTT Publish/Subscribe architecture
- JSON data formatting
- CO₂, Temperature and Humidity monitoring
- Automatic MQTT reconnection
- Remote LED control using MQTT commands
- Real-time Serial Monitor debugging