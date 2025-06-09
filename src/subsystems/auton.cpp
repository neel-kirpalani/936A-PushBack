#include "robot/auton.h"
#include "globals.h"


namespace subsystems {

Auton::Auton(lemlib::Chassis* chassis) : chassis(chassis), selected_auton(AUTON_ROUTINE::NONE) {}

void Auton::run_red_left() {

}

void Auton::run_red_right() {

}

void Auton::run_blue_left() {
}

void Auton::run_blue_right() {
   
}

void Auton::run_skills() {

    chassis->setPose(0, 0, 0);  
}

void Auton::run_auton(AUTON_ROUTINE routine) {
    switch (routine) {
        case AUTON_ROUTINE::RED_LEFT:
            run_red_left();
            break;
        case AUTON_ROUTINE::RED_RIGHT:
            run_red_right();
            break;
        case AUTON_ROUTINE::BLUE_LEFT:
            run_blue_left();
            break;
        case AUTON_ROUTINE::BLUE_RIGHT:
            run_blue_right();
            break;
        case AUTON_ROUTINE::SKILLS:
            run_skills();
            break;
        case AUTON_ROUTINE::NONE:
            break;
    }
}

void Auton::set_selected_auton(AUTON_ROUTINE routine) {
    selected_auton = routine;
}

AUTON_ROUTINE Auton::get_selected_auton() {
    return selected_auton;
}

void Auton::test_lateral() {
    // Reset the robot's position
    chassis->setPose(0, 0, 0);
    // Move forward 48 inches (2 field tiles)
    chassis->moveToPoint(0, 48, 10000);
}

void Auton::test_angular() {
    // Reset the robot's position
    chassis->setPose(0, 0, 0);
    // Turn to face 90 degrees
    chassis->turnToHeading(90, 10000);
}

} // namespace subsystems