/*
 * Volume.h
 *
 *  Created on: 20 nov. 2015
 *      Author: rduclos
 */

#ifndef SCE_VOLUME_H_
#define SCE_VOLUME_H_
#include "Dynamic.h"

using namespace std;

class Volume {
	private :
	int _g;
	double _d;
	vector<double> _solution;
	double* _pi;
	double* _piChapo;
	double _LB;
	int _UB;
	double* _subGradiant;

public:
	Volume();
	Volume(Instance* inst);
	virtual ~Volume();
	void solve(double alpha, Instance * inst);
	void computeX(double alpha, vector<double> newPattern);
	void violation(Instance* inst);
	double LB(Instance* inst, vector<double> & sol);
	bool stopCondition(Instance* inst);
	int greedy(Instance* inst);
};

#endif /* SCE_VOLUME_H_ */
