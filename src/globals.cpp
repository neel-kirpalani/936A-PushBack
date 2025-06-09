#include "globals.h"


pros::Motor leftFrontMotor(LEFT_MOTOR_1, pros::E_MOTOR_GEAR_BLUE);
pros::Motor leftMiddleMotor(-LEFT_MOTOR_3, pros::E_MOTOR_GEAR_BLUE);
pros::Motor leftBackMotor(LEFT_MOTOR_2, pros::E_MOTOR_GEAR_BLUE);
pros::Motor rightFrontMotor(-RIGHT_MOTOR_1, pros::E_MOTOR_GEAR_BLUE);
pros::Motor rightMiddleMotor(RIGHT_MOTOR_3, pros::E_MOTOR_GEAR_BLUE);
pros::Motor rightBackMotor(-RIGHT_MOTOR_2, pros::E_MOTOR_GEAR_BLUE);
pros::MotorGroup leftMotors({leftFrontMotor, leftMiddleMotor, leftBackMotor});
pros::MotorGroup rightMotors({rightFrontMotor,rightMiddleMotor, rightBackMotor});

// sensors
pros::Rotation horizontalEncoder(HORIZONTAL_ENCODER_PORT);
pros::Rotation verticalEncoder(VERTICAL_ENCODER_PORT);
pros::Imu imu(IMU_PORT);

pros::Controller master(pros::E_CONTROLLER_MASTER);

lemlib::Drivetrain drivetrain {
    &leftMotors,
    &rightMotors,
    12.5, // track width
    lemlib::Omniwheel::NEW_325, // wheel type
    520,  // rpm
    2   //drift
};

// create tracking wheels
lemlib::TrackingWheel vertical_tracking_wheel(&verticalEncoder, lemlib::Omniwheel::NEW_275, -2.5);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalEncoder, lemlib::Omniwheel::NEW_275, 4.5);

lemlib::OdomSensors sensors {
    &vertical_tracking_wheel, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2 (set to nullptr as we only have one)
    &horizontal_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2 (set to nullptr as we only have one)
    &imu // inertial sensor
};

lemlib::ControllerSettings controller(
    10,  //
    0,   
    20,   
    3,   
    1,   
    100, 
    3,    
    500, 
    20  
);
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
                                              
);
lemlib::Chassis chassis(
    drivetrain,
    controller,
    angular_controller,
    sensors
);

subsystems::Movement movement(&chassis);
subsystems::Auton auton(&chassis);
subsystems::Selector selector(&auton);
subsystems::Intake intake;
