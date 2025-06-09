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
        
        // Intake flywheel control using L1 and L2
        if (master.get_digital_new_press(DIGITAL_L1)) {
            intake.toggleFlywheel(); // Toggle flywheel on/off
        } else if (master.get_digital_new_press(DIGITAL_L2)) {
            intake.spinFlywheel(false); // Run flywheel in reverse
        }
        
        // Chain pusher control using R1 and R2
        if (master.get_digital(DIGITAL_R1)) {
            intake.spinPusher(true); // Push blocks out while held
        } else if (master.get_digital(DIGITAL_R2)) {
            intake.spinPusher(false); // Pull chain back while held
        } else {
            intake.stopPusher(); // Stop when released
        }
        
        if (master.get_digital_new_press(DIGITAL_DOWN)) {
            auton.test_lateral();
        }
        if (master.get_digital_new_press(DIGITAL_RIGHT)) {
            auton.test_angular();
        }
        
        selector.update();
        intake.update();
        pros::delay(10);
    }
}