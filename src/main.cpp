#define THINGER_SERIAL_DEBUG
#include <ThingerESP8266.h>
#include <DHTesp.h>
#include "device.h"
#include "wifi_id.h"
#include "thingerio_id.h"

#define USERNAME "swiedjaja"
#define DEVICE_ID "binus_iot_course_esp8266"
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

DHTesp dht;

void setup() {
	Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  dht.setup(PIN_DHT, DHTesp::DHT11);
  Serial.println("Booting...");
  Serial.println("Connecting to Thinger.io ...");
  thing.add_wifi(WIFI_SSID, WIFI_PASSWORD);
  // resource input
  thing["led"] << [](pson& in){
    digitalWrite(LED_BUILTIN, !in);
  };
  thing["led_red"] << digitalPin(LED_RED);
  thing["led_green"] << digitalPin(LED_GREEN);
  thing["led_yellow"] << digitalPin(LED_YELLOW);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());
  thing["humidity"] >> outputValue(dht.getHumidity());
  digitalWrite(LED_BUILTIN, LED_BUILTIN_OFF);
}

void loop() {
  thing.handle();
}