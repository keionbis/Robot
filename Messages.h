#ifndef MESSAGES_H_
#define MESSAGES_H_

class Messages {
public:
	typedef enum {kReserved,
		kStorageAvailability,
		kSupplyAvailability,
		kRadiationAlert,
		kStopMovement,
		kResumeMovement,
		kRobotStatus,
		kHeartbeat} MessageType;

	Messages();
  void Store_Message();
	bool isStopped();
	void sendHeartbeat();
	bool read();
	void setup();
	void printMessage();
  void SendUpdate_Radiation(unsigned char b4);

private:
	bool stopped;
};
extern int Message;
extern int loops;

#endif
