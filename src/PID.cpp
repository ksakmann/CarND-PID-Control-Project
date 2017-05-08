#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::UpdateCoefficients(double Kp0, double Ki0, double Kd0, double alpha_p, double alpha_i,double alpha_d, double v) {

	Kp0_ = Kp0;
	Ki0_ = Ki0;
	Kd0_ = Kd0;

	alpha_p_ = alpha_p;
	alpha_i_ = alpha_i;
	alpha_d_ = alpha_d;

	v_ = v;

	Kp_ = Kp0_ + alpha_p_ * v_;
	Ki_ = Ki0_ + alpha_i_ * v_;
	Kd_ = Kd0_ + alpha_d_ * v_;

	return;
}

void PID::Init(double Kp0, double Ki0, double Kd0, double alpha_p, double alpha_i,double alpha_d, double v, double mem_frac) {

	PID::UpdateCoefficients(Kp0,Ki0,Kd0,alpha_p,alpha_i,alpha_d,v);

	mem_frac_ = mem_frac;

	p_error_= 0;
	i_error_ = 0;
	d_error_ = 0;
	total_error_ = 0;
	
	cte_ = 0;
	cte_prev_ = 0;
	cte_mem_ = 0;

	return;
}


void PID::UpdateError(double cte) {

	cte_prev_ = cte_;
	cte_ = cte;
	cte_mem_ = mem_frac_ * cte_mem_ + cte_;

	p_error_ = Kp_* cte_;
	i_error_ = Ki_ * cte_mem_;
	d_error_ = Kd_* (cte_-cte_prev_);

	return;

}

double PID::TotalError() {

	total_error_= p_error_ + d_error_ + i_error_;

	return total_error_;

}

