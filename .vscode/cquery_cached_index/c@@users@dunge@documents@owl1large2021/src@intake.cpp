#include "intake.h"

RingIntake::RingIntake(Motor* _intake, int _lowBar, int _highBar, int _barPos)
{
  intakeRoller = _intake;

  lowTopBarSpeed = _lowBar;
  highTopBarSpeed = _highBar;
  highTopBarPos = _barPos;
};

void RingIntake::latchPress()
{
  if (!latch)
  {
    state = !state;
    latch = !latch;
  }
};

void RingIntake::latchRelease()
{
  if (latch)
  {
    latch = !latch;
  }
};






void RingIntake::run(int topBarPos)
{
  if (state)
  { move_topBar(topBarPos); }

  else
  { move(0); }
}

void RingIntake::move_topBar(int topBarPos)
{
  if (topBarPos < highTopBarPos)
  {  move(highTopBarSpeed);  }

  else
  {  move(lowTopBarSpeed);  }
};

void RingIntake::move(int speed)
{
  intakeRoller->move(-speed);
};
