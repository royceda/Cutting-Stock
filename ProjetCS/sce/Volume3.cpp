/*
 * Volume3.cpp
 *
 *  Created on: 3 déc. 2015
 *      Author: rduclos
 */

#include "../include/Volume3.h"

Volume3::Volume3() {
	// TODO Auto-generated constructor stub

}

Volume3::~Volume3() {
	// TODO Auto-generated destructor stub
}

Volume3::Volume3(Instance* inst) {

	int qty = inst->qty();
	_x.reserve(qty);
	_pi.reserve(qty);
	_bestPi.reserve(qty);
	_subGradiant.reserve(qty);
	_newPattern.reserve(qty);
	_inst = inst;
	_qty = inst->qty();
	_LB = 0;
	_bestLB = 0;
	_UB = 0;
	for (int i = 0; i < qty; i++) {
		_x[i] = 0;
		_bestPi[i] = 0;
		_pi[i] =1;
	}
}

double Volume3::greedy() {
	vector<int> remaining;
	int W = _inst->width();
	std::cout << "W=" << W << "\n";

	remaining.push_back(W);
	bool done = false;
	for (int i = 0; i < _qty; i++) {
		int j = 0;
		done = false;
		while ((j < (int) remaining.size()) && (!done)) {
			if ((remaining[j] - _inst->data()[i]->_width) >= 0) {
				remaining[j] -= _inst->data()[i]->_width;
				done = true;
			}
			j++;
		}
		if (!done) {
			remaining.push_back(W - _inst->data()[i]->_width);
		}
	}
	return remaining.size();
}

void Volume3::MajX(double alpha) {
	for (int i = 0; i < _qty; i++) {
		_x[i] *= alpha;
	}
	vector<double>::iterator it;
	for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
		_x[*it] += (1 - alpha);
	}
}

void Volume3::Gradiant() {
	for (int i = 0; i < _qty; i++) {
		_subGradiant[i] = 1 - _x[i];
	}
}

double Volume3::Step(double thetha) {
	double stepA = 0;
	double norm = 0;
	for (int i = 0; i < _qty; i++) {
		norm += pow(_subGradiant[i], 2);
	}
	stepA = thetha * ((double) _UB - (double) _LB) / norm;
	cout << "step : " << stepA << endl;
	return stepA;
}

void Volume3::MajPi(double thetha) {
	double stepA = Step(thetha);
	for (int i = 0; i < _qty; i++) {
		_pi[i] = _bestPi[i] + stepA * _subGradiant[i];
	}
}

void Volume3::printX() {
	for (int i = 0; i < _qty; i++) {
		cout << "x" << i << " = " << _x[i] << ", ";
	}
	cout << endl;
}

void Volume3::printPi() {
	for (int i = 0; i < _qty; i++) {
		cout << "pi" << i << " = " << _pi[i] << ", ";
	}
	cout << endl;
}


void Volume3::printNewPattern(){
	vector<double>::iterator it;
	cout << "NewPattern : ";
	for(it = _newPattern.begin(); it != _newPattern.end(); it++){
		cout<< *it << " , ";
	}
	cout << endl;
}
void Volume3::MajLB() {
	double inf = 0;
	for (int i = 0; i < _qty; i++) {
		inf += _pi[i];
	}
	double result = 0;
	vector<double>::iterator it;
	for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
		result += 1 - _pi[*it];
	}
	if (result < 0) {
		inf += result;
	}
	if(inf > _LB){
		for(int i =0; i < _qty; i++){
			_bestPi[i] = _pi[i];
		}
		_bestLB = inf;
	}
	_LB = inf;
	cout << "LB = " << _LB << endl;
}
void Volume3::solve(double alpha, double epsilon, double theta) {

	Dynamic* knp = new Dynamic;
	double thetha = theta;

	_UB = greedy();

	_newPattern = knp->solve(_inst, _pi);
	printNewPattern();
	MajX(alpha);
	printX();
	Gradiant();
	MajPi(thetha);
	printPi();
	MajLB();

	while (_LB < _UB) {
		_newPattern = knp->solve(_inst, _pi);
		printNewPattern();

		MajX(alpha);
		printX();

		Gradiant();

		MajPi(thetha);
		printPi();

		MajLB();
		//thetha *= 0.95;
	}

}
