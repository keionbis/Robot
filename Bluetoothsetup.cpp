#include"headers.h"
Messages msg;
unsigned long timeForHeartbeat;
int loops = 0;
void BT_setup(){
  comms.setup();
  msg.setup();
  timeForHeartbeat = millis() + 1000;
}

void BT_Data()
{
     while(msg.read()) {    
  }
}

void Send_HeartBeat()
{
  if (millis() > timeForHeartbeat) {
    timeForHeartbeat = millis() + 1000;
    msg.sendHeartbeat();
  }
}
