#include "robot/intake.h"
#include "globals.h"

namespace subsystems {

Intake::Intake() 
    : flywheel_running(false), flywheel_forward(true),
      pusher_running(false), pusher_forward(true), left_piston_extended(false), right_piston_extended(false) {
    // initialize motors
    flywheel_motor = new pros::Motor(INTAKE_FLYWHEEL_MOTOR, pros::E_MOTOR_GEAR_BLUE);
    pusher_motor = new pros::Motor(INTAKE_PUSHER_MOTOR, pros::E_MOTOR_GEAR_GREEN);
    left_piston = new pros::ADIDigitalOut(INTAKE_LEFT_PISTON_PORT);
    right_piston = new pros::ADIDigitalOut(INTAKE_RIGHT_PISTON_PORT);
}

void Intake::init() {
    stopFlywheel();
    stopPusher();
    left_piston->set_value(false);
    left_piston_extended = false;
    right_piston->set_value(false);
    right_piston_extended = false;
}

// flywheel controls (stage 1)
void Intake::spinFlywheel(bool forward) {
    flywheel_running = true;
    flywheel_forward = forward;
    if (forward) {
        flywheel_motor->move_velocity(600); // forward
    } else {
        flywheel_motor->move_velocity(-600); // reverse
    }
}

void Intake::stopFlywheel() {
    flywheel_running = false;
    flywheel_motor->move_velocity(0);
}

void Intake::toggleFlywheel() {
    if (flywheel_running) {
        stopFlywheel();
    } else {
        spinFlywheel(flywheel_forward);
    }
}

// pusher controls (stage 2)
void Intake::spinPusher(bool forward) {
    pusher_running = true;
    pusher_forward = forward;
    if (forward) {
        pusher_motor->move_velocity(200); // forwards
    } else {
        pusher_motor->move_velocity(-200); // reverse
    }
}

void Intake::stopPusher() {
    pusher_running = false;
    pusher_motor->move_velocity(0);
}

void Intake::togglePusher() {
    if (pusher_running) {
        stopPusher();
    } else {
        spinPusher(pusher_forward);
    }
}

// piston controls
void Intake::toggleLeftPiston() {
    left_piston_extended = !left_piston_extended;
    left_piston->set_value(left_piston_extended);
}

bool Intake::isLeftPistonExtended() const {
    return left_piston_extended;
}

void Intake::toggleRightPiston() {
    right_piston_extended = !right_piston_extended;
    right_piston->set_value(right_piston_extended);
}

bool Intake::isRightPistonExtended() const {
    return right_piston_extended;
}

} // namespace subsystems
