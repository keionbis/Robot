#include"headers.h"
Servo FourbarServo;
Servo GripperServo;

//**********************************************************************************************************
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


//**********************************************************************************************************

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




//*******************************************************************************************************

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


//*******************************************************************************************************


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



//******************************************************************************************************

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





//************************************************************************************



//**********************************************************************************
void Reverse()
{ 
    
    Read_Line_Sensor();
    while(!Check_Line_States()&&currentState!=STOP)
    {
    Read_Line_Sensor();
    drivepwmleft = map(analogRead(2),35,1024, 18000, 35000);
    drivepwmright = map(analogRead(7),35,1024, 18000, 35000 );
    setDrivePWM(drivepwmleft, LEFT, BACKWARD);
    setDrivePWM(drivepwmright, RIGHT, BACKWARD);
    delay(15);
    Start_Stop_Message();
    }
    setDrivePWM( 16380*2, LEFT, FORWARD);
    setDrivePWM( 16380*2, RIGHT, FORWARD);
      delay(1000);
      Stop();
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

