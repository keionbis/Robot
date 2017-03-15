#include"headers.h"
#include <Adafruit_NeoPixel.h>
int drivepwmright, drivepwmleft;
ArmStates currentArmState;
DriveStates prevState;

int runs = 0;
int nums  = 0;
int picks = 0;
ClawStates Stations = Depositing;
Intersection_States Storage[4], NewTubes[4];
int pos;
int Testing = 0;
int Deposit_intersection, Refuel_Intersection;
int dockSide = 0;
int dockval = 0;
int Intersections = 0;
int Left1sens, Left2sens, Left3sens, Center_Leftsens, Center_Rightsens, Right3sens, Right2sens, Right1sens;
Intersection_States ReactorStates[8];
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_pin, NEO_GRB + NEO_KHZ800);
//************************************************************************************************************************************

//************************************************************************************************************************************

//************************************************************************************************************************************

//************************************************************************************************************************************

//************************************************************************************************************************************

void Standby()
{
  delay(50);
}

//************************************************************************************************************************************


void Docked()
{
      Stop();
      Intersections = 0;
      Start_Stop_Message();
      Open_Gripper();
      
      currentArmState == ARMSTRAIGHT;
      Lower_Fourbar();
      Close_Gripper();
      Led_Empty();
      Lift_Fourbar();
      Stop();
      setDrivePWM(32762, RIGHT, BACKWARD);
      setDrivePWM(32762, LEFT, BACKWARD);
      delay(1200);
      Start_Stop_Message();
      Turn_180();
      Start_Stop_Message();
      currentState = LINE_FOLLOW;
      dockval = 1;
      
}

//************************************************************************************************************************************


void Docked_1()
{
      Find_Full_NewTubes();
      Stop();
      Extend_Fourbar();
      Open_Gripper();
      Led_Off();
      Lift_Fourbar();
      Reverse();
      if(picks == nums)
      {
        Turn_Left();
        Turn_Left();
        Stop();
        Line_Follow();
        Stop();
        setDrivePWM(32762/2, RIGHT, BACKWARD);
        setDrivePWM(32762/2, LEFT, BACKWARD);
        delay(120);
        Stop();
        dockval = 2;
        currentState = LINE_FOLLOW;
      }
      if(picks > nums)
      {
        if (dockSide == 0){
        Turn_Left();
        }
        else if (dockSide == 1){
        Turn_Right();
        }
        setDrivePWM(32762, RIGHT, BACKWARD);
        setDrivePWM(32762, LEFT, BACKWARD);
        delay(120);
        Reverse();
        setDrivePWM( 16380*2, LEFT, FORWARD);
        setDrivePWM( 16380*2, RIGHT, FORWARD);
        delay(900);
        while(Intersections< picks)
        {
          if (Check_Line_States() == 1)
          {
            Intersections++;
          }
          
        }
        Stop();
        if (dockSide == 0){
        Turn_Left();
        }
        else if (dockSide == 1){
          Turn_Right();
        }
        
        Stop();
        Line_Follow();
        Stop();
        setDrivePWM(32762/2, RIGHT, BACKWARD);
        setDrivePWM(32762/2, LEFT, BACKWARD);
        delay(120);
        Stop();
        dockval = 2;
        currentState = LINE_FOLLOW;
       
      }
      if(picks < nums)
      {
        if (dockSide == 1){
        Turn_Left();
        }
        else if (dockSide == 0){
        Turn_Right();
        }
        setDrivePWM(32762, RIGHT, BACKWARD);
      setDrivePWM(32762, LEFT, BACKWARD);
      delay(120);
       Reverse();
       setDrivePWM( 16380*2, LEFT, FORWARD);
        setDrivePWM( 16380*2, RIGHT, FORWARD);
        delay(800);
       while(Intersections> picks)
        {
          if (Check_Line_States() == 1)
          {
            Intersections--;
          }
          
        }
        if (dockSide == 1){
        Turn_Left();
        }
        else if (dockSide == 0){
          Turn_Right();
        }
        Stop();
        Line_Follow();
        Stop();
        setDrivePWM(32762/2, RIGHT, BACKWARD);
        setDrivePWM(32762/2, LEFT, BACKWARD);
        delay(120);
        Stop();
        dockval = 2;
        currentState = LINE_FOLLOW;
       
      }
      NewTubes[picks-1] = EMPTY;
}

//************************************************************************************************************************************

