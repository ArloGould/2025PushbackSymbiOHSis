using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Intake;
extern drivetrain Drivetrain;
extern motor Hopper;
extern motor Top;
extern digital_out Scraper;
extern digital_out Aligner;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );