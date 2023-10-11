/* Clock1 is a kinetic sculpture developed by Rockey Ke in 2022. 
   The program below shows a version of the stepper motor test on Clock 1 in November, 2022. 
*/

#include <AccelStepper.h>
#include <MultiStepper.h>
#include "RTClib.h"

RTC_DS3231 rtc;

// Define the stepper motor and the pins that is connected to// (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper stepper1(1, 3, 2); //green-right
AccelStepper stepper2(1, 5, 4); //red-front
AccelStepper stepper3(1, 8, 7); //black-left

MultiStepper steppersControl;  // Create instance of MultiStepper

long gotoposition[3]; // An array to store the target positions for each stepper motor
long currentposition[3]; // am array to store the current position

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


int TargetA = 0;
int TargetB = 0;
int TargetC = 0;

int currentTargetA = 0;
int currentTargetB = 0;
int currentTargetC = 0;

//for testing
int testLength = 150;
int testSpeed = 5;


void setup() {

  // Adding the 3 steppers to the steppersControl instance for multi stepper control
  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);

  //set max speed of motors  
  stepper1.setMaxSpeed(testSpeed); // Set maximum speed value for the stepper
  stepper2.setMaxSpeed(testSpeed);
  stepper3.setMaxSpeed(testSpeed);

  // checkRTCpower();
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  Serial.begin(57600);
}

void loop() {
  //code to display rtc data
  printNowTime();
  randomMovement();
  //moveStepper(-0,-50,0);
  testRun();
}

////////////////////////////////////////////////////////////////////////////////functions


//move stepper to the new position and update current position
void moveStepper(int g,int r, int b){
 
  gotoposition[0] += g;
  gotoposition[1] += r;
  gotoposition[2] += b;
  
  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  //update and print out current position
  currentposition[0] = gotoposition[0];
  currentposition[1] = gotoposition[1];
  currentposition[2] = gotoposition[2];

  Serial.print("Current Position of Right,Front,Left is : ");
  Serial.print(currentposition[0]);
  Serial.print(" ");
  Serial.print(currentposition[1]);
  Serial.print(" ");
  Serial.println(currentposition[2]);
}


//Print RTC Time right now
void printNowTime(){
    //code to display rtc data
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

//To test simple movement of arduino
void testRun(){
  currentTargetA = testLength;
  currentTargetB = -1*testLength;
  currentTargetC = 0;
  
  gotoposition[0] = currentTargetA;
  gotoposition[1] = currentTargetB;
  gotoposition[2] = currentTargetC;
  
  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  delay(50);

  gotoposition[0] = 0;
  gotoposition[1] = 0;
  gotoposition[2] = 0;

  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();

  delay(50);

  currentTargetA = 0;
  currentTargetB = testLength;
  currentTargetC = -1*testLength;
  
  gotoposition[0] = currentTargetA;
  gotoposition[1] = currentTargetB;
  gotoposition[2] = currentTargetC;
  
  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  delay(50);

  gotoposition[0] = 0;
  gotoposition[1] = 0;
  gotoposition[2] = 0;

  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();

  currentTargetA = testLength;
  currentTargetB = testLength;
  currentTargetC = testLength;
  
  gotoposition[0] = currentTargetA;
  gotoposition[1] = currentTargetB;
  gotoposition[2] = currentTargetC;
  
  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  delay(50);

  gotoposition[0] = 0;
  gotoposition[1] = 0;
  gotoposition[2] = 0;

  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();

  currentTargetA = testLength;
  currentTargetB = 0;
  currentTargetC = -1*testLength;
  
  gotoposition[0] = currentTargetA;
  gotoposition[1] = currentTargetB;
  gotoposition[2] = currentTargetC;
  
  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  delay(50);

  gotoposition[0] = 0;
  gotoposition[1] = 0;
  gotoposition[2] = 0;

  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();
}

void checkRTCpower(){
 if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void randomMovement(){

  int path[3] ;
  int randDir = random(1,8);
  int randInt = random(50,800);
  //print to display
  Serial.println(randDir);
  Serial.println(randInt);

  if (randDir == 1){
    path[0] = randInt;
    path[1] = -1*randInt;
    path[2] = 0;
  }

  
  if (randDir == 2){
    path[0] = -1*randInt;
    path[1] = randInt;
    path[2] = 0;
  }

  
  if (randDir == 3){
    path[0] = 0;
    path[1] = randInt;
    path[2] = -1*randInt;
  }

  if (randDir == 4){
    path[0] = 0;
    path[1] = -1*randInt;
    path[2] = randInt;
  }

  if (randDir == 5){
    path[0] = randInt;
    path[1] = 0;
    path[2] = -1*randInt;
  }

  if (randDir == 6){
    path[0] = -1*randInt;
    path[1] = 0;
    path[2] = randInt;
  }

    if (randDir == 7){
    path[0] = randInt;
    path[1] = randInt;
    path[2] = randInt;
  }

  if (randDir == 8){
    path[0] = -1*randInt;
    path[1] = -1*randInt;
    path[2] = -1*randInt;
  }

  delay(5);
  
  gotoposition[0] += path[0];
  gotoposition[1] += path[1];
  gotoposition[2] += path[2];
  
  steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  //update and print out current position
  currentposition[0] = gotoposition[0];
  currentposition[1] = gotoposition[1];
  currentposition[2] = gotoposition[2];

  Serial.print("Current Position of Right,Front,Left is : ");
  Serial.print(currentposition[0]);
  Serial.print(" ");
  Serial.print(currentposition[1]);
  Serial.print(" ");
  Serial.println(currentposition[2]);
}
