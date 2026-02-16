#pragma once
#include "main.h"

namespace subsystems
{
    class intake {
        public:
    
            // define all motors and solenoids used in the intake
            pros::MotorGroup Intake;

            pros::adi::Pneumatics Outtakes;
            pros::adi::Pneumatics Indexer;
            pros::adi::Pneumatics Scraper;
        
            //constructor for intake
            intake(
                int intake1Port, 
                int intake2Port, 
                char outtakesPort, 
                char indexerPort,
                char scraperPort
            );

            void driveFunctions();

    };
    
}