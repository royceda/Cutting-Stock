/*
 * Volume2.h
 *
 *  Created on: 27 nov. 2015
 *      Author: rduclos
 */

#ifndef SCE_VOLUME2_H_
#define SCE_VOLUME2_H_

#include "Dynamic.h"

class Volume2 {
private:
	vector <double> _x;
	vector <double> _pi;
	vector <double> _bestPi;
	vector <double> _subGradiant;
	vector <double> _newPattern;
	Instance* _inst;
	int _qty;
	double _LB;
	double _bestLB;
	double _UB;
public:
	Volume2();
	Volume2(Instance* inst);
	virtual ~Volume2();

	double greedy();
	void solve(double alpha, double epsilon, double theta);
	double step(double theta);
	double stop();
	double stopNorme1();
	double stopNorme2();


};

#endif /* SCE_VOLUME2_H_ */
