#include "main.h"
#include "ARMS/api.h"
#include "ARMS/config.h"

#include <string>
#include <cmath>

#include "header/devices.h"
#include "header/pid.hh"
#include "header/ports.h"
#include "header/functions.hh"

void reset_inertial()
{
	for (int i = 0; i < 2; i++){
		IMU[i].reset();
	}
}

void drive()
{
  while(true) {
    int moveL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int moveR = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    left_motors.move(std::clamp(moveL, -127, 127));
    right_motors.move(std::clamp(moveR, -127, 127));
  }
}

void initialize()
{
	arms::init();
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Inititalizing v1");
	reset_inertial();
}

void disabled() 
{
	pros::lcd::clear();
	while (1){
		pros::lcd::set_text(0, "Disabled");
		pros::delay(10);
	}
}

void competition_initialize()
{
	reset_inertial();
}

void autonomous()
{
	pros::lcd::clear();
	reset_inertial();
	while (1){
		pros::lcd::set_text(0, "Auto");
		pros::delay(10);
	}
}

void opcontrol()
{
	pros::lcd::clear();
	ResetInertialSensors();

	pros::Task catapult_task(catapult_trigger);
	pros::Task drive_task(drive);
	pros::Task debug_task(debug_values);
	while (true)
	{
		if (catapult_active) {
			catapult_motor.move_absolute(1000.0, 600);
        }
		pros::delay(10);


void fire_catapult_toggle() {
    while (true) {
        pros::lcd::set_text(3, std::to_string(catapult_motor.get_position()));

        if (catapult_shooting) {
            target_distance += 1000;
            pros::lcd::set_text(2, "Rewinding Catapult");
            while (true) {
                double current_distance = catapult_motor.get_position();
                
                if (current_distance > (target_distance - 5)) {
                    break;
                }
                
                double error = target_distance - current_distance;
                double output = pid(error, &previous_error, &integral, 0.25, 0.002, 0.1);
                pros::lcd::set_text(0, std::to_string(output) + " " + std::to_string(current_distance));
                catapult_motor.move_velocity(output);
                pros::delay(10);

                if (!catapult_shooting) {
                    break;
                }
            }       
        }

        pros::delay(10);
    }
}

double wings_pneumatic() {
    while(true) {
        if (wings_active) {
            pros::lcd::set_text(2, "Pneumatics Active");
            while (wings_active) {
                wings.set_value(true);
            }       
        } else {
            wings.set_value(false);
        }
    }
    pros::delay(10);
}

double move_multiple(double x) {
	return -0.4 * cos((360.0/254.0)*x)+0.6;
}

void drive_robot() {
	while (true) {
		double multiple = 1.0;
		int left_y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right_x = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		
        int left_motor_velocity = left_y + (right_x * move_multiple(right_x)) * multiple;
		int right_motor_velocity = left_y - (right_x * move_multiple(right_x)) * multiple;

		left_motors.move(std::clamp(left_motor_velocity, -127, 127));
		right_motors.move(std::clamp(right_motor_velocity, -127, 127));
		
        pros::lcd::set_text(1, "Left: " + std::to_string(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)));
		pros::lcd::set_text(2, "Right: " + std::to_string(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)));
		
        pros::delay(10);
    }	
}

void opcontrol() {
	pros::lcd::set_text(1, "Enters the OPControl");
  pros::Task catapult_toggle_task(fire_catapult_toggle);
  pros::Task wings_pneumatic_task(wings_pneumatic);
  pros::Task drive_task(drive_robot);
  
  pros::lcd::clear();
	reset_inertial();

	pros::Task catapult_task(catapult_trigger);
	pros::Task drive_task(drive);
	pros::Task debug_task(debug_values);


	while (true) {
    if (catapult_active) {
			catapult_motor.move_absolute(1000.0, 600);
    }
		// Check R2 button to toggle firing
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            catapult_shooting = !catapult_shooting;
            while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
                pros::delay(10);
            }
        }

		// Check A button to toggle firing
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            wings_active = !wings_active;
            while (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
                pros::delay(10);
            }
        }
    }	
}