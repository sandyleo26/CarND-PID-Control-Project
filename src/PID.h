#ifndef PID_H
#define PID_H

#include <vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  std::vector<double> p;
  std::vector<double> dp;
  std::vector<double> states; // 0 -> err < best_err; 1 -> err >= best_err
  int counter;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  // temp variables
  double prev_cte;
  double sum_cte;
  double best_err;
  int prev_state;
  double steering;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);
  void update(int index, double cte);
  double GetSteering() const { return steering; }

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
