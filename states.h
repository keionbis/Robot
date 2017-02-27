#ifndef STATES_H
#define STATES_H
//*****************************State Definitions****************************//

typedef enum DriveStates {
    STANDBY,  // Robot will sit and wait patiently
    LINE_FOLLOW , // Only one solid centered line to follow
    INTERSECTION , // Come to an intersection
    DOCKED,  // Docked at the base of the rods
    STOP //stop all motors

};

//extern int currentState;
typedef enum DriveSide {
  LEFT = 5, //Pin numbers
  RIGHT = 2
};

typedef enum TurnDirection {
  Left,
  Right
};

typedef enum DriveDirection {
  FORWARD = 1,
  BACKWARD = 0
};
typedef enum ArmStates{
  ARMRAISED,
  ARMSTRAIGHT,
  ARMLOWERED
};

typedef enum Intersection_States{
  FULL,
  EMPTY
};
//*****************************Variable Definitions****************************//
extern DriveStates currentState;
extern TurnDirection TurnDir;
extern DriveStates prevState;
extern ArmStates currentArmState;
extern Intersection_States ReactorStates[8];
extern Intersection_States IntersectionState;
extern Servo FourbarServo;
extern Servo GripperServo;
extern int Intersections;
extern int Left1sens, Left2sens, Left3sens, Center_Leftsens, Center_Rightsens, Right3sens, Right2sens, Right1sens;
extern unsigned long timeForHeartbeat;
//extern Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_pin, NEO_GRB + NEO_KHZ800);
//*****************************Function Definitions****************************//
void Line_Follow();
void Turn_Right();
void Turn_Left();
void Lift_Fourbar();
void Lower_Fourbar();
void Open_Gripper();
void Close_Gripper();
void Reverse();
void Led_Empty();
void Led_Loaded();
void Stop();
void Servo_Setup();
void Interrupt_Setup();
void Read_Line_Sensor();
void State_to_Arm_Down();
void State_to_Arm_Straight();
void State_to_Arm_Raised();
void State_to_Docked();
void Reactor_State_Set();
void Enter_Intersection_State();
void Standby();
void Start_Stop_Message();
void Extend_Fourbar();
//***************************************************************************//
#define LEFT_REVERSED 1
#define RIGHT_REVERSED 0
#define PWM_FREQ 16000 //this isn't in rates because it isn't a control loop but the hardware timer PWM freq
#define CLOCK_FREQ 16000000
static const unsigned int PWM_COUNT = (((CLOCK_FREQ/PWM_FREQ))-1);// make constant to avoid recomputing each time

static void initDrivePWM() {
    pinMode(LEFT_PWM_PIN,OUTPUT);
    pinMode(RIGHT_PWM_PIN,OUTPUT);
    pinMode(LEFT_DIR_PIN,OUTPUT);
    pinMode(RIGHT_DIR_PIN,OUTPUT);
    TCCR3B = _BV(WGM33)|_BV(WGM32)|_BV(CS30);
    TCCR3A = _BV(COM3A1)|_BV(COM3B1)|_BV(WGM31);//WGM3_14; //COM3 and WGM3 = 14 _BV(COM3A0)
    ICR3 = PWM_COUNT; // to count up to
    OCR3A = 0; //default to off
    OCR3B = 0; //default to off

}

static void setDrivePWM(unsigned int duty_cycle, DriveSide side,DriveDirection newDir) {
  //Sets the new PWM duty cycle; duty cycle scaled from 0 to 65535 for 0 - 100 percent
  constrain(duty_cycle,0,65535);
  if(side == LEFT)
  {
    OCR3A = ((duty_cycle*(unsigned long)PWM_COUNT)/65535);
    if(newDir == FORWARD)
    {
      if(LEFT_REVERSED)
        digitalWrite(LEFT_DIR_PIN,BACKWARD);
      else
        digitalWrite(LEFT_DIR_PIN,FORWARD);
    }
    else if(newDir == BACKWARD)
    {
      if(LEFT_REVERSED)
        digitalWrite(LEFT_DIR_PIN,FORWARD);
      else
        digitalWrite(LEFT_DIR_PIN,BACKWARD);
    }
  }
  else if (side == RIGHT)
  {
    OCR3B = ((duty_cycle*(unsigned long)PWM_COUNT)/65535);
    if(newDir == FORWARD)
    {
      if(RIGHT_REVERSED)
        digitalWrite(RIGHT_DIR_PIN,BACKWARD);
      else
        digitalWrite(RIGHT_DIR_PIN,FORWARD);
    }
    else if(newDir == BACKWARD)
    {
      if(RIGHT_REVERSED)
        digitalWrite(RIGHT_DIR_PIN,FORWARD);
      else
        digitalWrite(RIGHT_DIR_PIN,BACKWARD);
    }
  }
}

#endif
