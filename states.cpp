#include"headers.h"
#include <Adafruit_NeoPixel.h>
int drivepwmright, drivepwmleft;
ArmStates currentArmState;
DriveStates prevState;
Servo FourbarServo;
Servo GripperServo;
int runs = 0;
int pos;
int Intersections = -1;
int Left1sens, Left2sens, Left3sens, Center_Leftsens, Center_Rightsens, Right3sens, Right2sens, Right1sens;
Intersection_States ReactorStates[8];
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_pin, NEO_GRB + NEO_KHZ800);

void Standby()
{
  delay(50);
}
void Interrupt_Setup()
{
  attachInterrupt(digitalPinToInterrupt(Front_Limit_Switch),State_to_Docked,RISING);
  attachInterrupt(digitalPinToInterrupt(Top_Limit_Switch),State_to_Arm_Raised,RISING);
  attachInterrupt(digitalPinToInterrupt(Middle_Limit_Switch),State_to_Arm_Straight,RISING);
  attachInterrupt(digitalPinToInterrupt(Bottom_Limit_Switch),State_to_Arm_Down,RISING);
}

void Servo_Setup()
{
  FourbarServo.attach(9);
  GripperServo.write(10);
}

void Read_Line_Sensor()
{
   Left1sens = analogRead(Left1);
   Left2sens = analogRead(Left2);
   Left3sens = analogRead(Left3);
   Center_Leftsens = analogRead(Center_Left);
   Center_Rightsens = analogRead(Center_Right);
   Right3sens = analogRead(Right3);
   Right2sens =analogRead(Right2);
   Right1sens =analogRead(Right1);
}
int Check_Line_States()
{
   if(Left1sens>350 && Left2sens>350 && Left3sens>350 && Center_Leftsens>350 && Center_Rightsens>350 && Right3sens>350 && Right2sens>350 && Right1sens>350)
   {
    return 1;
   }
   else{
   return 0;
   }
}
void Enter_Intersection_State()
{
  Read_Line_Sensor();
  if(Check_Line_States() == 1)
  {
    currentState = INTERSECTION;
    Intersections = Intersections+2;
  }
  //delay(50);
}

void Line_Follow()
{
    Read_Line_Sensor();
    drivepwmleft = map(analogRead(2),35,1024,27500,10000);
    drivepwmright = map(analogRead(7),35,1024,27500,10000);
    Serial.println(drivepwmleft);
    setDrivePWM(drivepwmleft, LEFT, FORWARD);
    setDrivePWM(drivepwmright, RIGHT, FORWARD);
    Enter_Intersection_State();
}

void Turn_Right()
{
    setDrivePWM(65525, LEFT, FORWARD);
    setDrivePWM(65525, RIGHT, BACKWARD);
}

void Turn_Left()
{
   setDrivePWM(65525, LEFT, BACKWARD);
   setDrivePWM(65525, RIGHT, FORWARD);
   delay(375);
}

void Lift_Fourbar()
{
  while(currentArmState != ARMRAISED){
  pos = pos-1;
  FourbarServo.write(pos);
  delay(10);
  }
}

void Lower_Fourbar()
{
  while(currentArmState != ARMLOWERED){
  pos = pos+1;
  FourbarServo.write(pos);
  delay(10);

  }

}
void Extend_Fourbar()
{

  Lift_Fourbar();
  while(currentArmState != ARMSTRAIGHT)
  {
    pos = pos+1;
    FourbarServo.write(pos);
    delay(10);
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
  Read_Line_Sensor();
  while(Left1sens<350 && Left2sens<350 && Left3sens<350 && Center_Leftsens<350 && Center_Rightsens<350 && Right3sens<350 && Right2sens<350 && Right1sens<350)
    {
    drivepwmleft = map(analogRead(2),35,1024,15000,27500);
    drivepwmright = map(analogRead(7),35,1024,15000,27500);
    setDrivePWM(drivepwmleft, LEFT, BACKWARD);
    setDrivePWM(drivepwmright, RIGHT, BACKWARD);
    }
    setDrivePWM(35000, LEFT, FORWARD);
    setDrivePWM(35000, RIGHT, FORWARD);
    delay(15);
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


void Start_Stop_Message()
{
  if((comms.getMessageByte(0))==4)
  {
    prevState = currentState;
    currentState = STOP;
  }
  if((comms.getMessageByte(0))==4)
  {
    currentState = prevState;
  }
  
}
