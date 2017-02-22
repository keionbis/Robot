#include"headers.h"
BTComms comms;
int Message[2];
Messages::Messages() {
	stopped = false;
}
void Messages::setup() {
	comms.setup();
}

bool Messages::isStopped() {
	return stopped;
}

void Messages::sendHeartbeat() {
	comms.writeMessage(kHeartbeat, 0x0a, 0x00);
}

void Messages::Store_Message(){
  
    Message[0] = (comms.getMessageByte(3),HEX);
    Message[1] = (comms.getMessageByte(3),HEX);
    Reactor_State_Set();
    
  
}

void Messages::printMessage() {
    for (int i = 0; i < comms.getMessageLength(); i++) {
      Serial.print(comms.getMessageByte(i), HEX);
      Serial.print(" ");
    }
    Serial.println();
}

bool Messages::read() {
	if (comms.read()) {
		switch (comms.getMessageByte(0)) {
		case kStorageAvailability:
			break;
		case kSupplyAvailability:
			break;
		case kRadiationAlert:
			break;
		case kStopMovement:
			break;
		case kResumeMovement:
			break;
		case kRobotStatus:
			break;
		case kHeartbeat:
			break;
		}
		return true;
	}
	return false;
}
