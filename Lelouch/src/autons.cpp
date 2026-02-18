#include "main.cpp"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/distance.hpp"
#include "pros/rtos.hpp"
#include "robot-config.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {  
	chassis.setPose(0,0,0);

	// to matchloader 1
	chassis.turnToPoint(0, 28, 1000);
	chassis.moveToPoint(0, 28, 1000, {.maxSpeed = 70});
	pros::delay(200);

	// in matchloader 1
	chassis.turnToHeading(90, 1000);
	looog.set_value(true);
	inner.move(-127);
	pros::delay(200);
	chassis.moveToPoint(10, 34, 1000, {.maxSpeed = 80}); 
	chassis.moveToPoint(13, 34, 1000, {.maxSpeed = 10});
	pros::delay(2000);
	chassis.moveToPoint(9, 34, 1000, {.forwards = false});
	chassis.moveToPoint(10, 34, 1000, {.maxSpeed = 80}); 
	chassis.moveToPoint(13, 34, 1000, {.maxSpeed = 10});
	pros::delay(1000);

	// exit first matchloader
	chassis.moveToPoint(0, 34, 1000, {.forwards = false});

	//go across map to second stuff
	chassis.turnToHeading(135, 1000);
	chassis.moveToPoint(-13, 45, 1000, {.forwards = false});
	chassis.turnToHeading(90, 1000);
	chassis.moveToPoint(-85, 45, 5000, {.forwards = false, .maxSpeed = 70});

	// scoring long goal
	chassis.turnToHeading(180, 1000);
	chassis.moveToPoint(-85, 32, 1000);
	chassis.turnToHeading(270, 1000);
	chassis.moveToPoint(-70, 28, 1000, {.forwards = false, .maxSpeed = 80}, false);
	inner.move(-127);
	outter.move(127);
	chassis.moveToPoint(-67, 28, 1000, {.forwards = false, .maxSpeed = 5});
	pros::delay(2200);

	// get second matchloader
	chassis.turnToPoint(-100, 28, 1000);
	chassis.moveToPoint(-103, 28, 1000, {.maxSpeed = 10});
	chassis.moveToPoint(-75, 28, 1000);
	chassis.turnToPoint(-100, 29, 1000);
	outter.move(0);
	chassis.moveToPoint(-100, 27, 1000, {.maxSpeed = 55});
	chassis.moveToPoint(-103, 27, 1000, {.maxSpeed = 10});
	pros::delay(2200);

	// score long goal again
	chassis.moveToPoint(-75, 28, 1000, {.forwards = false, .maxSpeed = 80}, false);
	outter.move(127);
	chassis.moveToPoint(-67, 28, 1000, {.forwards = false, .maxSpeed = 5});
	pros::delay(2200);

    // gun park
    looog.set_value(false);
	chassis.moveToPoint(-85, 29, 1000);
	chassis.turnToHeading(0, 1000);
	chassis.moveToPoint(-80, 15, 1000, {.forwards = false});
	chassis.moveToPoint(20, 7, 2500, {.forwards = false, .maxSpeed = 50});
    chassis.turnToPoint(20, -15, 1000);
    chassis.moveToPoint(20, -15, 1000);
}