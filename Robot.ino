#include"headers.h"
 DriveStates currentState;
void setup() {
  Servo_Setup();
  initDrivePWM();
  BT_setup();
  BT_Data();
  Interrupt_Setup();

}

void loop() {
  Read_Line_Sensor();
  Send_HeartBeat();
  switch (currentState){
    case LINE_FOLLOW :
      Line_Follow();
      break;
    case INTERSECTION :
      //check left and right statuses
      Stop();
      if()//bluetooth message[Intersections] = full
      {
        //currentState = Turn_Right()
      }
      break;
    case TURN_RIGHT :
      Turn_Right();

      break;
    case TURN_LEFT:
      Turn_Left();
      break;
    case DOCKED:
      Stop();
      break;
    case REMOVE_ROD:
      break;
    case PLACE_ROD:
      break;
    case REVERSE:
      break;
    case STOP:
      Stop();
      break;
  }

    delay(15);


}
