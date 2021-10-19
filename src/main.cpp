#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "largeboy activated");
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
void autonomous() {}

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
void opcontrol()
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	//TODO: remove placeholder port nums
	//TODO: invert the ones that need inverting
	//drive motors
	pros::Motor backLeft(13);
	pros::Motor midLeft(12, true);
	pros::Motor frontLeft(11);

	pros::Motor backRight(18, true);
	pros::Motor midRight(19);
	pros::Motor frontRight(20, true);
	//back arm
	pros::Motor frontArmMove(1);
	pros::Motor frontArmMove2(2);

	frontArmMove.set_brake_mode(MOTOR_BRAKE_HOLD);
	frontArmMove2.set_brake_mode(MOTOR_BRAKE_HOLD);

	bool doConveyor = false;

	while (true)
	{
		int leftInput = master.get_analog(ANALOG_LEFT_Y);
		int rightInput = master.get_analog(ANALOG_RIGHT_Y);
		//drive controls
		backLeft.move(leftInput);
		midLeft.move(leftInput);
		frontLeft.move(leftInput);

		backRight.move(rightInput);
		midRight.move(rightInput);
		frontRight.move(rightInput);
		//arm controls
		if (master.get_digital(DIGITAL_L1))
		{
			frontArmMove.move(-127);
			frontArmMove2.move(127);
		}
		else if (master.get_digital(DIGITAL_L2))
		{
			frontArmMove.move(127);
			frontArmMove2.move(-127);
		}
		else
		{
			frontArmMove.move(0);
			frontArmMove2.move(0);
		}
		pros::delay(2);
	}
}