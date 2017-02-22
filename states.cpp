#include"headers.h"
#include <Adafruit_NeoPixel.h>
int drivepwmright, drivepwmleft;
Servo FourbarServo;
Servo GripperServo;
int runs = 0;
int pos;
int Intersections;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_pin, NEO_GRB + NEO_KHZ800);

void Interrupt_Setup()
{
  attachInterrupt(digitalPintoInterrupt(Front_Limit_Switch),State_to_Docked,RISING);
  attachInterrupt(digitalPintoInterrupt(Top_Limit_Switch),State_to_Arm_Raised,RISING);
  attachInterrupt(digitalPintoInterrupt(Middle_Limit_Switch),State_to_Arm_Straight,RISING);
  attachInterrupt(digitalPintoInterrupt(Bottom_Limit_Switch),State_to_Arm_Down,RISING);
}

void Servo_Setup()
{
  FourbarServo.attach(9);
  GripperServo.write(10);
}

void Read_Line_Sensor()
{
  int Left1sens = analogRead(Left1);
  int Left2sens = analogRead(Left2);
  int Left3sens = analogRead(Left3);
  int Center_Leftsens = analogRead(Center_Left);
  int Center_Rightsens = analogRead(Center_Right);
  int Right3sens = analogRead(Right3);
  int Right2sens =analogRead(Right2);
  int Right1sens =analogRead(Right1);

  if(Left1sens>350 && Left2sens>350 && Left3sens>350 && Center_Leftsens>350 && Center_Rightsens>350 && Right3sens>350 && Right2sens>350 && Right1sens>350)
  {
    currentState = INTERSECTION();
    Intersections = Intersections+1;
  }
  //delay(50);
}

void Line_Follow()
{
    Read_Line_Sensor();
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
  if(runs != 1)
  {
    FourbarServo.write(22);
    runs = 1;
  }
  if(currentArmState != ARMRAISED){
  pos = pos-1;
  FourbarServo.write(pos);
  }
}

void Lower_Fourbar()
{
  if(runs != 1)
  {
    FourbarServo.write(129);
    runs = 1;
  }
  if(currentArmState != ARMLOWERED){
  pos = pos+1;
  FourbarServo.write(pos);

  }

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
  pixels.setPixelColor(1, pixels.Color(0,255,0));
  pixels.show();
}

void Led_Loaded()
{
  pixels.setPixelColor(1, pixels.Color(255,0,0));
  pixels.show();
}

void Stop()
{
  setDrivePWM(0, LEFT, BACKWARD);
  setDrivePWM(0, RIGHT, BACKWARD);
}
void State_to_Docked()
{
  currentState = DOCKED;
}
void State_to_Arm_Raised()
{
  currentArmState = ARMRAISED;
}

void State_to_Arm_Straight()
{
  currentArmState = ARMSTRAIGHT;
}
void State_to_Arm_Down()
{
  currentArmState = ARMLOWERED;
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
