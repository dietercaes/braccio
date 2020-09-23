#include <Braccio.h>
#include <Servo.h>
#include <math.h>

// CONSTANTS
// X and Z values are the given coordinates for the top joint of the first three movable armpieces.
// This program doesn't use the full functionality of the braccio to simplify creating the code.
// X and Z value of the first joint won't change.
const unsigned int XVALUE = 0;
const unsigned int ZVALUE = 195;
// C and B are the lenghts of the second and thrird arm joints.
const int C = 125;
const int B = 110;

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;


void moveToPosition(unsigned int x, unsigned int z){
  // calculating the length of the vector from 0, 195 to target point x, z using 
  double lengthBCvector = sqrt((XVALUE - x) * (XVALUE - x) + (ZVALUE - z) * (ZVALUE - z));

  // angles
  double angleA;
  double angleB;
  double angleC;

  // lengths
  int a = lengthBCvector;
  int b = B;
  int c = C;

  // calculating the angles of the triangle consisting of vectors B, C and BC using the lengths of the sides.
  // # TODO: check sum to be 180°, fix calculations using proper Arduino code.
  angleA = acos(((b*b) + (c*c) - (a*a))/(2 * b * c));
  angleB = acos((a*a + c*c - b*b)/(2 * a * c));
  angleC = acos((a*a + b*b - c*c)/(2 * a * b));  

  // move Braccio to correct position.
  Braccio.ServoMovement(20,   90, 90, round(angleA), round(angleB), 90, 10);
}

void setup() {
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Braccio.begin();
  Serial.begin(9600);
}

void loop() {
   /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
  moveToPosition(78, 400);
}
