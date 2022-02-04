#ifndef robotBase
#define robotBase

#include "main.h"
using namespace pros;

#define _INCHES *28.6479

class RobotBase
{
private:
  void resetPos();
  int minRightMeasure();
  int minLeftMeasure();
  int rightMaxError(int target);
  int leftMaxError(int target);

public:
  Motor* right1;
  Motor* right2;
  Motor* right3;
  Motor* left1;
  Motor* left2;
  Motor* left3;

  RobotBase(Motor* _r1, Motor* _r2, Motor* _r3, Motor* _l1, Motor* _l2, Motor* _l3);

  void move(int rightPower, int leftPower);

  void movePID(int target, int maxDist = 2);
  void moveGyro(int target, Imu* imu, bool console = false, int precision = 5);
  void turnGyro(double target, Imu* imu, bool console = false, double precision = 0.1);
};

#endif
