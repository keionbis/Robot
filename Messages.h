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

	bool isStopped();
	void sendHeartbeat();
	bool read();
	void setup();
	void printMessage();

private:
	bool stopped;
};

#endif
