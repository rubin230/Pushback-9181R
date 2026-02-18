#pragma once

#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/imu.hpp"
#include "pros/distance.hpp"
#include "pros/rotation.hpp"

/*----------------------------------------------------------------------------*/
/*                            CORE COMPONENTS                                 */
/*----------------------------------------------------------------------------*/

extern pros::Controller controller;

/*----------------------------------------------------------------------------*/
/*                            DRIVETRAIN MOTORS                               */
/*----------------------------------------------------------------------------*/

extern pros::Motor Left1;
extern pros::Motor Left2;
extern pros::Motor Left3;
extern pros::Motor Right1;
extern pros::Motor Right2;
extern pros::Motor Right3;

extern pros::MotorGroup lefty;
extern pros::MotorGroup righty;

/*----------------------------------------------------------------------------*/
/*                           SUBSYSTEM MOTORS                                 */
/*----------------------------------------------------------------------------*/

extern pros::Motor outter;
extern pros::Motor inner;

/*----------------------------------------------------------------------------*/
/*                             PNEUMATICS                                     */
/*----------------------------------------------------------------------------*/

extern pros::ADIDigitalOut looog;
extern pros::ADIDigitalOut middle;
extern pros::ADIDigitalOut descore;

/*----------------------------------------------------------------------------*/
/*                              SENSORS                                       */
/*----------------------------------------------------------------------------*/

extern pros::Distance eyes;
extern pros::Imu imu;
extern pros::Rotation tracker;
