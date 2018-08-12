#include <limits>
#include <iostream>

#include "PID.h"


using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  p_error = 1.0;
  i_error = 1.0;
  d_error = 1.0;

  counter = 0;
  for (int i = 0; i < 3; i++) {
    states.push_back(0);
    dp.push_back(1.0);
    p.push_back(0);
  }

  p[0] = Kp;
  p[1] = Ki;
  p[2] = Kd;

  prev_cte = 0.0;
  sum_cte = 0.0;
  best_err = std::numeric_limits<double>::max();
  steering = 0.0;
}

void PID::UpdateError(double cte) {
  if (TotalError() < 0.2)
    return;

  steering = -p[0] * cte - p[1] * sum_cte - p[2] * (cte - prev_cte);
  if (steering > 1) steering = 1;
  if (steering < -1) steering = -1;

  std::cout << std::endl;
  std::cout << "Kp: " << p[0] << " Ki: " << p[1] << " Kd: " << p[2] << std::endl;
  std::cout << "dp[0]: " << dp[0] << " dp[1]: " << dp[1] << " dp[2]: " << dp[2] << std::endl; 

  prev_cte = cte;
  sum_cte += cte;

  int index = counter++ / 2 % 2;
  update(index, cte);

}

void PID::update(int i, double cte) {
  double err = cte * cte;
  if (states[i] == 0)
  {
    if (err < best_err)
    {
      best_err = err;
      dp[i] *= 1.1;
      p[i] += dp[i];
    }
    else
    {
      p[i] -= 2 * dp[i];
      states[i] = 1;
    }
  }
  else
  {
    if (err < best_err)
    {
      best_err = err;
      dp[i] *= 1.1;
    }
    else
    {
      p[i] += dp[i];
      dp[i] *= 0.9;
    }
    p[i] += dp[i];
    states[i] = 0;
  }
}

double PID::TotalError() {
  return dp[0] + dp[1] + dp[2];
}

