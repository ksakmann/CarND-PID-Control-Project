#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

	Kp_ = Kp;
	Ki_ = Ki;
	Kd_ = Kd;

	return;
}

void PID::UpdateError(double cte) {

	p_error = Kp_*cte;
	d_error = Kd_*(cte-cte_prev);
	i_error += Ki_ * cte;

}

double PID::TotalError() {

	return p_error + d_error + i_error;

}

