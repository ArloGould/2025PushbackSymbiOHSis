#include "toriLibInclude/subsystems.hpp"
#include "toriLibInclude/globals.h"

namespace subsystems
{
    //intake class
        //constructor
        //this references the intake:: class name so it doesnt need to be placed in a class
        //the constructor just takes the ports for each part of the intake and uses it to define what they are for
        intake::intake(
            int intake1Port, 
            int intake2Port, 
            char outtake1Port, 
            char outtake2Port, 
            char indexerPort
        ): 
        //it goes [name](pros::motor(other stuff)) instead of pros::motor [name](other stuff) because we already 
        //defined the names in the header file just without the port and gearset, which we are now adding
        Intake1(pros::Motor(intake1Port, pros::MotorGearset::blue)),
        Intake2(pros::Motor(intake2Port, pros::MotorGearset::blue)),

        Outtake1(pros::adi::Pneumatics(outtake1Port, false, false)),
        Outtake2(pros::adi::Pneumatics(outtake2Port, false, false)),

        Indexer(pros::adi::Pneumatics(indexerPort, true, false))
        {}

        void intake::driveFunctions()
        {
            if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) 
            {
                Intake1.move(100);
                Intake2.move(100);
            }

            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
            {
                Intake1.move(-100);
                Intake2.move(-100);
            }

            else
            {
                Intake1.brake();
                Intake2.brake();
            }

            if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
            {
                Outtake1.extend();
                Outtake2.extend();
            }

            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
            {
                Outtake1.retract();
                Outtake2.retract();
            }
        }
}