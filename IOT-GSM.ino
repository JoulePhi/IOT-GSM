#include <SoftwareSerial.h>
#include "SIM800L.h"
#define SIM800_RX_PIN 9
#define SIM800_TX_PIN 10
#define SIM800_RST_PIN 8
#define POST 1
#define GET 0
SIM800L* sim800l;
const char* APN = "internet";
void setup() {
  Serial.begin(9600);
  while(!Serial);
  SoftwareSerial* serial = new SoftwareSerial(SIM800_RX_PIN, SIM800_TX_PIN);
  serial->begin(9600);
  delay(1000);  
  sim800l = new SIM800L((Stream *)serial, SIM800_RST_PIN, 200, 512);
  setupModule();
}
void loop() {
  http(POST,"");
}
