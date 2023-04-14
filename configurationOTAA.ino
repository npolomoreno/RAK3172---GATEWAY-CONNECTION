#include <Arduino.h>   // required before wiring_private.h
#include "wiring_private.h" // pinPeripheral() function


Uart SerialLora (&sercom4, 19, 18, SERCOM_RX_PAD_1, UART_TX_PAD_0);
//
void SERCOM4_Handler()
{
  SerialLora.IrqHandler();  
}

void atCommand(String command){
  String teststr; 
  String commandnr;
  commandnr = command+"\r\n";
  Serial.print(commandnr);
  SerialLora.write(commandnr.c_str());
  do {
    while(SerialLora.available()==0);
    teststr = SerialLora.readStringUntil('\n');
    Serial.println(teststr);
  } while(teststr != "OK\r");
}

void setup() {
  String teststr;
  delay(1000);
  Serial.begin(9600);    // connect serial
  while (!Serial) {       // wait for serial port to connect. Needed for native USB
  }
  Serial.println("USB Serial OK");
  SerialLora.begin(115200); // connect lora sensor
  while (!SerialLora) {       // wait for serial port to connect. Needed for native USB
  }
  Serial.println("LoRa Serial OK"); 
  atCommand("AT+JOIN=0");
  atCommand("AT+NJM=1");
  atCommand("AT+CLASS=A");
  atCommand("AT+BAND=6");
  atCommand("AT+MASK=0002");
  atCommand("AT+CHE=2");  
  atCommand("AT+JOIN=1:0:10:8");
  do{
   while(SerialLora.available()==0){
   }
    teststr = SerialLora.readStringUntil('\r');
    Serial.println(teststr);
  }while(teststr != "+EVT:JOINED");
  atCommand("AT+SEND=2:04FF7420");
  while(1){
   while(SerialLora.available()==0){
   }
    teststr = SerialLora.readStringUntil('\r');
    Serial.println(teststr);  
  }
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
