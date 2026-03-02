#include "main.h"
#include "../include/toriLibInclude/subsystems.hpp"
#include "../include/toriLibInclude/globals.h"
#include "../include/toriLibInclude/devices.hpp"
namespace subsystems
{
    //intake class
        //constructor
        //this references the intake:: class name so it doesnt need to be placed in a class
        //the constructor just takes the ports for each part of the intake and uses it to define what they are for
        intake::intake(
            int intake1Port, 
            int intake2Port, 
            char outtakesPort,
            char indexerPort,
            char scraperPort
        ): 
        //it goes [name](pros::motor(other stuff)) instead of pros::motor [name](other stuff) because we already 
        //defined the names in the header file just without the port and gearset, which we are now adding

        Intake(pros::MotorGroup({intake1Port, intake2Port}, pros::MotorGearset::blue)),

        Outtakes(pros::adi::Pneumatics(outtakesPort, true, true)),
        Indexer(pros::adi::Pneumatics(indexerPort, false)),
        Scraper(pros::adi::Pneumatics(scraperPort, false))
        {}

        void intake::driveFunctions()
        {
            //all the code for this is kinda spagettish
            //maybe change this later to be like how alister did it
            // cause thats cleaner and easier to read

            //load cubes
            if(master.get_digital(LOADCUBES))
            {
                Intake.move_velocity(550);
                Indexer.retract();
            }

            //score bottom goal
            else if(master.get_digital(SCOREL1))
            {
                Intake.move_velocity(-600);
            }

            //score middle goal
            else if(master.get_digital(SCOREL2))
            {
                Outtakes.retract();
                Indexer.extend();
                Intake.move_velocity(600);
            }

            //score long goal
            else if(master.get_digital(SCOREL3))
            {
                Indexer.extend();
                Intake.move_velocity(600);
            }

            //if you aint pressing a macro that spins the intake motors,
            // brake them
            else
            {
                Intake.brake();
            }

            //lower scraper
            if(master.get_digital(SCRAPERDOWN))
            {
                Outtakes.extend();
                Scraper.extend();
            }

            //lift scraper
            if(master.get_digital(SCRAPERUP))
            {
                Scraper.retract();
            }

            //lift outtake
            if(master.get_digital(RAISEBOT))
            {
                Outtakes.extend();
            }

            //lower outtake
            if(master.get_digital(LOWERBOT))
            {
                Outtakes.retract();
            }
        };

        void intake::loadCubes()
        {
            Intake.move_velocity(550);
            Indexer.retract();
        };

        void intake::scoreL1()
        {
            Intake.move_velocity(-600);
        };

        void intake::scoreL2()
        {
            Outtakes.retract();
            Indexer.extend();
            Intake.move_velocity(600);
        };

        void intake::scoreL3()
        {
            Indexer.extend();
            Intake.move_velocity(600);
        };

        void intake::stopIntake()
        {
            Intake.brake();
        };

        void intake::scraperDown()
        {
            Outtakes.extend();
            Scraper.extend();
        };

        void intake::scraperUp()
        {
            Scraper.retract();
        };

        void intake::raiseOuttake()
        {
            Outtakes.extend();
        };

        void intake::lowerOuttake()
        {
            Outtakes.retract();
        };

}