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

void Volume::solve(double alpha, Instance * inst) {
	int qty = inst->qty();
	vector<item*> knpSol;
	knpSol.reserve(qty);
	double * price = new double[qty];

	greedy(inst);

	for (int i = 0; i < qty; i++) {
		price[i] = (double) inst->data()[i]->_width / (double) inst->width();
	}

	Dynamic* knap = new Dynamic();

	knap->solve(inst, price, knpSol);


}

