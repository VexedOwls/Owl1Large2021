#include "main.h"

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
	//Front arm
	pros::Motor frontArmMove(1);
	pros::Motor frontArmMove2(10);
	//Back arm
	pros::Motor backArmMove(2);
	pros::Motor backArmMove2(9);
	//Top bar
	pros::Motor topBar(6);
	//conveyor
	pros::Motor swirlyDo(5);
	//

	frontArmMove.set_brake_mode(MOTOR_BRAKE_HOLD);
	frontArmMove2.set_brake_mode(MOTOR_BRAKE_HOLD);
	backArmMove.set_brake_mode(MOTOR_BRAKE_HOLD);
	backArmMove2.set_brake_mode(MOTOR_BRAKE_HOLD);
	topBar.set_brake_mode(MOTOR_BRAKE_HOLD);

	bool state = 0;
	pros::ADIDigitalOut actuator(1, state);

	bool doConveyor = false;
	int delayCounter = 0;
	//TODO: Sofia's incrementor inside A button event idea, don't toggle if increment is more than 1, yknow how it is
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
			frontArmMove.move(127);
			frontArmMove2.move(-127);
		}
		else if (master.get_digital(DIGITAL_L2))
		{
			frontArmMove.move(-127);
			frontArmMove2.move(127);
		}
		else
		{
			frontArmMove.move(0);
			frontArmMove2.move(0);
		}

		if (master.get_digital(DIGITAL_R1))
		{
			backArmMove.move(127);
			backArmMove2.move(-127);
		}
		else if (master.get_digital(DIGITAL_R2))
		{
			backArmMove.move(-127);
			backArmMove2.move(127);
		}
		else
		{
			backArmMove.move(0);
			backArmMove2.move(0);
		}

		if (master.get_digital(DIGITAL_UP))
		{
			topBar.move(127);
		}
		else if (master.get_digital(DIGITAL_DOWN))
		{
			topBar.move(-127);
		}
		else
		{
			topBar.move(0);
		}

		//toggle conveyor
		if (master.get_digital(DIGITAL_A))
		{
			delayCounter++; //this is an int set to 0 outside of the main while(true) loop
		}
		else if (delayCounter >= 10) //if we have been holding down the A button for 10 or more loops, and we let go:
		{
			doConveyor = !doConveyor; //invert the doConveyor boolean
			delayCounter = 0;		  //reset the delayCounter
		}

		//
		if (doConveyor)
		{
			swirlyDo.move(-90);
			pros::lcd::set_text(1, "doConveyor is true");
		}
		else
		{
			swirlyDo.move(0);
			pros::lcd::set_text(1, "doConveyor is false");
		}

		if (master.get_digital(DIGITAL_B))
		{
			state = 1;
			actuator.set_value(state);
		}
		else
		{
			state = 0;
			actuator.set_value(state);
		}

		pros::delay(2);
	}
}