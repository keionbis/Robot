#include"headers.h"
 DriveStates currentState;

void setup() {
  BT_setup();
  while (!Serial3.available()) {
    delay(50);
  }
  BT_Data();
  Interrupt_Setup();
  Servo_Setup();
  initDrivePWM();
}

void loop() {
  Read_Line_Sensor();
  Send_HeartBeat();
  Start_Stop_Message();
  switch (currentState){
    case STANDBY:
      Standby();
      break;
    case LINE_FOLLOW :
      Line_Follow();
      break;
    case INTERSECTION :
      Stop();
        switch(ReactorStates[Intersections-1])
        {
          case FULL:
            Turn_Right();
            while(currentState!= DOCKED)
            {
              Line_Follow();
            }
            Stop();
            Lift_Fourbar();
            Open_Gripper();
            Close_Gripper();
            Reverse();
            Turn_Right();
            break;
          case EMPTY:
            break;
        }
        switch(ReactorStates[Intersections])
        {
          case FULL:
            Turn_Left();
            while(currentState!= DOCKED)
            {
            Line_Follow();
            }
            Stop();
            Lift_Fourbar();
            Open_Gripper();
            Close_Gripper();
            Reverse();
            Turn_Left();
            break;
          case EMPTY:
            break;
        }
      currentState = LINE_FOLLOW;
      break;
    case DOCKED:
      break;
    case STOP:
      Stop();
      break;
  }

    delay(15);


}
