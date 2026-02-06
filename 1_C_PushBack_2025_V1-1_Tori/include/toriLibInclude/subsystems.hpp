#include "main.h"
#include "toriLibInclude/globals.h"

namespace subsystems
{
    class intake {
        public:
    
            // define all motors and solenoids used in the intake
            pros::Motor Intake1;
            pros::Motor Intake2;

            pros::adi::Pneumatics Outtake1;
            pros::adi::Pneumatics Outtake2;
            pros::adi::Pneumatics Indexer;
        
            //constructor for intake
            intake(
                int intake1Port, 
                int intake2Port, 
                char outtake1Port, 
                char outtake2Port, 
                char indexerPort
            );

            void driveFunctions();

    };
    
}