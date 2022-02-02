#ifndef goalLift
#define goalLift

#include "main.h"
using namespace pros;

class GoalLift
{
  public:
    int contrastVal;
    int bottomPos;
    int goalPos;
    int topPos;
    int marginOfError;

    Motor* rightMotor;
    Motor* leftMotor;
    ADIPotentiometer* potentiometer;
    ADILineSensor* sensor;

    GoalLift(Motor* _rightM, Motor* _leftM, ADIPotentiometer* _pot, ADILineSensor* _sens, int _contrast = 2905, int _bottomPos = 1050, int _goalPos = 1830, int _topPos = 2600, int _margin = 100);

    void setBrake(motor_brake_mode_e brake);
    void moveTowards(int target, int current);
    bool goalPresent();
    int potVal();
    void stop();
};

#endif
