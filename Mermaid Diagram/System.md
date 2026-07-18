# System Architechure 

```mermaid
flowchart LR

  ESP32[ESP32 Microcontrooler]
  WIFI[WI-FI Router]
  MQTT[HiveMQ Broker]
  Sensor[SCD41 Sensor]
  User[MQTT dashboard/client]

  ESP32 -->|I2C| Sensor
  ESP32 -->|WI-FI| WIFI
  WIFI --> MQTT
  MQTT -->|Subscribe Greenhouse Command| ESP32
  ESP32 -->|publish Greenhouse/data| MQTT
  User --> MQTT
  ```