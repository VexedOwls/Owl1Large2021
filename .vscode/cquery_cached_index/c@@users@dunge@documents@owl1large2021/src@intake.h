#ifndef ringIntake
#define ringIntake

#include "main.h"
using namespace pros;

class RingIntake
{
public:
  bool state = false;
  bool latch = false;
  int lowTopBarSpeed;
  int highTopBarSpeed;
  int highTopBarPos;

  Motor* intakeRoller;

  RingIntake(Motor* _intake, int _lowBar = 127, int _highBar = 90, int _barPos = -100);

  void move_topBar(int topBarPos);
  void move(int speed);
  void toggleLatch();
};

#endif
