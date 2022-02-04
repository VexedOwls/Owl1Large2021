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
		
	}





	if (selector::auton == middleRed || selector::auton == middleBlue)
	{
        claw.set_value(1);

		base.moveGyro(-43 _INCHES, &imu, true);

		claw.set_value(0);

		base.moveGyro(28 _INCHES, &imu, true);

		actuator.set_value(1);
		delay(200);

		
	}
}
