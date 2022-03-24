#include <WiFi.h>
#include "PubSubClient.h"

const char* ssid = "LPiOTIA";
const char* password = "";

static const char* connectionString = "";

const char* mqtt_server = "192.168.143.144";
const char* temperature_topic = "M5/Temperature";

const char* clientID = "M5_bajour";

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);

float t;

void setup(){
  Serial.begin(115200);
  Serial.println("Starting connection WiFi.");

  delay(10);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());

  if(client.connect(clientID)){
    Serial.println("Connected to MQTT Broker!");
  }else{
    Serial.print("Connection to MQTT Broker failed...");
  }
}

void loop(){
  Serial.println("start sending events.");
  t=random(50);

  String ts="Temp: "+String((float)t)+"C";

  if(client.publish(temperature_topic, String(t).c_str())){
    Serial.println("Temperature sent!");
  }

  delay(5000);
}
