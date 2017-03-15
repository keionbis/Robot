#include"headers.h"

BTComms::BTComms() {
  messageIndex = 0;
  messageLength = 0;
  BTstate = kLookingForStart;
}

void BTComms::setup() {
  Serial3.begin(115200);
}

void BTComms::writeMessage(unsigned char b1, unsigned char b2, unsigned char b3) {
  Serial3.write(kMessageStart);
  Serial3.write(5);
  Serial3.write(b1);
  Serial3.write(b2);
  Serial3.write(b3);
  Serial3.write(0xff - (b1 + b2 + b3 + 5));
}

void BTComms::writeMessage2(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4) {
  Serial3.write(kMessageStart);
  Serial3.write(5);
  Serial3.write(b1);
  Serial3.write(b2);
  Serial3.write(b3);
  Serial3.write(b4);
  Serial3.write(0xff - (b1 + b2 + b3 + b4 + 5));
}

int BTComms::getMessageLength() {
  return messageLength;
}

unsigned char BTComms::getMessageByte(unsigned index) {
  return message[index];
}

bool BTComms::read() {
  while (Serial3.available()) {
    unsigned inByte = Serial3.read();
    switch (BTstate) {
      case kLookingForStart:
        if (inByte != kMessageStart)
          break;
        BTstate = kReadingMessageLength;
        break;
      case kReadingMessageLength:
        messageLength = inByte - 1;
        messageIndex = 0;
        BTstate = kReadMessage;
        break;
      case kReadMessage:
        message[messageIndex++] = inByte;
        if (messageIndex >= messageLength) {
          BTstate = kLookingForStart;
          return true;
        }
        break;
      default:
        Serial.println("Invalid state");
    }
  }
  return false;
}

