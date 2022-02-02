#ifndef motors
#define motors

#include "main.h"
using namespace pros;



Motor goalLift_rightMotor(10);
Motor goalLift_leftMotor(1);
ADIAnalogIn goalLift_potentiometer('C');
Task *goalLift_currentTask = NULL;



#endif
