#include"headers.h"
Messages msg;
unsigned long timeForHeartbeat;
int loops = 0;
void BT_setup(){
   while (!Serial3.available()) {
    delay(50);
   }
   
  comms.setup();
  msg.setup();
  timeForHeartbeat = millis() + 300;
  
}

void BT_Data()
{
     while(msg.read()) {
     msg.printMessage();  
     delay(7);  
  }
}

void Send_HeartBeat()
{
  if (millis() > timeForHeartbeat) {
    timeForHeartbeat = millis() + 1000;
    msg.sendHeartbeat();
  }
}
