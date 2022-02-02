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

  RingIntake(Motor* _intake, int _lowBar = 115, int _highBar = 90, int _barPos = -100);

  void run(int topBarPos);
  void move_topBar(int topBarPos);
  void move(int speed);

  void latchPress();
  void latchRelease();
};

#endif
