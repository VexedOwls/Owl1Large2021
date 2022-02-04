#include "goalLift.h"

GoalLift::GoalLift(Motor* _rightM, Motor* _leftM, ADIPotentiometer* _pot, ADILineSensor* _sens, int _contrast, int _bottomPos, int _goalPos, int _topPos, int _margin)
{
  rightMotor = _rightM;
  leftMotor = _leftM;
  potentiometer = _pot;
  sensor = _sens;

  contrastVal = _contrast;
  bottomPos = _bottomPos;
  goalPos = _goalPos;
  topPos = _topPos;
  marginOfError = _margin;
};



void GoalLift::setBrake(motor_brake_mode_e brake)
{
  rightMotor->set_brake_mode(brake);
  leftMotor->set_brake_mode(brake);
};



void GoalLift::moveTowards(int target, int current)
{
  if (  (current-target)>marginOfError  )
  {
    leftMotor->move(-127);
    rightMotor->move(127);
  }
  else if (  (current-target)<-marginOfError  )
  {
    leftMotor->move(127);
    rightMotor->move(-127);
  }
  else
  {
    leftMotor->move(0);
    rightMotor->move(0);
  }
};

void GoalLift::moveToLoop(int target)
{
  if (  (potentiometer->get_value()-target)>marginOfError  )
  {
    leftMotor->move(-127);
    rightMotor->move(127);

    while( (potentiometer->get_value()-target)>marginOfError ) { delay(10); }
  }
  else if (  (potentiometer->get_value()-target)<-marginOfError  )
  {
    leftMotor->move(127);
    rightMotor->move(-127);

    while( (potentiometer->get_value()-target)<-marginOfError ) { delay(10); }
  }
  leftMotor->move(0);
  rightMotor->move(0);
};



// Return true when a goal is present in the lifter
bool GoalLift::goalPresent()
{
  return (sensor->get_value() < contrastVal);
};

int GoalLift::potVal()
{
  return potentiometer->get_value();
};

void GoalLift::stop()
{
  rightMotor->move(0);
  leftMotor->move(0);
};
