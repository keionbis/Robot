#include"headers.h"

void Line_Follow()
{
int drivepwmright, drivepwmleft;
  drivepwmleft = map(analogRead(2),35,1024,35000,10000);
   drivepwmright = map(analogRead(7),35,1024,35000,10000);
    setDrivePWM(drivepwmleft, LEFT, FORWARD);
    setDrivePWM(drivepwmright, RIGHT, FORWARD);
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
