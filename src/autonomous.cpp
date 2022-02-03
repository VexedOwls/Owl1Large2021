#include "main.h"
#include "goalLift.h"
#include "intake.h"
#include "robotBase.h"
using namespace pros;
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
void autonomous()
{
    pros::Motor backLeft(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
    pros::Motor midLeft(12, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
    pros::Motor frontLeft(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

    pros::Motor backRight(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
    pros::Motor midRight(19, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
    pros::Motor frontRight(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

    Vision vision_sensor(16);
    vision_sensor.set_exposure(20);

    RobotBase rBase(&backRight, &midRight, &frontRight, &backLeft, &midLeft, &frontLeft);
    rBase.moveTo_Vision(-1670, &vision_sensor);

    delay(2);
}