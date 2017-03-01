#include"headers.h"
#include <Adafruit_NeoPixel.h>
int drivepwmright, drivepwmleft;
ArmStates currentArmState;
DriveStates prevState;
Servo FourbarServo;
Servo GripperServo;
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
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_pin, NEO_GRB + NEO_KHZ800);

void Standby()
{
  delay(50);
}
void Separate_Messages()
{
  NewTubes[0] = ReactorStates[1];
  Storage[0] = ReactorStates[0];
  NewTubes[1] = ReactorStates[3];
  Storage[1] = ReactorStates[2];
  NewTubes[2] = ReactorStates[5];
  Storage[2] = ReactorStates[4];
  NewTubes[3] = ReactorStates[7];
  Storage[3] = ReactorStates[6];
  
}
void Separate_Messages_2()
{
  NewTubes[3] = ReactorStates[1];
  Storage[3] = ReactorStates[0];
  NewTubes[2] = ReactorStates[3];
  Storage[2] = ReactorStates[2];
  NewTubes[1] = ReactorStates[5];
  Storage[1] = ReactorStates[4];
  NewTubes[0] = ReactorStates[7];
  Storage[0] = ReactorStates[6];
  
}

int Find_Empty_Storage()
{
  if((Storage[0] == FULL)&&(Storage[1] == FULL)&&(Storage[2] == FULL)&&(Storage[3] == FULL)) 
   {
    Stop();
    currentState = STANDBY;
    //return(0);
    }
  for(int i = 0;i<4;i++)
  {
    if(Storage[i] == EMPTY)
    {
      
      nums = i+1;
      break;

    }
  }
}
void Find_Full_NewTubes()
{
  if(NewTubes[0] == EMPTY &&NewTubes[1] == EMPTY&&NewTubes[2] == EMPTY&&NewTubes[3] == EMPTY) 
   {
    Stop();
    currentState = STANDBY;
    //return(0);
    }
  for(int i = 0;i<4;i++)
  {
    if(NewTubes[i] == FULL)
    {
      picks = i+1;
      
      break;
    }
  }
  }
