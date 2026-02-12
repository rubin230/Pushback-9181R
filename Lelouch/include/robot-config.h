#pragma once
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/imu.hpp"

// Controller
extern pros::Controller controller;

// Drivetrain
extern pros::MotorGroup lefty;
extern pros::MotorGroup righty;

// Subsystem Motors
extern pros::Motor inner;
extern pros::Motor outter;

// Pneumatics
extern pros::adi::DigitalOut looog;
extern pros::adi::DigitalOut middle;
extern pros::adi::DigitalOut descore;

// Sensors
extern pros::Distance eyes;
extern pros::Imu imu;
