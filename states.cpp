#include"headers.h"

void Line_Follow()
{
int drivepwmright, drivepwmleft;
    drivepwmleft = map(analogRead(2),35,1024,35000,10000);
    drivepwmright = map(analogRead(7),35,1024,35000,10000);
    setDrivePWM(drivepwmleft, LEFT, FORWARD);
    setDrivePWM(drivepwmright, RIGHT, FORWARD);
}

void Turn_Right()
{
    setDrivePWM(32767, LEFT, FORWARD);
    setDrivePWM(32767, RIGHT, BACKWARD);
    delay(75);
}
void Turn_Left()
{
   setDrivePWM(32767, LEFT, BACKWARD);
   setDrivePWM(32767, RIGHT, FORWARD);
   delay(75);
}
void Lift_Fourbar()
{
  if(runs>1)
  {
    FourbarServo.write(22);
  }
  FourbarServo.write(pos);
  
 
}
void Lower_Fourbar()
{
   

}
void Open_Gripper()
{
  GripperServo.write(100);
}
void Close_Gripper()
{
  GripperServo.write(150);
}
void Reverse()
{
    drivepwmleft = map(analogRead(2),35,1024,10000,35000);
    drivepwmright = map(analogRead(7),35,1024,10000,35000);
    setDrivePWM(drivepwmleft, LEFT, BACKWARD);
    setDrivePWM(drivepwmright, RIGHT, BACKWARD);
}

void Led_Empty()
{
  pixels.setPixelColor(i, pixels.Color(0,255,0));
  pixels.show();
}

void Led_Loaded()
{
  pixels.setPixelColor(i, pixels.Color(255,0,0));
  pixels.show();
}



















//if(analogRead(0)>300&&analogRead(1)>300&&analogRead(2)>300&&analogRead(3)>300&&analogRead(4)>300&&analogRead(5)>300&&analogRead(6)>300&&analogRead(7)>300)
  //{
   // stepcount++;
  //}
  //if(stepcount == 5)
  //{
   // delay(300);
    //setDrivePWMLeft(0);
    //setDrivePWMRight(0);
    //delay(100000);
  //}

  
