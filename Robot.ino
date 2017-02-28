#include"headers.h"
DriveStates currentState = LINE_FOLLOW;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  BT_setup();
//  while (!Serial3.available()) {
//    delay(50);
//   }
  BT_Data();
  
//  for(int i = 0;i<4;i++)
//  {
//    Serial.println(Storage[i]);
//    Serial.println(NewTubes[i]);
//  }
  Interrupt_Setup();
  Servo_Setup();
  initDrivePWM();
}

void loop() {
  Read_Line_Sensor();
  Send_HeartBeat();
  Start_Stop_Message();
  switch (currentState) {
    case STANDBY:
      Standby();
      break;
    case LINE_FOLLOW :
      Line_Follow();
      Serial.println("line");
      break;

    case INTERSECTION :
      Stop();
      Run_During_Intersection();
      break;
     case INTERSECTION_2 :
      Stop();
      Run_During_Intersection_2();
      break;
    case DOCKED:
      Stop();
      Docked();
    break;
    case DOCKED1:
      Stop();
      Docked_1();
      break;
    case DOCKED2:
      Stop();
      Docked_2();
      break;
    case DOCKED2_2:
      Stop();
      Docked_2_2();
      break;
    case DOCKED3:
       Stop();
       Docked_3();
      break;
    case STOP:
      Stop();
      
      break;
  }

  delay(15);


}
