#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SensirionI2cScd4x.h>
#define LED_PIN 15

const char* WIFI_ID = "Rishi";
const char* WIFI_PASSWORD = "Iamrishi";

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

SensirionI2cScd4x scd4x;

unsigned long lastMsg = 0;

void setup_wifi() {

  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_ID);

  WiFi.begin(WIFI_ID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {

  while (!client.connected()) {

    Serial.print("Connecting to MQTT... ");

    if (client.connect("ESP32_Manav")) {

      Serial.println("Connected");

      client.subscribe("greenhouse/command");

    } else {

      Serial.print("Failed, state = ");
      Serial.println(client.state());

      delay(2000);
    }
  }
}



void callback(char* topic,byte* payload,unsigned int length){

  String msg="";

  for(int i=0;i<length;i++){
    msg +=(char)payload[i];
  }

  Serial.println("Message Recived");
  Serial.println(msg);

  if(msg=="blink led"){

    Serial.println("message recived");

    for(int i=0;i<25;i++){
      digitalWrite(LED_PIN,HIGH);
      delay(500);

      digitalWrite(LED_PIN,LOW);
    delay(500);
    }

    digitalWrite(LED_PIN,HIGH);

  }

}

void setup() {

  Serial.begin(115200);

  setup_wifi();

  client.setServer(mqtt_server, 1883);

  client.setCallback(callback);

  Wire.begin();

  scd4x.begin(Wire, 0x62);

  scd4x.startPeriodicMeasurement();

  Serial.println("SCD41 Started");

  pinMode(LED_PIN,OUTPUT);

  digitalWrite(LED_PIN,HIGH);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  if (millis() - lastMsg > 5000) {

    lastMsg = millis();

    bool dataReady = false;

    scd4x.getDataReadyStatus(dataReady);

    if (dataReady) {

      uint16_t co2;
      float temperature;
      float humidity;

      scd4x.readMeasurement(
        co2,
        temperature,
        humidity
      );

      JsonDocument doc;

      doc["temperature"] = temperature;
      doc["humidity"] = humidity;
      doc["co2"] = co2;

      char jsonBuffer[200];

      serializeJson(doc, jsonBuffer);

      bool result = client.publish(
    "manav/greenhouse/data",
    jsonBuffer
);

Serial.print("Publish result: ");
Serial.println(result);

      Serial.print("Published: ");
      Serial.println(jsonBuffer);
    }
  }
}