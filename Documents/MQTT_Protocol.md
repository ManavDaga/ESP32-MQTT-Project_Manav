# MQTT Topics

This project uses two MQTT topics: one for publishing sensor data and another for receiving commands from the MQTT dashboard.

---

## MQTT Topic Overview

| Topic | Direction | Purpose |
|--------|-----------|---------|
| `manav/greenhouse/data` | ESP32 → MQTT Broker | Publishes temperature, humidity, and CO₂ sensor data in JSON format. |
| `greenhouse/command` | MQTT Dashboard → ESP32 *(via MQTT Broker)* | Receives user commands such as `blink led`. |

---

## Publish Topic

**Topic Name**

```text
manav/greenhouse/data
```

**Sample JSON Payload**

```json
{
  "temperature": 27.5,
  "humidity": 58.2,
  "co2": 620
}
```

The ESP32 creates a JSON payload containing the sensor readings and publishes it to the MQTT broker every 5 seconds.

---

## Subscribe Topic

**Topic Name**

```text
greenhouse/command
```

**Example Command**

```text
blink led
```

When the ESP32 receives this command through the subscribed MQTT topic, the callback function is executed and the onboard LED blinks.

---

## Communication Flow

```text
SCD41 Sensor
      │
      ▼
ESP32
      │
Read Sensor Data
      │
      ▼
Create JSON Payload
      │
      ▼
Publish to MQTT Topic
      │
      ▼
HiveMQ MQTT Broker
      │
      ▼
MQTT Dashboard

User Sends Command
      │
      ▼
HiveMQ MQTT Broker
      │
      ▼
ESP32 Callback Function
      │
      ▼
Blink LED
```