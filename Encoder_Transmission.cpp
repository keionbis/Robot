#include "headers.h"

int ticks_Right, ticks_Left, bytes;
int Right_Turn_Encoder_Vals_Start, Left_Turn_Encoder_Vals_Start;
void Read_Encoder_Ticks()
{
  Wire.requestFrom(SLAVE_ADDRESS, 1);
  bytes = Wire.available();
  for(int i = 0; i< bytes; i++)
  {
    ticks_Right = Wire.read();
  }
  Wire.requestFrom(SLAVE_ADDRESS_2, 1);
  bytes = Wire.available();
  for(int i = 0; i< bytes; i++)
  {
    ticks_Left = Wire.read();
  }
}


void turn90(TurnDirection TurnDir)
{
  Read_Encoder_Ticks();
  Right_Turn_Encoder_Vals_Start = ticks_Right;
  Left_Turn_Encoder_Vals_Start = ticks_Left;
  switch(TurnDir)
  {
    case Right:
      while ((ticks_Right - Right_Turn_Encoder_Vals_Start) < Turn_Ticks &&  (Left_Turn_Encoder_Vals_Start- ticks_Left ) < Turn_Ticks )
      {
        setDrivePWM(32767, LEFT, FORWARD);
        setDrivePWM(32767, RIGHT, BACKWARD);
        // delay(75); 
      }
      
      break;
    case Left:
       while ((ticks_Left - Left_Turn_Encoder_Vals_Start) < Turn_Ticks &&  (Right_Turn_Encoder_Vals_Start- ticks_Right ) < Turn_Ticks )
       {
        
       }
      break; 
  }
}

