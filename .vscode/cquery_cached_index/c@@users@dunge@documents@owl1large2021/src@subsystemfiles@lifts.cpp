#include "main.h"

//Front arm
pros::Motor frontArm(1);
pros::Motor frontArm2(10);
//Back arm
pros::Motor backArm(2);
pros::Motor backArm2(9);
//Top bar
pros::Motor topBar(6);
//conveyor
pros::Motor swirlyDo(5);
//

frontArm.set_brake_mode(MOTOR_BRAKE_HOLD);
frontArm2.set_brake_mode(MOTOR_BRAKE_HOLD);
backArm.set_brake_mode(MOTOR_BRAKE_HOLD);
backArm2.set_brake_mode(MOTOR_BRAKE_HOLD);
topBar.set_brake_mode(MOTOR_BRAKE_HOLD);

void setFrontArm(float position, float speed){
  frontArm.move_relative(position, speed);
  frontArm2.move_relative(position, speed);
}

void rawFrontArm(float speed){
  frontArm.move(speed);
  frontArm2.move(-speed);
}
