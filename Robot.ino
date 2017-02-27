#include"headers.h"
 DriveStates currentState = LINE_FOLLOW;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  //Serial.println("SETUP");
  BT_setup();
  //printMessage();
  //while (!Serial3.available()) {
    //delay(50);
  //}
  BT_Data();
//  for (int i = 0;i<8;i++){
//  Serial.println(ReactorStates[i]);
//  }
  //Serial.println("End BT");
  Interrupt_Setup();
  //Serial.println("End Interrupts");
  Servo_Setup();
  //Serial.println("END SERVO SETUP");
  initDrivePWM();
  //Serial.println("END Insitdrive");
  Turn_Left();
  delay(500);
  Stop();
  Serial.println("LEFT");
  Turn_Right();
  delay(500);
  Serial.println("RIGHT");
  Stop();
}

void loop() {
  Read_Line_Sensor();
  Send_HeartBeat();
  Start_Stop_Message();
  switch (currentState){
    case STANDBY:
      Standby();
      Serial.println("STANDBY");
      break;
    case LINE_FOLLOW :
      //Line_Follow();
      Serial.println("LINEFOLLOW");
      break;
    case INTERSECTION :
      Stop();
      currentState = LINE_FOLLOW;
      Serial.println("INTERSECTION");
      delay(5000);
      while(Enter_Intersection_State);
      {
      setDrivePWM( 65535, LEFT,FORWARD);
      setDrivePWM( 65535, RIGHT,FORWARD);
      }
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
      break;
    case DOCKED:
      Serial.println("DOCKED");
      break;
    case STOP:
    Serial.println("STOP");
      Stop();
      break;
  }

    delay(15);


}
