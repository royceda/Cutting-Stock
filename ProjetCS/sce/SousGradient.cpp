/*
 * SousGradient.cpp
 *
 *  Created on: 30 nov. 2015
 *      Author: rduclos
 */

#include "../include/SousGradient.h"
#include <algorithm>

SousGradient::SousGradient() {
	// TODO Auto-generated constructor stub

}

SousGradient::~SousGradient() {
	// TODO Auto-generated destructor stub
}

SousGradient::SousGradient(Instance* inst) {
	_inst = inst;
	_qty = _inst->qty();
	_UB = 0;
	ssGradient.reserve(_qty);

}

double SousGradient::step(double theta, double lb) {
	double norm = 0.0;
	for (int i = 0; i < _qty; i++) {
		norm += (ssGradient[i] * ssGradient[i]);
	}
	return theta * (_UB - lb) / (norm);
}

void SousGradient::solve() {
	int W = _inst->width();
	vector<double> pi;
	vector<double> newPattern;
	double theta = 2;

	ssGradient.reserve(_qty);
	int compteur = 0;
	for (int i = 0; i < _qty; i++) {
		ssGradient[i] = 1;
	}
	pi.reserve(_qty);
	for (int i = 0; i < _qty; i++) {
		pi.push_back((double) _inst->data()[i]->_width / (double) W);
	}

	Dynamic* knap = new Dynamic();

	double result = 1.0;
	while (result > 0) {

		for (int i = 0; i < _qty; i++) {
			ssGradient[i] = 1;
		}
		result = 0;
		newPattern = knap->solve(_inst, pi);

		vector<double>::iterator it = newPattern.begin();
		cout << "new Pattern : ";
		while (it != newPattern.end()) {
			cout << *it << ", ";
			ssGradient[*it] = 0;
			result += pi[*it];
			it++;
		}
		cout << endl;

		for (int i = 0; i < _qty; i++) {
			pi[i] = max(pi[i] + step(theta, result) * ssGradient[i],0.0);
		}
		cout << result << endl;
		compteur++;
	}
	cout << "pi :";
	for (int i = 0; i < _qty; i++) {
		cout << pi[i] << ", ";
	}
	cout << endl;

	//cout << "Borne: " << newPattern << endl;

}
