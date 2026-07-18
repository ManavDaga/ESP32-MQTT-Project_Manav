# Setup Guide

This document explains how to set up and run the ESP32 MQTT Greenhouse Monitoring System.

---

# Prerequisites

Before starting, ensure you have the following:

- ESP32 Development Board
- SCD41 CO₂ Sensor
- USB Cable
- Computer with Windows, Linux or macOS
- Wi-Fi Network
- Internet Connection

---

# Software Requirements

Install the following software:

| Software | Purpose |
|----------|---------|
| Arduino IDE | Write and upload the ESP32 program |
| Git | Clone and manage the project repository |
| GitHub Account | Access the project repository |
| MQTT Client (MQTT Explorer or MQTTX) | View sensor data and send MQTT commands |

---

# Install ESP32 Board Package

1. Open Arduino IDE.
2. Go to **File → Preferences**.
3. In **Additional Boards Manager URLs**, add:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

4. Click **OK**.
5. Open **Tools → Board → Boards Manager**.
6. Search for **ESP32**.
7. Install **ESP32 by Espressif Systems**.

---

# Install Required Libraries

Open:

**Sketch → Include Library → Manage Libraries**

Install the following libraries:

| Library | Author |
|---------|--------|
| PubSubClient | Nick O'Leary |
| ArduinoJson | Benoit Blanchon |
| Sensirion I2C SCD4x | Sensirion |
| Wire | Included with Arduino IDE |

---

# Hardware Connections

Connect the SCD41 sensor to the ESP32.

| SCD41 Pin | ESP32 Pin |
|-----------|-----------|
| VIN | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

> **Note:** Verify the SDA and SCL pins if your ESP32 board uses different default I2C pins.

---

# Clone the Repository

Open Command Prompt or Git Bash and run:

```bash
git clone https://github.com/ManavDaga/ESP32-MQTT-Project_Manav.git
```

Then open the project in Arduino IDE or Visual Studio Code.

---

# Configure Wi-Fi

Open the source code and update the following values:

```cpp
const char* WIFI_ID = "Your_WiFi_Name";
const char* WIFI_PASSWORD = "Your_WiFi_Password";
```

Replace them with your own Wi-Fi credentials.

---

# MQTT Configuration

The project uses the public HiveMQ broker.

```cpp
const char* mqtt_server = "broker.hivemq.com";
```

Default MQTT Port:

```text
1883
```

No username or password is required.

---

# Select the ESP32 Board

In Arduino IDE:

1. Open **Tools → Board**.
2. Select your ESP32 board.
3. Select the correct COM Port.

---

# Upload the Program

1. Connect the ESP32 using a USB cable.
2. Click **Verify** to compile the code.
3. Click **Upload**.
4. Wait until the upload is complete.

---

# Open the Serial Monitor

1. Open **Tools → Serial Monitor**.
2. Set the baud rate to:

```text
115200
```

You should see messages indicating:

- Wi-Fi connected
- MQTT connected
- Sensor initialized
- JSON data published

---

# Test MQTT Communication

Open an MQTT client such as MQTT Explorer or MQTTX.

Subscribe to:

```text
manav/greenhouse/data
```

You should receive JSON data every 5 seconds.

Example:

```json
{
  "temperature": 26.8,
  "humidity": 58.4,
  "co2": 650
}
```

---

# Test LED Control

Publish the following message:

Topic:

```text
greenhouse/command
```

Payload:

```text
blink led
```

The ESP32 should blink the LED 25 times and leave it ON.

---

# Troubleshooting

## ESP32 does not connect to Wi-Fi

- Verify the Wi-Fi name.
- Verify the Wi-Fi password.
- Ensure the Wi-Fi network is available.

---

## MQTT connection fails

- Check your Internet connection.
- Verify the broker address.
- Ensure port **1883** is accessible.

---

## Sensor data is not published

- Check the I2C wiring.
- Verify the sensor is powered.
- Ensure the SCD41 library is installed.

---

# Setup Complete

If all the above steps are completed successfully, the ESP32 will:

- Connect to Wi-Fi.
- Connect to the MQTT broker.
- Read CO₂, temperature and humidity.
- Publish sensor data every 5 seconds.
- Receive MQTT commands.
- Control the onboard LED based on received commands.