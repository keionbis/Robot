#ifndef MESSAGES_H_
#define MESSAGES_H_
extern int Message[50];
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

private:
	bool stopped;
};
extern int Message[50];

#endif
