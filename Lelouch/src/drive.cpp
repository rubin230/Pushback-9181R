#include "main.h"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include "robot-config.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


// --------------- Driver Control ---------------
void debug_screen() { 
    lemlib::Pose pose = chassis.getPose();
	pros::lcd::print(0, "X: %.2f", pose.x);
	pros::lcd::print(1, "Y: %.2f", pose.y);
	pros::lcd::print(2, "Theta: %.2f", pose.theta);
	printf("X: %.2f | Y: %.2f | Theta: %.2f\n", pose.x, pose.y, pose.theta);
	pros::delay(100);
}

void opcontrol() {
    chassis.setPose(0, 0, 0);

    chassis.setPose(0,0,0);

    while (true) {
        debug_screen();
        // Controller Input
        double forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        double turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // Joystick drift avoiding stuff
        if (fabs(forward) < 5) forward = 0;
        if (fabs(turn) < 5) turn = 0;

        forward /= 127.0;
        turn /= 127.0;

        forward = 0.7 * pow(forward, 3) + 0.3 * forward;
        turn = 0.7 * pow(turn, 3) + 0.3 * turn;

        // Reduce turning sensitivity slightly
        turn *= 0.55;

        // Convert back to motor range
        double leftOutput = (forward + turn) * 127.0;
        double rightOutput = (forward - turn) * 127.0;

        // Clamp just in case
        leftOutput = std::clamp(leftOutput, -127.0, 127.0);
        rightOutput = std::clamp(rightOutput, -127.0, 127.0);

        // Drive
        lefty.move(leftOutput);
        righty.move(rightOutput);

        // Subs
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
            inner.move(-127);
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
            inner.move(127);
        else
            inner.move(0);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
            outter.move(-127);
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
            outter.move(127);
        else
            outter.move(0);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
            chassis.turnToHeading(90, 1000);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
            chassis.turnToHeading(0, 1000);


        // Pistons
        static bool looog_state = false;
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            looog_state = !looog_state;
            looog.set_value(looog_state);
        }

        static bool middle_state = false;
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            middle_state = !middle_state;
            middle.set_value(middle_state);
        }

        static bool descore_state = false;
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            descore_state = !descore_state;
            descore.set_value(descore_state);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            drive_to_wall(425, 8000, 1, 5, 2000, false);
        }

        pros::delay(10);
    }
}

