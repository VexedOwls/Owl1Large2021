#include "main.h"
#include "subsystemHeaders/drive.h"

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


void setDrive(float leftDrive, float rightDrive){
  backLeft.move(leftDrive);
  midLeft.move(leftDrive);
  frontLeft.move(leftDrive);

  backRight.move(rightDrive);
  midRight.move(rightDrive);
  frontRight.move(rightDrive);
}
