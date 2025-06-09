#ifndef INTAKE_H
#define INTAKE_H

#include "pros/motors.hpp"
#include "pros/misc.hpp"

namespace subsystems {

class Intake {
public:
    Intake();
    void init();
    
    // Flywheel controls
    void spinFlywheel(bool forward);  // Control intake flywheels
    void stopFlywheel();
    void toggleFlywheel();
    
    // Chain pusher controls
    void spinPusher(bool forward);    // Control chain pusher
    void stopPusher();
    void togglePusher();
    
    void update();

private:
    // Flywheel state
    bool flywheel_running;
    bool flywheel_forward;
    pros::Motor* flywheel_motor;

    // Chain pusher state
    bool pusher_running;
    bool pusher_forward;
    pros::Motor* pusher_motor;
};

}  // namespace subsystems

#endif // INTAKE_H 