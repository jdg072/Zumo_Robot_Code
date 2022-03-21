//#include <SoftwareSerial.h>
#include "TurnSensor.h"

//SoftwareSerial myBlue(2, 3);  //RX | TX
//int flag = 1;     
//int value = 0;
//char enterChar;
char ProtocolChar;     //Variable used to tell the robot which activity is being used and when to exit activity
int flag = 1;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);         //This begins communication to the serial monitor on the computer through the micro-usb - used for debugging purposes
  Serial1.begin(9600);        //Begins Bluetooth communication
  turnSensorSetup();          
  delay(500);
  turnSensorReset();
  delay(500);                //Startup delay to allow voltages to settle
}

void loop() {
  
  
  // put your main code here, to run repeatedly:
  //Serial.println(flag);
  //delay(5000);
  if(flag == 1){
    Serial.println("Waiting for which activity to jump to");
    flag = 0;
  }
  if(Serial1.available()){
    ProtocolChar = Serial1.read();    //Reads the character sent

    switch(ProtocolChar){
      case 'a':      
        autonomous_mode();
        flag = 1;
        break;
      case 'b':     //This is the RC mode enterance
        RC_MODE();
        //Serial.println("Exited RC Mode");
        flag = 1;
        //Serial.println(flag);
        break;
      case 'c':
        RC_MODE();
        flag = 1;
        break;
        /*I will be placing whatever else activities we will need here later*/
    }    
  }
  delay(50);
}
