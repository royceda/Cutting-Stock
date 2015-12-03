/*
 * SousGradient.h
 *
 *  Created on: 30 nov. 2015
 *      Author: rduclos
 */

#ifndef SCE_SOUSGRADIENT_H_
#define SCE_SOUSGRADIENT_H_
#include "Instance.h"
#include "Dynamic.h"

class SousGradient {
private:
	Instance* _inst;
	int _qty;
	double _LB;
	double _UB;
	vector<double> ssGradient;

public:
	SousGradient();
	SousGradient(Instance* inst);
	double step(double theta, double lb);
	void solve();
	virtual ~SousGradient();
};

#endif /* SCE_SOUSGRADIENT_H_ */
