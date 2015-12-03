/*
 * Volume3.h
 *
 *  Created on: 3 déc. 2015
 *      Author: rduclos
 */

#ifndef SCE_VOLUME3_H_
#define SCE_VOLUME3_H_

#include "Instance.h"
#include "Dynamic.h"

class Volume3 {
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
	Volume3();
	Volume3(Instance* inst);
	void solve(double alpha, double epsilon, double theta);
	virtual ~Volume3();
	double greedy();
	void MajX(double alpha);
	void Gradiant();
	double Step(double thetha);
	void MajPi(double thetha);
	void printX();
	void printPi();
	void printNewPattern();
	void MajLB();
};

#endif /* SCE_VOLUME3_H_ */
