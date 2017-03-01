#include"headers.h"
DriveStates currentState = LINE_FOLLOW;
#define PIN           12
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 5; // delay for half a second
void setup() {
  pixels.begin(); 

  Serial3.begin(115200);
  Serial.begin(9600);
  BT_setup();
  BT_Data();
  Separate_Messages();
  Serial.println("here");
  for(int i = 0;i<4;i++)
  {
    Serial.println(NewTubes[i]);
    Serial.println(Storage[i]);
  }
  Interrupt_Setup();
  Servo_Setup();
  Find_Empty_Storage();
  Find_Full_NewTubes();
  //Serial.println(picks);
  initDrivePWM();
  Lift_Fourbar();
  Send_Update_Radiation(0xFF);
}

void loop() {
   comms.read();
  Read_Line_Sensor();
  Send_HeartBeat();
  Start_Stop_Message();
  if (dockSide == 1){
   Separate_Messages_2();
  Find_Empty_Storage();
  Find_Full_NewTubes();
  }
  if (dockSide == 0){
    Separate_Messages();
  Find_Empty_Storage();
  Find_Full_NewTubes();
  
  }
  
  switch (currentState) {
    case STANDBY:
      Stop();
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
      comms.read();
      Stop();
      
      break;
  }

  delay(15);


}


void Led_Empty()
{
 for(int i=0;i<NUMPIXELS;i++){    
    pixels.setPixelColor(i, pixels.Color(255,255,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  //Send_Update_Radiation(0x2C);
}

void Led_Off()
{
 for(int i=0;i<NUMPIXELS;i++){    
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  //Send_Update_Radiation(0x00);
}


void Led_Loaded()
{
  for(int i=0;i<NUMPIXELS;i++){    
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  //Send_Update_Radiation(0xFF);
}
