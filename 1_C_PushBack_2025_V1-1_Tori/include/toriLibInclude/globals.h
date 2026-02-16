#pragma once
//drivetrain vars:

    // right dt ports
    #define RIGHTPORT1 -1
    #define RIGHTPORT2 -2
    #define RIGHTPORT3 -3

    // left dt ports
    #define LEFTPORT1 18
    #define LEFTPORT2 19
    #define LEFTPORT3 20

    // idk other stuff
    #define TRACKWIDTH 10.25
    #define WHEELBASE 11
    #define WHEELRPM 450
    #define HORIZONTALDRIFT 8

//imu port
#define IMU 10

//peu matics
    //outtake
    #define OUTTAKEPISTONS 'B'

    //scraper
    #define SCRAPERPISTON 'A'

    //indexer
    #define INDEXERPISTON 'H'


//intake motors
#define INTAKEPORT1 -11
#define INTAKEPORT2 12

//controls
    //intaking
    #define LOADCUBES pros::E_CONTROLLER_DIGITAL_R1
    #define SCRAPERDOWN pros::E_CONTROLLER_DIGITAL_DOWN
    #define SCRAPERUP pros::E_CONTROLLER_DIGITAL_UP

    //goal scoring
    #define SCOREL1 pros::E_CONTROLLER_DIGITAL_R2
    #define SCOREL2 pros::E_CONTROLLER_DIGITAL_L2
    #define SCOREL3 pros::E_CONTROLLER_DIGITAL_L1

    //manual outtake toggling
    #define LOWERBOT pros::E_CONTROLLER_DIGITAL_B
    #define RAISEBOT pros::E_CONTROLLER_DIGITAL_A