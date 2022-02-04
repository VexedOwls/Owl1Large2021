#include "main.h"
#include "autoSelect/selection.h"
#include "robotBase.h"
#include "intake.h"
#include "goalLift.h"

using namespace pros;


#define middleRed 1
#define middleBlue -1
#define fakerRed 2
#define fakerBlue -2
#define naRed 3
#define naBlue -3
#define skills 0


void autonomous()
{
	Imu imu(16);

	Motor *gL_right = new Motor(10);
	Motor *gL_left = new Motor(1);
	ADIPotentiometer *gL_pot = new ADIPotentiometer('C');
	ADILineSensor *gL_sensor = new ADILineSensor('D');
	GoalLift gL(gL_right, gL_left, gL_pot, gL_sensor);
	gL.setBrake(MOTOR_BRAKE_HOLD);


    //Back arm
    Motor backArmMove(4);
    Motor backArmMove2(8);

    //Top bar
    Motor topBar(6);

    //conveyor
    Motor swirlyDo(5);

    backArmMove.set_brake_mode(MOTOR_BRAKE_HOLD);
    backArmMove2.set_brake_mode(MOTOR_BRAKE_HOLD);
    topBar.set_brake_mode(MOTOR_BRAKE_HOLD);

    ADIDigitalOut needle('A', 0);
    ADIDigitalOut claw('B', 0);

	Motor backRight(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor midRight(19, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor frontRight(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor backLeft(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor midLeft(12, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor frontLeft(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

	RobotBase base(&backRight, &midRight, &frontRight, &backLeft, &midLeft, &frontLeft);

	// Double check that the imu is calibrated
	while (imu.get_status() & c::E_IMU_STATUS_CALIBRATING)
	{  delay(10);  }





	if (selector::auton == skills)
	{
		claw.set_value(0);

base.moveGyro(-45 _INCHES, &imu, false);

claw.set_value(1);

base.moveGyro(29 _INCHES, &imu, false);

base.turnGyro(80, &imu, true);

base.moveGyro(-8 _INCHES, &imu, true);

claw.set_value(0);

base.moveGyro(13 _INCHES, &imu, true);

base.turnGyro(-90, &imu, true);

base.moveGyro(13 _INCHES, &imu, false);

base.turnGyro(-65, &imu, false);

topBar.move_relative(1600, 127);

gL.moveToLoop(gL.bottomPos);

base.moveGyro(12 _INCHES, &imu, false);				// goal 2

gL.moveToLoop(gL.goalPos);

base.moveGyro(-12 _INCHES, &imu, false);

base.turnGyro(65, &imu, false);

swirlyDo.move(-90);

for (int i = 0; i < 15; i++)
{
	base.moveGyro(-14 _INCHES, &imu, false);

	base.moveGyro(14 _INCHES, &imu, false);
}

delay(5000);

swirlyDo.move(0);

base.moveGyro(-100 _INCHES, &imu, false);
	}





	if (selector::auton == middleRed || selector::auton == middleBlue)
	{
        claw.set_value(0);

		base.moveGyro(-45 _INCHES, &imu, false);

		claw.set_value(1);

		base.moveGyro(29 _INCHES, &imu, false);

		base.turnGyro(80, &imu, true);

		base.moveGyro(-8 _INCHES, &imu, true);

		claw.set_value(0);

		base.moveGyro(13 _INCHES, &imu, true);

		base.turnGyro(-90, &imu, true);

		base.moveGyro(13 _INCHES, &imu, false);

		base.turnGyro(-65, &imu, false);

		topBar.move_relative(1600, 127);

		gL.moveToLoop(gL.bottomPos);

		base.moveGyro(12 _INCHES, &imu, false);				// goal 2

		gL.moveToLoop(gL.goalPos);

		base.moveGyro(-12 _INCHES, &imu, false);

		base.turnGyro(65, &imu, false);

		swirlyDo.move(-100);								// start intake

		for (int i = 0; i < 12; i++)
		{
			base.moveGyro(-14 _INCHES, &imu, false);

			base.moveGyro(14 _INCHES, &imu, false);
		}

		delay(5000);

		swirlyDo.move(0);
	}
}
