#include"headers.h"
BTComms comms;
Messages::Messages() {
	stopped = false;
}
int Message[50];
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
  for (int i = 0; i < comms.getMessageLength(); i++) {
    Message[i] = (comms.getMessageByte(i),HEX);
  }
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
