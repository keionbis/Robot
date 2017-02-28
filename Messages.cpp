#include"headers.h"

BTComms comms;
int Message;
int i = 0;
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
  
   
    loops++;
    
  
}

void Messages::printMessage() {
    Message = (comms.getMessageByte(3));
    if (Message == 0)
    {
      Serial.println("0");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 1)
    {
      Serial.println("1");
      ReactorStates[i] = FULL;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 2)
    {
      Serial.println("2");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 3)
    {
      Serial.println("3");
      ReactorStates[i] = FULL;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 4)
    {
      Serial.println("3");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 5)
    {
      Serial.println("5");
      ReactorStates[i] = FULL;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 6)
    {
      Serial.println("6");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 7)
    {
      Serial.println("7");
      ReactorStates[i] = FULL;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = EMPTY;
    }
    else if (Message == 8)
    {
      Serial.println("8");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = FULL;
    }else if (Message == 9)
    {
      Serial.println("9");
      ReactorStates[i] = FULL;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = FULL;
    }
    else if (Message == 10)
    {
      Serial.println("10");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = FULL;
    }
    else if (Message == 11)
    {
      Serial.println("11");
      ReactorStates[i] = FULL;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = EMPTY;
      ReactorStates[i+6] = FULL;
    }
    else if (Message == 12)
    {
      Serial.println("12");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = FULL;
    }
    else if (Message == 13)
    {
      Serial.println("13");
      ReactorStates[i] = FULL;
      ReactorStates[i+2] = EMPTY;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = FULL;
    }
    else if (Message == 14)
    {
      Serial.println("14");
      ReactorStates[i] = EMPTY;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = FULL;
    }
    else if (Message == 15)
    {
      Serial.println("15");
       ReactorStates[i] = FULL;
      ReactorStates[i+2] = FULL;
      ReactorStates[i+4] = FULL;
      ReactorStates[i+6] = FULL;
    }
    i++;
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
