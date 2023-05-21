void http(bool req,const char* URL,const char* CONTENT_TYPE = "application/json",const char* PAYLOAD = ""){
  bool connected = false;
  for(uint8_t i = 0; i < 5 && !connected; i++) {
    delay(1000);
    connected = sim800l->connectGPRS();
  }
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
  uint16_t rc = 0;
  if(req){
    rc = sim800l->doPost(URL, CONTENT_TYPE, PAYLOAD, 10000, 10000);
  }else{
    rc = sim800l->doGet(URL, 10000);
  }
   if(rc == 200) {
    // Success, output the data received on the serial
    Serial.print(F("HTTP REQ successful ("));
    Serial.print(sim800l->getDataSizeReceived());
    Serial.println(F(" bytes)"));
    Serial.print(F("Received : "));
    Serial.println(sim800l->getDataReceived());
  } else {
    Serial.print(F("HTTP POST error "));
    Serial.println(rc);
  }
  delay(1000);
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
  bool lowPowerMode = sim800l->setPowerMode(MINIMUM);
  if(lowPowerMode) {
    Serial.println(F("Module in low power mode"));
  } else {
    Serial.println(F("Failed to switch module to low power mode"));
  }
}
