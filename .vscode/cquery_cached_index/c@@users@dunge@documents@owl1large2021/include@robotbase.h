#ifndef robotBase
#define robotBase

#include "main.h"
using namespace pros;

class RobotBase
{
public:
  Motor* right1;
  Motor* right2;
  Motor* right3;
  Motor* left1;
  Motor* left2;
  Motor* left3;

  RobotBase(Motor* _r1, Motor* _r2, Motor* _r3, Motor* _l1, Motor* _l2, Motor* _l3);

  void move(int rightPower, int leftPower);

  void moveTo_Vision(int target, Vision* vision, int maxDist = 2, int stopSpeed = 20);

  void testVis(Vision* vision);
};

#endif
