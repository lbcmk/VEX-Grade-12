#include "main.h"
#include "ports.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Motors
// Left Motors
pros::Motor left_motor_1(PORT4, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor left_motor_2(PORT5, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor left_motor_3(PORT6, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

// Right Motors
pros::Motor right_motor_1(PORT11, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor right_motor_2(PORT2, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor right_motor_3(PORT3, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

// Motor Groups
pros::Motor_Group left_motors({left_motor_1, left_motor_2, left_motor_3});
pros::Motor_Group right_motors({right_motor_1, right_motor_2, right_motor_3});

// Kicker Motor
pros::Motor kicker_motor_1(PORT9, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group kicker_motors({kicker_motor_1});

// Intake Motor
pros::Motor intake_motor_1(PORT8, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group intake_motors({intake_motor_1});

// Sensors
pros::IMU IMU[] = {PORT7};
// pros::Optical optical_sensor(PORT10);
pros::ADIUltrasonic ultrasonic(PORTC, PORTD); // plug output into port C and input into port D

// Pneumatics
pros::ADIDigitalOut hang(PORTH);
pros::ADIDigitalOut wings(PORTB);
