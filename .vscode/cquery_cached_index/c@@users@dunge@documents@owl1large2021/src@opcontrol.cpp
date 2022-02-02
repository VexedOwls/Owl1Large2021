#include "main.h"
#include "goalLift.h"
#include "intake.h"
#include "robotBase.h"
using namespace pros;







#define intakeSpeed_topBarUp 127
#define intakeSpeed_topBarDown 90














void opcontrol_test()
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

void opcontrol()
 {
   Motor* gL_right = new Motor(10);
   Motor* gL_left = new Motor(1);
   ADIPotentiometer* gL_pot = new ADIPotentiometer('C');
   ADILineSensor* gL_sensor = new ADILineSensor('D');
   GoalLift gL(gL_right, gL_left, gL_pot, gL_sensor);
   gL.setBrake(MOTOR_BRAKE_HOLD);

   Motor* rI_roller = new Motor(5);
   RingIntake rI(rI_roller);



   Vision vision_sensor(17);
   vision_signature_s_t YELLOW_SIG = Vision::signature_from_utility(1, -361, 1351, 495, -3999, -2953, -3476, 2.600, 0);
   vision_sensor.set_signature(1, &YELLOW_SIG);





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

   //Back arm
   pros::Motor backArmMove(4);
   pros::Motor backArmMove2(8);

   //Top bar
   pros::Motor topBar(6);

   //conveyor
   pros::Motor swirlyDo(5);
   //

   backArmMove.set_brake_mode(MOTOR_BRAKE_HOLD);
   backArmMove2.set_brake_mode(MOTOR_BRAKE_HOLD);
   topBar.set_brake_mode(MOTOR_BRAKE_HOLD);

   bool state = 0;
   pros::ADIDigitalOut actuator(1, state);


   bool backClaw_state = 0;
   pros::ADIDigitalOut backClaw_actuator('E', state);

   bool doConveyor = false;
   bool doNeedle = false;
   bool doBackClaw = false;
   int delayCounter = 0;
   bool latchA = false;
   bool latchB = false;
   bool latchC = false;




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




       /*
        *   Goal Lift
        */
       if (master.get_digital(DIGITAL_L1))
       {
         if (gL.goalPresent())
         {  gL.moveTowards(gL.goalPos, gL.potVal());  }

         else
         {  gL.moveTowards(gL.topPos, gL.potVal());  }
       }

       else if (master.get_digital(DIGITAL_L2))
       {  gL.moveTowards(gL.bottomPos, gL.potVal());  }

       else
       {  gL.stop();  }



      /*
       *   Ring Intake
       */
      if (master.get_digital(DIGITAL_A))
      {  rI.latchPress();    }
      else
      {  rI.latchRelease();  }








       if (master.get_digital(DIGITAL_UP))
       {
         topBar.move(127);
         if (topBar.get_position() > 100)
         {
           doNeedle = true;
         }
       }
       else if (master.get_digital(DIGITAL_DOWN))
       {
           topBar.move(-127);
       }
       else
       {
           topBar.move(0);
       }






        // Lift
        if (master.get_digital(DIGITAL_R1))
        {
          if (topBar.get_position() < 300)
          {
            topBar.move(127);
          }
          else
          {
            backArmMove.move(127);
            backArmMove2.move(-127);
          }
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













       if(master.get_digital(DIGITAL_B))
       {
         if (!latchC)
         {
           doBackClaw = ! doBackClaw;
           latchC = true;
         }
       }
       else
       {
         latchC = false;
       }




       // Toggle needle
       if (master.get_digital(DIGITAL_LEFT))
       {
         if(!latchB){ //flip the toggle one time and set the latch
           doNeedle = !doNeedle;
           latchB = true;
         }
       }
       else {
         //Once the BumperA is released then then release the latch too
         latchB = false;
       }






       rI.run(topBar.get_position());





       if (doNeedle)
       {
           state = 1;
           actuator.set_value(state);
       }
       else
       {
           state = 0;
           actuator.set_value(state);
       }



       if (doBackClaw)
       {
         backClaw_state = 1;
         backClaw_actuator.set_value(backClaw_state);
       }
       else
       {
         backClaw_state = 0;
         backClaw_actuator.set_value(backClaw_state);
       }





       pros::delay(2);
   }
}
