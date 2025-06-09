#include "main.h"
#include "globals.h"

using namespace subsystems;

void initialize() {
    imu.reset();
    
    chassis.calibrate();
    chassis.setPose(0, 0, 0);
    selector.init();
    intake.init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    auton.run_auton(auton.get_selected_auton());
}

void opcontrol() {
    while (true) {
        movement.drive(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        
        if (master.get_digital_new_press(DIGITAL_L1)) {
            intake.toggleFlywheel(); // flywheel on/off (toggle)
        } else if (master.get_digital_new_press(DIGITAL_L2)) {
            intake.spinFlywheel(false); // run flywheel in reverse
        }
        
        
        if (master.get_digital(DIGITAL_R1)) {
            intake.spinPusher(true); // push blocks out while held
        } else if (master.get_digital(DIGITAL_R2)) {
            intake.spinPusher(false); // pull chain back while held
        } else {
            intake.stopPusher(); // stop when released
        }
        
        if (master.get_digital_new_press(DIGITAL_DOWN)) {
            intake.toggleLeftPiston();
        }
        if (master.get_digital_new_press(DIGITAL_RIGHT)) {
            intake.toggleRightPiston();
        }
        
        selector.update();
        pros::delay(10);
    }
}