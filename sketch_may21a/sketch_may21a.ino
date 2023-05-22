#include <SoftwareSerial.h>
/* Create object named SIM900 of the class SoftwareSerial */
SoftwareSerial SIM900(9, 10);
void setup() {
  SIM900.begin(9600);  /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {
  Serial.println("TCP Send :");
  Serial.print("AT\\r\\n");
  SIM900.println("AT"); /* Check Communication */
  delay(5000);
  ShowSerialData(); /* Print response on the serial monitor */
  delay(5000);
  Serial.println("AT+CIPMODE=0\\r\\n");
  SIM900.println("AT+CIPMODE=0"); /* Non-Transparent (normal) mode for TCP/IP application */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CIPMUX=0\\r\\n");
  SIM900.println("AT+CIPMUX=0");  /* Single TCP/IP connection mode */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CGATT=1\\r\\n");
  SIM900.println("AT+CGATT=1"); /* Attach to GPRS Service */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CREG?\\r\\n");
  SIM900.println("AT+CREG?"); /* Network registration status */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CGATT?\\r\\n");
  SIM900.println("AT+CGATT?");  /* Attached to or detached from GPRS service */ 
  delay(5000); 
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CSTT=\"internet\",\"\",\"\"\\r\\n");
  SIM900.println("AT+CSTT=\"internet\",\"\",\"\""); /* Start task and set APN */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CIICR\\r\\n");
  SIM900.println("AT+CIICR"); /* Bring up wireless connection with GPRS */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CIFSR\\r\\n");
  SIM900.println("AT+CIFSR"); /* Get local IP address */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CIPSSL=1\\r\\n");
  SIM900.println("AT+CIPSSL=1"); /* Get local IP address */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CIPSTART=\"TCP\",\"https://iot-gsm-b7cb1-default-rtdb.firebaseio.com\",443\\r\\n");
  SIM900.println("AT+CIPSTART=\"TCP\",\"https://iot-gsm-b7cb1-default-rtdb.firebaseio.com/\",\"443\"");  /* Start up TCP connection */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+CIPSEND\\r\\n");
  SIM900.println("AT+CIPSEND"); /* Send data through TCP connection */
  delay(2000);
  ShowSerialData();
  delay(2000);
  Serial.print("POST Data.json "); 
  Serial.println("HTTP/1.1\r\n");
  delay(10);
  Serial.println(F("Host: https://iot-gsm-b7cb1-default-rtdb.firebaseio.com"));
  Serial.println(F("Content-Type: applicacion/json\r\nContent-Length: 256"));
  Serial.print(F("X-HTTP-Method-Override: PUT\r\n\r\n"));
  Serial.println(F("{\"PH\" : 90,\"CD\" : 190, \"GPS\" : 100, \"TEMP\" : 10}"));
  Serial.print((char)26);
  SIM900.print("POST Data.json "); 
  SIM900.println("HTTP/1.1\r\n");
  delay(10);
  SIM900.println(F("Host: https://iot-gsm-b7cb1-default-rtdb.firebaseio.com"));
  SIM900.println(F("Content-Type: application/json\r\nContent-Length: 256"));
  SIM900.print(F("X-HTTP-Method-Override: PUT\r\n\r\n"));
  SIM900.println(F("{\"PH\" : 90,\"CD\" : 190, \"GPS\" : 100, \"TEMP\" : 10}"));
  SIM900.print((char)26);
  delay(20000);
  ShowSerialData();
  delay(5000);
  Serial.println();
  Serial.print("AT+CIPSHUT\\r\\n");
  SIM900.println("AT+CIPSHUT"); /* Deactivate GPRS PDP content */
  delay(5000);
  ShowSerialData();
  delay(5000);
}

void ShowSerialData()
{
  Serial.println();
  while(SIM900.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM900.read())); /* Print character received on to the serial monitor */
}
