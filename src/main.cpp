#include "main.h"

#include <string>
#include <cmath>

#include "header/catapult.hh"
#include "header/controls.h"
#include "header/devices.hh"
#include "header/drive.hh"
#include "header/functions.hh"
#include "header/ports.h"
#include "header/wings.hh"
#include "header/auto.hh"
#include "header/intake.hh"

// void initialize()
// {
// 	pros::lcd::initialize();
// 	pros::lcd::set_text(0, "Inititalizing v1");
// 	reset_inertial();
// }

void disabled() 
{
	pros::lcd::clear();
	while (1){
		pros::lcd::set_text(0, "Disabled");
		pros::delay(10);
	}
}

void competition_initialize() {
	reset_inertial();
}
void autonomous__() { // Auton far side


	// move_forward_inertial(500, -80.0, 80.0, 60.0);

	// pros::delay(5000);

	// move_forward_inertial(200.0, -80.0, 80.0, 50.0);

	// wings.set_value(1);
	left_motors.move(-110);
	right_motors.move(-80);
	// wings.set_value(0);
	pros::delay(1400);
	left_motors.move(0);
	right_motors.move(0);

	pros::delay(100);
	left_motors.move(110);
	right_motors.move(80);
	wings.set_value(1);
	pros::delay(400);
	wings.set_value(0);
	pros::delay(1000);
	left_motors.move(0);
	right_motors.move(0);
	
	intake.set_value(1);
	intake.set_value(0);

	move_backward(80.0, -50.0, 50.0);
	turn_right_to_look_at(5);
	move_forward_inertial(100.0, -100.0, 100.0, 80.0);
	move_backward(150.0, -100.0, 100.0);
	move_forward_inertial(300.0, -100.0, 100.0, 80.0);
	turn_right_to_look_at(45);

}

void autonomous() { // Auton near side
	// wings.set_value(1);
	left_motors.move(-80);
	right_motors.move(-110);
	// wings.set_value(0);
	pros::delay(800);
	left_motors.move(0);
	right_motors.move(0);

	pros::delay(100);
	wings.set_value(1);
	left_motors.move(70);
	right_motors.move(120);
	pros::delay(400);
	wings.set_value(0);
	pros::delay(700);
	left_motors.move(0);
	right_motors.move(0);
	
	intake.set_value(1);
	intake.set_value(0);

	move_forward(15, -20, 20);

	// move_backward(80.0, -50.0, 50.0);
	// turn_left_to_look_at(-5);
	// move_forward_inertial(100.0, -100.0, 100.0, 80.0);
	// move_backward(150.0, -100.0, 100.0);
	// move_forward_inertial(300.0, -100.0, 100.0, 80.0);
	// turn_left_to_look_at(45);
}

void opcontrol() {
    pros::Task drive_task(drive_robot);
	pros::Task catapult_task(catapult_trigger);
	pros::Task wings_task(wings_trigger);
	pros::Task intake_task(intake_trigger);
	while (true) {
		handle_catapult();
		handle_wings();
		handle_intake();
        pros::delay(10);
	}        
}
