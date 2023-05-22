void SEND(String GPS,String DATE,String TIME,String CD,String PH,String TEMP){
  bool connected = false;
  for(uint8_t i = 0; i < 5 && !connected; i++) {
    delay(1000);
    connected = sim800l->connectGPRS();
  }

  // Check if connected, if not reset the module and setup the config again
  if(connected) {
    Serial.print(F("GPRS connected with IP "));
    Serial.println(sim800l->getIP());
  } else {
    Serial.println(F("GPRS not connected !"));
    Serial.println(F("Reset the module."));
    sim800l->reset();
    setupModule();
    return;
  }

  Serial.println(F("Start HTTP POST..."));
  String content = "";
  content += "[[";
  content += "\"";
  content += GPS;
  content += "\"";
  content += ",";
  content += "\"";
  content += DATE;
  content += "\"";
  content += ",";
  content += "\"";
  content += TIME;
  content += "\"";
  content += ",";
  content += "\"";
  content += PH;
  content += "\"";
  content += ",";
  content += "\"";
  content += CD;
  content += "\"";
  content += ",";
  content += "\"";
  content += TEMP;
  content += "\"";
  content += "]]";
  Serial.println(content);
  // Do HTTP POST communication with 10s for the timeout (read and write)
  uint16_t rc = sim800l->doPost(URL, CONTENT_TYPE, content.c_str(), 10000, 10000);
   if(rc == 200) {
    // Success, output the data received on the serial
    Serial.print(F("HTTP POST successful ("));
    Serial.print(sim800l->getDataSizeReceived());
    Serial.println(F(" bytes)"));
    Serial.print(F("Received : "));
    Serial.println(sim800l->getDataReceived());
  } else {
    // Failed...
    Serial.print(F("HTTP POST error "));
    Serial.println(rc);
  }

  delay(1000);

  // Close GPRS connectivity (5 trials)
  bool disconnected = sim800l->disconnectGPRS();
  for(uint8_t i = 0; i < 5 && !connected; i++) {
    delay(1000);
    disconnected = sim800l->disconnectGPRS();
  }
  
  if(disconnected) {
    Serial.println(F("GPRS disconnected !"));
  } else {
    Serial.println(F("GPRS still connected !"));
  }

  // Go into low power mode
  bool lowPowerMode = sim800l->setPowerMode(MINIMUM);
  if(lowPowerMode) {
    Serial.println(F("Module in low power mode"));
  } else {
    Serial.println(F("Failed to switch module to low power mode"));
  }

}