void Docked_2()
{
  Stop();
      Extend_Fourbar();
      Close_Gripper();
      Led_Loaded();
      delay(150);
      Reverse();
      Turn_Left();
      Stop();
      setDrivePWM(32762/2, RIGHT, BACKWARD);
      setDrivePWM(32762/2, LEFT, BACKWARD);
      delay(120);
      dockval = 3;
      dockSide = 1;
      currentState = LINE_FOLLOW;
}

//************************************************************************************************************************************


void Docked_2_2()
{
      Stop();
      Extend_Fourbar();
      Close_Gripper();
      Led_Loaded();
      delay(150);
      Reverse();
      Turn_Right();
      Stop();
      setDrivePWM(32762/2, RIGHT, BACKWARD);
      setDrivePWM(32762/2, LEFT, BACKWARD);
      delay(120);
      dockval = 3;
      dockSide = 0;
      currentState = LINE_FOLLOW;
}

//************************************************************************************************************************************


void Docked_3()
{
  Stop();
      setDrivePWM(32762/2, RIGHT, BACKWARD);
      setDrivePWM(32762/2, LEFT, BACKWARD);
      delay(180);
      Stop();
      currentArmState = ARMRAISED;
      Lower_Fourbar();
      Open_Gripper();
      Led_Off();
      Lift_Fourbar();
      setDrivePWM(32762, RIGHT, BACKWARD);
      setDrivePWM(32762, LEFT, BACKWARD);
      delay(1200);
      Turn_180();
      currentState = LINE_FOLLOW;
      dockval = 0;
      
      
}

//************************************************************************************************************************************

void Stop()
{
  setDrivePWM(0, LEFT, BACKWARD);
  setDrivePWM(0, RIGHT, BACKWARD);
}



//************************************************************************************************************************************

void State_to_Docked()
{
  if (dockval == 0)
  {
    currentState = DOCKED;
  }
  else if (dockval == 1)
  {
    currentState = DOCKED1;
    
    
  }
  else if(dockval == 2){
    if(dockSide == 0)
    {
    currentState = DOCKED2;
    }
    else if(dockSide == 1)
    {
      currentState = DOCKED2_2;
    }
  }
  else if(dockval == 3){
    currentState = DOCKED3;
  }
}

//************************************************************************************************************************************



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

//************************************************************************************************************************************



void Start_Stop_Message()
{
  if((comms.getMessageByte(0))==4&&(comms.getMessageByte(2) == 0x03 || comms.getMessageByte(2) == 0x00))
  {
    if(currentState != STOP)
    {
    prevState = currentState;
    currentState = STOP;
    }
  }
  if((comms.getMessageByte(0))==5&&(comms.getMessageByte(2) == 0x03 || comms.getMessageByte(2) == 0x00))
  {
    currentState = prevState;
  }
  while(currentState == STOP)
  {
    Stop();
    Start_Stop_Message();
  }
}

//************************************************************************************************************************************



void Run_During_Intersection()
{
      Find_Empty_Storage();
      Serial.println(nums);
      if(Intersections == nums)
      { 
      setDrivePWM( 27000, LEFT, FORWARD);
      setDrivePWM( 27000, RIGHT, FORWARD);
      delay(1000);
      Stop();
      Start_Stop_Message();
      Turn_Right();
      Stop();
      Start_Stop_Message();
      Stations == Filling;
      Storage[nums-1] = FULL;
      currentState = LINE_FOLLOW;
      }
      else if (Intersections != nums)
      {
       setDrivePWM( 27000, LEFT, FORWARD);
      setDrivePWM( 27000, RIGHT, FORWARD);
      delay(1000);
      
      currentState = LINE_FOLLOW;
      }
      
      

}

//************************************************************************************************************************************




void Run_During_Intersection_2()
{     
      
      Find_Empty_Storage();
      if(Intersections == nums)
      { 
      setDrivePWM( 27000, LEFT, FORWARD);
      setDrivePWM( 27000, RIGHT, FORWARD);
      delay(1000);
      Stop();
      Start_Stop_Message();
      Turn_Left();
      Stop();
      Start_Stop_Message();
      Stations == Filling;
       Storage[nums-1] = FULL;
      currentState = LINE_FOLLOW;
      }
      else if (Intersections != nums)
      {
       setDrivePWM( 27000, LEFT, FORWARD);
      setDrivePWM( 27000, RIGHT, FORWARD);
      delay(1000);
     
      currentState = LINE_FOLLOW;
      
      }
      
      

}
