#include"headers.h"
Messages msg;
unsigned long timeForHeartbeat;
void BT_setup(){
msg.setup();
  timeForHeartbeat = millis() + 1000;
}

void BT_Data()
{
  if (msg.read()) {
    msg.printMessage();
  }
  if (millis() > timeForHeartbeat) {
    timeForHeartbeat = millis() + 1000;
    msg.sendHeartbeat();
  }

}

