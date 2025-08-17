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

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Scraper.set(true); 
  Aligner.set(true);
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
  Drivetrain.driveFor(25.622, inches);
  Scraper.set(true);
  Intake.spin(fwd, 80, percentUnits::pct);
  Hopper.spin(fwd, 80, percentUnits::pct);
  Top.spin(fwd, 80, percentUnits::pct);
  wait(2, seconds); 
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
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);

  Brain.Screen.setPenColor(green);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(10, 10, 230, 220);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(240, 10, 230, 220);
  Brain.Screen.setFont(fontType::prop60);
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
