#ifndef _BTReader
#define _BTReader
class BTComms {
  public:
    BTComms();
    void setup();
    int getMessageLength();
    unsigned char getMessageByte(unsigned index);
    bool read();
    void writeMessage(unsigned char b1, unsigned char b2, unsigned char b3);
   private:
    enum BTstate {kLookingForStart, kReadingMessageLength, kReadMessage} BTstate;
    unsigned messageLength;
    unsigned char message[20];
    unsigned messageIndex;
    unsigned char kMessageStart = 0x5f;
};
void BT_setup();
void BT_Data();
void Send_HeartBeat();

#endif
