#include "main.h"
#include "lemlib/api.hpp"
#include "2900/globals.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

//left and right sides of the drivetrain
pros::MotorGroup right_dt({RIGHTPORT1, RIGHTPORT2, RIGHTPORT3}, pros::MotorGearset::blue);
pros::MotorGroup left_dt({LEFTPORT1, LEFTPORT2, LEFTPORT3}, pros::MotorGearset::blue);

pros::Imu imu(IMU);

lemlib::Drivetrain Drivetrain
(
	&left_dt, 
	&right_dt, 
	10.25,
	lemlib::Omniwheel::OLD_325,
	450,
	4
);


// intake motors, this is a motor group since they will always be spinning together
pros::Motor intake_1(-11, pros::MotorGearset::blue);
pros::Motor intake_2(12, pros::MotorGearset::blue);
// pros::MotorGroup Intake({-11, 12}, pros::MotorGearset::blue);

//penumatics
// pros::adi::Pneumatics outtake_1('A', false);
pros::adi::Pneumatics outtake_2('B', false);
pros::adi::Pneumatics indexer('H', true);
pros::adi::Pneumatics scraper('A', false, true);

double bot_battery = 0;
std::int32_t control_battery = 0;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

	master.clear();
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
void competition_initialize() {}

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

		// Arcade control scheme
		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		left_dt.move(dir - turn);                      // Sets left motor voltage
		right_dt.move(dir + turn);                     // Sets right motor voltage

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) 
		{
			intake_1.move(100);
			intake_2.move(100);
		}

		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			intake_1.move(-100);
			intake_2.move(-100);
		}

		else
		{
			intake_1.brake();
			intake_2.brake();
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			// outtake_1.extend();
			outtake_2.extend();
		}

		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			// outtake_1.retract();
			outtake_2.retract();
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			indexer.retract();
		}

		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			indexer.extend();
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			scraper.extend();
		}

		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			scraper.retract();
		}

		//PRINT SCREEN STUFF HERE!!!!
		//the "master.clear() pros::delay(15)" lines are so that we can be able to print to multiple lines on the controller screen
		//for some reason if you try to do different print things to multiple lines it will just print the first one
		//and for whatever reason clearing the screen and delaying it by at least 15ms will let you do this fine

		bot_battery = pros::battery::get_capacity();
		master.print(0, 0, "b: %1.0lf", bot_battery);
		master.clear();
		pros::delay(15);
		
		int intake_1_temp = intake_1.get_temperature();
		int intake_2_temp = intake_2.get_temperature();
		int intake_temps = (intake_1_temp + intake_2_temp) / 2;

		master.print(1, 0, "I: %d", intake_temps);
		master.clear();
		pros::delay(15);
		
		

		// master.print(1, 0, "Left=%lf, Right=%lf", left_temps, right_temps);

		pros::delay(20);                               // Run for 20 ms then update
	}
}