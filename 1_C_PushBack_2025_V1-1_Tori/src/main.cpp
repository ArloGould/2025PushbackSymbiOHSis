#include "main.h"
#include "lemlib/api.hpp"

#include "../include/toriLibInclude/devices.hpp"
#include "../include/toriLibInclude/subsystems.hpp"

//left and right sides of the drivetrain
pros::MotorGroup right_dt({RIGHTPORT1, RIGHTPORT2, RIGHTPORT3}, pros::MotorGearset::blue);
pros::MotorGroup left_dt({LEFTPORT1, LEFTPORT2, LEFTPORT3}, pros::MotorGearset::blue);

pros::Imu imu(IMU);

lemlib::Drivetrain Drivetrain
(
	&left_dt, //drivetrain side groups
	&right_dt, 
	TRACKWIDTH, 
	lemlib::Omniwheel::OLD_325,
	WHEELRPM,
	HORIZONTALDRIFT
);

// we dont have any tracking wheels so they just get null pointers
// surely this wont mess up anything in the future!! 
lemlib::OdomSensors Sensors(
	nullptr, nullptr, //vertical tracking wheel 1 and 2
	nullptr, nullptr, //horizontal tracking wheel 1 and 2
	&imu
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(
	10, // proportional gain (kP)
    0, // integral gain (kI)
	3, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(
	2, // proportional gain (kP)
    0, // integral gain (kI)
    10, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(
	Drivetrain,
	lateral_controller,
	angular_controller,
	Sensors
);

subsystems::intake intake = subsystems::intake(INTAKEPORT1, INTAKEPORT2, OUTTAKEPISTONS, INDEXERPISTON, SCRAPERPISTON);

double bot_battery = 0;
std::int32_t control_battery = 0;


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	master.clear();
	intake.startCode();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	intake.startCode();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {

		// get vertical value for left joystick
		int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		// get horizontal value for right joystick
		int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		// drive the robot rahhhh
		// leftY = throttle, rightX = turning
		chassis.arcade(leftY, rightX);

		// runs driver functions defined in subsystems.cpp
		intake.driveFunctions();

		//PRINT SCREEN STUFF HERE!!!!
		//the "master.clear() pros::delay(15)" lines are so that we can be able to print to multiple lines on the controller screen
		//for some reason if you try to do different print things to multiple lines it will just print the first one
		//and for whatever reason clearing the screen and delaying it by at least 15ms will let you do this fine

		bot_battery = pros::battery::get_capacity();
		master.print(0, 0, "b: %1.0lf", bot_battery);
		master.clear();
		pros::delay(15);
		
		// int intake_1_temp = intake_1.get_temperature();
		// int intake_2_temp = intake_2.get_temperature();
		// int intake_temps = (intake_1_temp + intake_2_temp) / 2;

		// master.print(1, 0, "I: %d", intake_temps);
		// master.clear();
		// pros::delay(15);
		
		

		// master.print(1, 0, "Left=%lf, Right=%lf", left_temps, right_temps);

		pros::delay(20);                               // Run for 20 ms then update
	}
}