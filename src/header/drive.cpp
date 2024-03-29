#include "devices.hh"
#include "controls.h"

double move_multiple(double x) {
	return -0.3 * cos((3.14159265/127)*x)+0.5;
}

void drive_robot() {
	while (true) {
		int left_y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right_x = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * -1;
		
        int left_motor_velocity = (left_y - (right_x * move_multiple(right_x))) * 1;
		int right_motor_velocity = (left_y + (right_x * move_multiple(right_x))) * 1;

		left_motors.move(std::clamp(left_motor_velocity, -127, 127));
		right_motors.move(std::clamp(right_motor_velocity, -127, 127));
		
        // pros::delay(10);
    }	
}