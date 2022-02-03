#include "robotBase.h"
RobotBase::RobotBase(Motor* _r1, Motor* _r2, Motor* _r3, Motor* _l1, Motor* _l2, Motor* _l3)
{
  right1 = _r1;
  right2 = _r2;
  right3 = _r3;
  left1 = _l1;
  left2 = _l2;
  left3 = _l3;
};

void RobotBase::move(int rightPower, int leftPower)
{
  right1->move(rightPower);
  right2->move(rightPower);
  right3->move(rightPower);

  left1->move(leftPower);
  left2->move(leftPower);
  left3->move(leftPower);
};



//316
//212

void RobotBase::testVis(Vision* vision)
{
  vision_object_s_t largestObj = vision->get_by_sig(0, 1);

  int error = 158 - largestObj.x_middle_coord;
  if (abs(error) > 5)
  {
    move(error, -error);
  }
  else
  {
    move(-50, -50);
  }
  std::cout << largestObj.x_middle_coord<<" "<<error << std::endl;
};


int mean(int val1, int val2)
{
  return ((val1 + val2)/2);
}

int clamp(int val, int max, int min)
{
  return (   std::max( std::min(val, max), min)   );
}


void RobotBase::moveTo_Vision(int distance, Vision* vision, int maxDist, int stopSpeed)
{
  double kP = 0.5; // 0.25
  double kI = 0.1; // 0.001
  double kD = 0.5; // 0.1
  double kV = 0; // 0.1
  int integral = 0;
  int previous_error = distance;
  int error = distance;
  int averageSpeed = 0;

  right1->tare_position();
  left1->tare_position();

  while(   abs(error)>maxDist   )  //  ||   abs(averageSpeed)>stopSpeed
  {
    error = distance - mean(right1->get_position(), left1->get_position());
    integral = integral + error;

    if (abs(error) < 2) { integral = 0; }
    if (abs(error) > 20) { integral = 0; }

    int derivative = error - previous_error;
    previous_error = error;

    vision_object_s_t largestObj = vision->get_by_sig(0, 1);
    int cameraError = 158 - largestObj.x_middle_coord;

    int rightSpeed = clamp(kP*error, 200, -200) + kI*integral + kD*derivative + kV*cameraError;
    int leftSpeed  = clamp(kP*error, 200, -200) + kI*integral + kD*derivative - kV*cameraError;

    averageSpeed = mean(rightSpeed, leftSpeed);
    move(rightSpeed, leftSpeed);
    // std::cout <<    error<<" | "<<error*kP<<" "<<integral*kI<<" "<<derivative*kD<<" "<<cameraError*kV<<" | "<<rightSpeed<<" "<<leftSpeed    << std::endl;
    delay(10);
  }

  move(0, 0);
};
