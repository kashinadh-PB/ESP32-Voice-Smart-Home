#include <Arduino.h>
#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID "ESP_TEST"
#define WIFI_PASS "12345678"

#define APP_KEY "d001b05c-866a-4e43-afb7-0bc66a432909"
#define APP_SECRET "3cb7f339-96dc-41f9-aa54-26c33e2a852c-9a10dc12-0107-44de-a22e-e4a1cc38b3c0"

#define LIGHT_ID  "69b2be55db0f6e0b159c5856"
#define FAN_ID    "69b52630db0f6e0b159d9dd7"
#define SWITCH_ID "69b52f6c17b32c0941d381ab"

#define LIGHT_LED 2
#define FAN_LED 4
#define SWITCH_LED 5

// -------------------- LIGHT --------------------

bool onLight(const String &deviceId, bool &state) {

  digitalWrite(LIGHT_LED, state);

  Serial.print("Light ");
  Serial.println(state ? "ON" : "OFF");

  return true;
}

// -------------------- FAN --------------------

bool onFan(const String &deviceId, bool &state) {

  digitalWrite(FAN_LED, state);

  Serial.print("Fan ");
  Serial.println(state ? "ON" : "OFF");

  return true;
}

// -------------------- SWITCH --------------------

bool onSwitch(const String &deviceId, bool &state) {

  digitalWrite(SWITCH_LED, state);

  Serial.print("Switch ");
  Serial.println(state ? "ON" : "OFF");

  return true;
}

// -------------------- SETUP --------------------

void setup() {

  Serial.begin(115200);

  pinMode(LIGHT_LED, OUTPUT);
  pinMode(FAN_LED, OUTPUT);
  pinMode(SWITCH_LED, OUTPUT);

  Serial.print("Connecting WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  // SinricPro devices
  SinricProSwitch &light = SinricPro[LIGHT_ID];
  SinricProSwitch &fan = SinricPro[FAN_ID];
  SinricProSwitch &sw = SinricPro[SWITCH_ID];

  light.onPowerState(onLight);
  fan.onPowerState(onFan);
  sw.onPowerState(onSwitch);

  SinricPro.begin(APP_KEY, APP_SECRET);

  Serial.println("Voice control ready");
}

// -------------------- LOOP --------------------

void loop() {

  SinricPro.handle();

}