void Docked()
{
      Stop();
      Intersections = 0;
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
      Turn_180();
      currentState = LINE_FOLLOW;
      dockval = 1;
      
}
void Docked_1()
{
      Find_Full_NewTubes();
      Stop();
      Extend_Fourbar();
      Open_Gripper();
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
      Led_Empty();
      Lift_Fourbar();
      setDrivePWM(32762, RIGHT, BACKWARD);
      setDrivePWM(32762, LEFT, BACKWARD);
      delay(1200);
      Turn_180();
      currentState = LINE_FOLLOW;
      dockval = 0;
      
      
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
  FourbarServo.attach(Fourbar_pin);
  GripperServo.attach(Gripper_pin);
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
bool Check_Line_States()
{
   if( Left2sens>350 && Left3sens>350 && Center_Leftsens>350 && Center_Rightsens>350 && Right3sens>350 && Right2sens>350)
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
  
  if((Check_Line_States() == 1) &&(currentState == LINE_FOLLOW)&&(dockval!= 0)&&(dockval!= 3))
  {
    Intersections = Intersections+1;
    if(dockSide == 0)
    {
    currentState = INTERSECTION;
    }
    else if (dockSide == 1)
    {
      currentState = INTERSECTION_2;
     
    }
    
  }
  //delay(50);
}

void Line_Follow()
{
    Read_Line_Sensor();
    drivepwmleft = map(analogRead(2),35,1024,65525/1.25,8000);
    drivepwmright = map(analogRead(7),35,1024,65525/1.25,8000);
    //Serial.println(drivepwmleft);
    setDrivePWM(drivepwmleft, LEFT, FORWARD);
    setDrivePWM(drivepwmright, RIGHT, FORWARD);
    Enter_Intersection_State();
}

void Line_Follow_Arms()
{
    Read_Line_Sensor();
    drivepwmleft = map(analogRead(2),35,1024,65525,10000);
    drivepwmright = map(analogRead(7),35,1024,65525,10000);
    //Serial.println(drivepwmleft);
    setDrivePWM(drivepwmleft, LEFT, FORWARD);
    setDrivePWM(drivepwmright, RIGHT, FORWARD);
    Enter_Intersection_State();
}

void Turn_Left()
{ 
 while(analogRead(Right1)<400){
  setDrivePWM(20000, LEFT, FORWARD);
   setDrivePWM(20000, RIGHT, BACKWARD);
  }
  while(analogRead(Center_Right)<300){
  setDrivePWM(16500, LEFT, FORWARD);
   setDrivePWM(16500, RIGHT, BACKWARD);
   //delay(1300);
}
   Stop();
 

}

void Turn_Right()
{
  while(analogRead(Left1)<275){
  setDrivePWM(22000, RIGHT, FORWARD);
   setDrivePWM(22000, LEFT, BACKWARD);
  }
  while(analogRead(Center_Left)<275){
  setDrivePWM(20000, RIGHT, FORWARD);
   setDrivePWM(20000, LEFT, BACKWARD);
   //delay(1300);
}
   Stop();
 
}
void Turn_180()
{
  while(analogRead(Left1)<275){
  setDrivePWM(32762, RIGHT, FORWARD);
   setDrivePWM(32762, LEFT, BACKWARD);
  }
  while(analogRead(Center_Left)<300){
  setDrivePWM(32762, RIGHT, FORWARD);
   setDrivePWM(32762, LEFT, BACKWARD);
   //delay(1300);
}
   Stop();
 
}

void Lift_Fourbar()
{
  while(currentArmState != ARMRAISED){
  pos = pos-1;
  FourbarServo.write(pos);
  delay(10);
  }
  FourbarServo.write(pos+15);
}

void Lower_Fourbar()
{
  while(currentArmState != ARMLOWERED){
  pos = pos+1;
  FourbarServo.write(pos);
  delay(10);

  }
   //FourbarServo.write(pos-10);
  delay(150);

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
  delay(150);
  
}
void Extend_Fourbar_Extra()
{
  FourbarServo.write(pos-10);
}
void Open_Gripper()
{
  GripperServo.write(80);
  delay(150);
}

void Close_Gripper()
{
  GripperServo.write(150);
  delay(150);
}

void Reverse()
{
    Read_Line_Sensor();
    while(!Check_Line_States())
    {
    Read_Line_Sensor();
    drivepwmleft = map(analogRead(2),35,1024, 18000, 35000);
    drivepwmright = map(analogRead(7),35,1024, 18000, 35000 );
    setDrivePWM(drivepwmleft, LEFT, BACKWARD);
    setDrivePWM(drivepwmright, RIGHT, BACKWARD);
    delay(15);
    }
    setDrivePWM( 16380*2, LEFT, FORWARD);
    setDrivePWM( 16380*2, RIGHT, FORWARD);
      delay(1000);
      Stop();
      
    
    
}

void Led_Empty()
{
  pixels.setPixelColor(1, pixels.Color(0,255,0));
  pixels.show();
}

void Led_Off()
{
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  pixels.show();
}

void Led_Loaded()
{
  pixels.setPixelColor(1, pixels.Color(255,0,0));
  pixels.show();
  delay(100);
  pixels.setPixelColor(1, pixels.Color(0,0,0));
  pixels.show();
  
}

void Stop()
{
  setDrivePWM(0, LEFT, BACKWARD);
  setDrivePWM(0, RIGHT, BACKWARD);
}
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

void State_to_Arm_Raised()
{
  currentArmState = ARMRAISED;
  //Serial.println("F");
}
void State_to_Arm_Straight()
{
  currentArmState = ARMSTRAIGHT;
  //Serial.println("A");
}

void State_to_Arm_Down()
{
  currentArmState = ARMLOWERED;
  //Serial.println("B");
}


void Start_Stop_Message()
{
  if((comms.getMessageByte(0))==4)
  {
    prevState = currentState;
    currentState = STOP;
  }
  if((comms.getMessageByte(0))==5)
  {
    currentState = prevState;
  }
  
}
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
      Turn_Right();
      Stop();
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

void Run_During_Intersection_2()
{     
      
      Find_Empty_Storage();
      if(Intersections == nums)
      { 
      setDrivePWM( 27000, LEFT, FORWARD);
      setDrivePWM( 27000, RIGHT, FORWARD);
      delay(1000);
      Stop();
      Turn_Left();
      Stop();
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
