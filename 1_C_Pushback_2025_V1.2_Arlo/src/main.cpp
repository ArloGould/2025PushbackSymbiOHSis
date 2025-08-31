/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intake               motor         12              
// Drivetrain           drivetrain    18, 19, 1, 2    
// Hopper               motor         13              
// Top                  motor         11              
// Scraper              digital_out   G               
// Aligner              digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
bool side = false; 
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void autonselector(void) {
 if (Brain.Screen.pressing()) {

    // LEFT SIDE AUTON
    if (Brain.Screen.xPosition() <= 240) {
      side = true;
      Brain.Screen.setFillColor("#909090");
      Brain.Screen.drawRectangle(245, 15, 225, 215);
      Brain.Screen.setFont(fontType::prop60);
      Brain.Screen.printAt( 70, 136, "Left" );

      // RIGHT SIDE AUTON
    } else if (Brain.Screen.xPosition() > 240) {
      side = false;
      Brain.Screen.setFillColor("#909090");
      Brain.Screen.drawRectangle(15, 15, 225, 215);
      Brain.Screen.setFont(fontType::prop60);
      Brain.Screen.printAt( 300, 136, "Right" );
    }
  }
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Scraper.set(true); 
  Aligner.set(true);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor("#808080");
  Brain.Screen.drawRectangle(10, 10, 230, 220);
  Brain.Screen.drawRectangle(240, 10, 230, 220);
  Brain.Screen.setFillColor("#909090");
  Brain.Screen.drawRectangle(15, 15, 225, 215);
  Brain.Screen.drawRectangle(245, 15, 225, 215);
  Brain.Screen.setFont(fontType::prop60);
  Brain.Screen.printAt( 70, 136, "Left" );
  Brain.Screen.setPenColor(black);
  Brain.Screen.printAt( 300, 136, "Right" );
  
  

  while (true) {
    autonselector();
    wait(100, msec);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  
  if (!side) {
    // Drive the drivetrain for 10 inches at 100 rpm.

    // RIGHT SIDE AUTON

    // pick up group of cubes
    Hopper.spin(reverse, 80, percentUnits::pct);
    Intake.spin(reverse, 80, percentUnits::pct);
    Top.spin(reverse, 80, percentUnits::pct);
    Drivetrain.driveFor(65.07988, distanceUnits::cm, 190, rpm);
    wait(1,seconds);

    // stop spinning intake and hopper and list and stuff
    Hopper.stop();
    Intake.stop();
    Top.stop();

    // turn towards the middle goal
    Drivetrain.turnFor(-40, rotationUnits::deg, true);
    Drivetrain.driveFor(50, distanceUnits::cm, 190, rpm);
    wait(0.7, sec);

    // score
    Hopper.spin(forward, 80, percentUnits::pct);
    Intake.spin(forward, 30, percentUnits::pct);
    Top.spin(forward, 80, percentUnits::pct);
    wait(1.5, sec);

    // drive back
    Drivetrain.driveFor(-50, distanceUnits::cm, 190, rpm);

    // other stuff
    // Drivetrain.turnFor(115, rotationUnits::deg, true);
    // Drivetrain.driveFor(60.07988, distanceUnits::cm, 190, rpm);
    // Drivetrain.turnFor(-65, rotationUnits::deg, true);
    // Drivetrain.driveFor(60.07988, distanceUnits::cm, 190, rpm);
    // Drivetrain.turnFor(67, rotationUnits::deg, true);
    // Scraper.set(false);
    // Drivetrain.driveFor(49.07988, distanceUnits::cm, 190, rpm);
    // wait(2, sec);
    // Drivetrain.driveFor(-30, distanceUnits::cm, 190, rpm);
    // Scraper.set(true);
    // Drivetrain.turnFor(94, rotationUnits::deg, true);
    // Drivetrain.driveFor(135.07988, distanceUnits::cm, 190, rpm);

    // LEFT SIDE AUTON
  } else if (side) {

    // pick up cubes
    Hopper.spin(reverse, 80, percentUnits::pct);
    Intake.spin(reverse, 80, percentUnits::pct);
    Top.spin(reverse, 80, percentUnits::pct);
    Drivetrain.driveFor(65.07988, distanceUnits::cm, 190, rpm);
    wait(1,seconds);

    // other stuff
    Drivetrain.turnFor(-115, rotationUnits::deg, true);
    Drivetrain.driveFor(60.07988, distanceUnits::cm, 190, rpm);
    Drivetrain.turnFor(65, rotationUnits::deg, true);
    Drivetrain.driveFor(60.07988, distanceUnits::cm, 190, rpm);
    Drivetrain.turnFor(-67, rotationUnits::deg, true);
    Scraper.set(false);
    Drivetrain.driveFor(49.07988, distanceUnits::cm, 190, rpm);
    wait(2, sec);
    Drivetrain.driveFor(-30, distanceUnits::cm, 190, rpm);
    Scraper.set(true);
    Drivetrain.turnFor(-94, rotationUnits::deg, true);
    Drivetrain.driveFor(135.07988, distanceUnits::cm, 190, rpm);
  } 
  

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  
  while (1) {
    if (Controller1.ButtonL1.pressing()) {
        Hopper.spin(fwd, 80, percentUnits::pct);
        Top.spin(reverse, 80, percentUnits::pct);
        Intake.spin(reverse, 80, percentUnits::pct);
        Aligner.set(false);
      } else if (Controller1.ButtonL2.pressing()) {
        Hopper.spin(fwd, 80, percentUnits::pct);
        Top.spin(fwd, 80, percentUnits::pct);
        Intake.spin(reverse, 80, percentUnits::pct);
        Aligner.set(false);
      } else if (Controller1.ButtonR1.pressing()) {
        Hopper.spin(reverse, 80, percentUnits::pct);
        Intake.spin(reverse, 80, percentUnits::pct);
        Top.spin(reverse, 80, percentUnits::pct);
        Aligner.set(true);
      } else if (Controller1.ButtonR2.pressing()) {
        Hopper.spin(fwd, 80, percentUnits::pct);
        Intake.spin(fwd, 80, percentUnits::pct);
        Top.spin(fwd, 80, percentUnits::pct);
      } else {
        Hopper.stop(hold);
        Intake.stop(hold);
        Top.stop(hold);
      }
      
      // Scraper 

      if (Controller1.ButtonDown.PRESSED) {
        Scraper.set(false);
        Aligner.set(true);
      } else if (Controller1.ButtonUp.PRESSED) {
        Scraper.set(true);
      }

      if (Controller1.ButtonA.PRESSED) {
        Aligner.set(false);
      } else if (Controller1.ButtonB.PRESSED) {
        Aligner.set(true);
      }
   
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
