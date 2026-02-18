#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/imu.hpp"
#include "pros/distance.hpp"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.cpp                                          */
/*    Description:  Hardware definitions for all robot devices                */
/*                                                                            */
/*    PORT MAP:                                                               */
/*    ---------                                                               */
/*    PORT1  - RightMotor1          PORT11 - Intake                           */
/*    PORT2  - RightMotor2          PORT16 - TopRoller                        */
/*    PORT3  - RightMotor3          PORT17 - DistanceSide                     */
/*    PORT6  - LeftMotor2           PORT18 - DistanceFront                    */
/*    PORT7  - Inertial             PORT19 - DistanceBack                     */
/*    PORT9  - LeftMotor3           PORT20 - BackRoller                       */
/*    PORT10 - LeftMotor1                                                     */
/*                                                                            */
/*    3-WIRE PORTS:                                                           */
/*    A - Hood          B - Matchloader                                       */
/*    C - Wings         D - Descore                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                            CORE COMPONENTS                                 */
/*----------------------------------------------------------------------------*/

pros::Controller controller(pros::E_CONTROLLER_MASTER);

/*----------------------------------------------------------------------------*/
/*                            DRIVETRAIN MOTORS                               */
/*    Motor constructor: motor(port, gearRatio, reversed)                     */
/*    - ratio18_1 = 200 RPM (green cartridge)                                 */
/*    - ratio6_1  = 600 RPM (blue cartridge)                                  */
/*----------------------------------------------------------------------------*/

//Individual Drivetrain Motors
pros::Motor Left1(-4);
pros::Motor Left2(-12);
pros::Motor Left3(-13);
pros::Motor Right1(17);
pros::Motor Right2(18);
pros::Motor Right3(19);

// Drivetrain Left and Right
pros::MotorGroup lefty({-4, -12, -13});
pros::MotorGroup righty({17, 18, 19});

/*----------------------------------------------------------------------------*/
/*                           SUBSYSTEM MOTORS                                 */
/*----------------------------------------------------------------------------*/

// Intake and Outtake
pros::Motor outter(9);
pros::Motor inner(3);

/*----------------------------------------------------------------------------*/
/*                             PNEUMATICS                                     */
/*    Connected via 3-wire ports on the Brain                                 */
/*----------------------------------------------------------------------------*/

pros::ADIDigitalOut looog('B');
pros::ADIDigitalOut middle('G');
pros::ADIDigitalOut descore('c');

/*----------------------------------------------------------------------------*/
/*                              SENSORS                                       */
/*----------------------------------------------------------------------------*/

// Distance sensor
pros::Distance eyes(5);

// Inertial sensor
pros::Imu imu(2);

// Tracking wheel
pros::Rotation tracker(16);
