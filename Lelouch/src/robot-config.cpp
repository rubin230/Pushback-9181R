#include "main.h"
#include "robot-config.h"

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

// Drivetrain Left and Right
pros::MotorGroup lefty({-4, -12, -13}, pros::MotorGearset::blue);
pros::MotorGroup righty({17, 18, 19}, pros::MotorGearset::blue);

/*----------------------------------------------------------------------------*/
/*                           SUBSYSTEM MOTORS                                 */
/*----------------------------------------------------------------------------*/

// Intake and Outtake
pros::Motor outter(9, pros::MotorGearset::blue);
pros::Motor inner(3, pros::MotorGearset::blue);

/*----------------------------------------------------------------------------*/
/*                             PNEUMATICS                                     */
/*    Connected via 3-wire ports on the Brain                                 */
/*----------------------------------------------------------------------------*/

pros::adi::DigitalOut looog('B');
pros::adi::DigitalOut middle('G');
pros::adi::DigitalOut descore('C');

/*----------------------------------------------------------------------------*/
/*                              SENSORS                                       */
/*----------------------------------------------------------------------------*/

// Distance sensor
pros::Distance eyes(7);

// Inertial sensor
pros::Imu imu(2);