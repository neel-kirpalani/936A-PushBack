#ifndef INTAKE_H
#define INTAKE_H

#include "pros/motors.hpp"
#include "pros/misc.hpp"
#include "pros/adi.hpp"

namespace subsystems {

class Intake {
public:
    Intake();
    void init();
    
    // flywheel controls
    void spinFlywheel(bool forward);  
    void stopFlywheel();
    void toggleFlywheel();
    
    // chain pusher controls
    void spinPusher(bool forward);   
    void stopPusher();
    void togglePusher();

    // piston controls
    void toggleLeftPiston();
    bool isLeftPistonExtended() const; 
    void toggleRightPiston();
    bool isRightPistonExtended() const;

private:
    bool flywheel_running;
    bool flywheel_forward;
    pros::Motor* flywheel_motor;

    bool pusher_running;
    bool pusher_forward;
    pros::Motor* pusher_motor;

    bool left_piston_extended;
    pros::ADIDigitalOut* left_piston;
    bool right_piston_extended;
    pros::ADIDigitalOut* right_piston;
};

}  // namespace subsystems

#endif // INTAKE_H 