#include "main.h"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/distance.hpp"
#include "pros/rtos.hpp"
#include "robot-config.h"

// Drivetrain struct
lemlib::Drivetrain drivetrain(&lefty, &righty, 8, lemlib::Omniwheel::NEW_325, 450, 2);

lemlib::TrackingWheel tracking(&tracker, lemlib::Omniwheel::NEW_275, 0);
// Controller construct

lemlib::OdomSensors sensors(&tracking, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);
 
// lateral PID controller
lemlib::ControllerSettings lateral_controller(1, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              1000, // large error range timeout, in milliseconds
                                              5 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              2.5, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

/*----------------------------------------------------------------------------*/
/*                              Chassis                                       */
/*----------------------------------------------------------------------------*/
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
/*----------------------------------------------------------------------------*/
/*                           INITIALIZATION                                   */
/*----------------------------------------------------------------------------*/
#include <cmath>

void drive_to_wall(float target_distance,
                   float drive_max_voltage,
                   float heading_kp,
                   float settle_error,
                   float timeout,
                   bool relative_to_robot) {

    float drive_kp = relative_to_robot ? 4.0 : 0.05;
    float drive_kd = relative_to_robot ? 17.0 : 0.5;

    lemlib::Pose startPose = chassis.getPose();
    float start_heading = startPose.theta;

    float drive_error = target_distance;
    float drive_prev_error = target_distance;
    float heading_prev_error = 0;

    int time_spent = 0;
    int settle_time = 0;
    const int settle_threshold = 200;

    while (time_spent < timeout) {

        if (relative_to_robot) {
            lemlib::Pose currentPose = chassis.getPose();

            float dx = currentPose.x - startPose.x;
            float dy = currentPose.y - startPose.y;

            float distance_traveled = std::sqrt(dx * dx + dy * dy);

            drive_error = target_distance - distance_traveled;
        }
        else {
            float current_distance = eyes.get(); // mm
            drive_error = current_distance - target_distance;
        }

        float drive_derivative = drive_error - drive_prev_error;
        drive_prev_error = drive_error;

        float drive_output =
            (drive_kp * drive_error) +
            (drive_kd * drive_derivative);

        // clamp to millivolts
        if (drive_output > drive_max_voltage)
            drive_output = drive_max_voltage;
        if (drive_output < -drive_max_voltage)
            drive_output = -drive_max_voltage;

        // Heading correction
        lemlib::Pose currentPose = chassis.getPose();
        float heading_error = start_heading - currentPose.theta;

        if (heading_error > 180) heading_error -= 360;
        if (heading_error < -180) heading_error += 360;

        float heading_derivative = heading_error - heading_prev_error;
        heading_prev_error = heading_error;

        float heading_correction =
            (heading_kp * heading_error) +
            (0.1 * heading_derivative);

        float left_voltage = drive_output + heading_correction;
        float right_voltage = drive_output - heading_correction;

        chassis.tank(left_voltage,
                     right_voltage);

        if (fabs(drive_error) < settle_error) {
            settle_time += 10;
            if (settle_time >= settle_threshold)
                break;
        } else {
            settle_time = 0;
        }

        pros::delay(10);
        time_spent += 10;
    }

    chassis.tank(0, 0);
}


void vexcodeInit(void) {
  // Reserved for future initialization
}


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        pros::lcd::set_text(2, "I was pressed!");
    } else {
        pros::lcd::clear_line(2);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();

    pros::lcd::register_btn1_cb(on_center_button);
    
    imu.reset();
    pros::delay(2000);        // wait for calibration
    chassis.calibrate();
    chassis.setPose(0, 0, 0); // starting position
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}




