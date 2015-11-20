/*
 * Volume.cpp
 *
 *  Created on: 20 nov. 2015
 *      Author: rduclos
 */

#include "../include/Volume.h"

Volume::Volume() {
	// TODO Auto-generated constructor stub

}

Volume::~Volume() {
	// TODO Auto-generated destructor stub
}

int Volume::greedy(Instance* inst) {

	vector<int> remaining;
	int qty = inst->qty();
	int W = inst->width();
	remaining.push_back(W);
	bool done = false;
	for (int i = 0; i < qty; i++) {
		for (int j = 0; j < (int) remaining.size(); j++) {
			if (remaining[j] - inst->data()[i]->_width >= 0) {
				remaining[j] -= inst->data()[i]->_width;
				_solution[i] = j;
				done = true;
				break;
			}
		}
		if (!done) {
			remaining.push_back(W - inst->data()[i]->_width);
			_solution[i] = (int) remaining.size();
		}
	}
	return remaining.size();
}

void Volume::computeX(double alpha, vector<double> newPattern) {
	for (int i = 0; i < (int) _solution.size(); i++) {
		_solution[i] = _solution[i] * alpha + newPattern[i] * (1 - alpha);
	}
}

void Volume::violation(Instance* inst) {
	int qty = inst->qty();
	for (int i = 0; i < qty; i++) {
		_subGradient[i] = 1 - _solution[i];
	}
}

double Volume::LB(Instance* inst, vector<double> & sol){
	int qty = inst->qty();
	double sum = 0;
	double* comple = new double[qty];
	double temp =0;
	double L =0;
	for(int i =0; i < qty; i++){
		sum += _subGradient[i];
		comple[i] = 1-_subGradient[i];
		temp += comple[i] * sol[i];
		L += sum + temp;
	}
	return L;
}

void Volume::solve(double alpha, Instance * inst) {
	int qty = inst->qty();
	vector<double> knpSol;
	knpSol.reserve(qty);
	_subGradient = new double[qty];

	greedy(inst);

	for (int i = 0; i < qty; i++) {
		_subGradient[i] = (double) inst->data()[i]->_width
				/ (double) inst->width();
	}

	Dynamic* knap = new Dynamic();

	knap->solve(inst, _subGradient, knpSol);




	computeX(alpha, knpSol);

	violation(inst);

}

