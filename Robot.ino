#include"headers.h"
 DriveStates currentState;
void setup() {
  Servo_Setup();
  initDrivePWM();

}

void loop() {
  switch (currentState){
    case LINE_FOLLOW :
      Line_Follow();
      break;
    case INTERSECTION :
      break;
    case TURN_RIGHT :
      break;
    case TURN_LEFT:
      break;
    case DOCKED:
      break;
    case REMOVE_ROD:
      break;
    case PLACE_ROD:
      break;
    case REVERSE:
      break;
    case STOP:
      break;
    case GRIPPER_STRAIGHT:
      break;
  }

    delay(15);


}
