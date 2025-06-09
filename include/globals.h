#ifndef GLOBALS_H
#define GLOBALS_H

#include "pros/rtos.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/rotation.hpp"
#include "pros/imu.hpp"
#include "robot/movement.h"
#include "robot/selector.h"
#include "robot/intake.h"
#include "lemlib/api.hpp"



//ports
#define LEFT_MOTOR_1 11
#define LEFT_MOTOR_2 12
#define LEFT_MOTOR_3 13
#define RIGHT_MOTOR_1 1
#define RIGHT_MOTOR_2 2
#define RIGHT_MOTOR_3 3
#define INTAKE_FLYWHEEL_MOTOR 14
#define INTAKE_PUSHER_MOTOR 15 // this motor controls the chain that outtakes the ball


// sensor ports
#define HORIZONTAL_ENCODER_PORT 4
#define VERTICAL_ENCODER_PORT 5
#define IMU_PORT 6


//controller
#define DIGITAL_L1 pros::E_CONTROLLER_DIGITAL_L1
#define DIGITAL_L2 pros::E_CONTROLLER_DIGITAL_L2
#define DIGITAL_R1 pros::E_CONTROLLER_DIGITAL_R1
#define DIGITAL_R2 pros::E_CONTROLLER_DIGITAL_R2
#define DIGITAL_A pros::E_CONTROLLER_DIGITAL_A
#define DIGITAL_B pros::E_CONTROLLER_DIGITAL_B
#define DIGITAL_X pros::E_CONTROLLER_DIGITAL_X
#define DIGITAL_Y pros::E_CONTROLLER_DIGITAL_Y
#define DIGITAL_DOWN pros::E_CONTROLLER_DIGITAL_DOWN
#define DIGITAL_UP pros::E_CONTROLLER_DIGITAL_UP
#define ANALOG_LEFT_Y pros::E_CONTROLLER_ANALOG_LEFT_Y
#define ANALOG_RIGHT_X pros::E_CONTROLLER_ANALOG_RIGHT_X

// toggle variables
extern bool pistonToggle;
extern bool intakeToggle;
extern bool climbingToggle;
extern bool wallToggle;

namespace subsystems {
    class Movement;
    class Selector;
    class Auton;
    class Intake;
}


// motors
extern pros::Motor leftFrontMotor;
extern pros::Motor leftBackMotor;
extern pros::Motor leftMiddleMotor;
extern pros::Motor rightFrontMotor;
extern pros::Motor rightBackMotor;
extern pros::Motor rightMiddleMotor;
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// sensors
extern pros::Rotation horizontalEncoder;
extern pros::Rotation verticalEncoder;
extern pros::Imu imu;

// tracking wheels
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::TrackingWheel horizontal_tracking_wheel;



extern pros::Controller master;
extern pros::ADIDigitalOut piston;

// subsystem
extern subsystems::Movement movement;
extern subsystems::Selector selector;
extern subsystems::Auton auton;
extern subsystems::Intake intake;
// chassis
extern lemlib::Drivetrain drivetrain;

extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings controller;
extern lemlib::Chassis chassis;

#endif // GLOBALS_H