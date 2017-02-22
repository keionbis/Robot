#include"headers.h"
Servo FourbarServo;
Servo GripperServo;
int pos = 22;
int runs = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_pin, NEO_GRB + NEO_KHZ800);
void setup() {
  FourbarServo.attach(9);
  GripperServo.write(100);
  Serial.begin(15200);
  initDrivePWM();
}

void loop() {
  switch(DriveStates)
  {
    case LINE_FOLLOW :
      Line_Follow();
      break;
    case INTERSECTION :
      break;
    case TURN_RIGHT :
      break;
    case TURN_LEFT:
      break;
    case DOCKED:
      break;
    case REMOVE_ROD:
      void Arm_State()
      break;
    case PLACE_ROD:
      void Arm_State()
      break;
    case REVERSE:
      break;
    case STOP:
      break;
    case GRIPPER_STRAIGHT:
      break;
  }
    delay(15);
}
