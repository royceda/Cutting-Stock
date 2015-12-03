/*
 * Volume2.cpp
 *
 *  Created on: 27 nov. 2015
 *      Author: rduclos
 */

#include "../include/Volume2.h"

Volume2::Volume2() {
	// TODO Auto-generated constructor stub

}

Volume2::~Volume2() {
	// TODO Auto-generated destructor stub
}

Volume2::Volume2(Instance* inst) {

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
	}
}

double Volume2::greedy() {
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

double Volume2::step(double theta) {
	double norm = 0.0;
	for (int i = 0; i < _qty; i++) {
		norm += (_subGradiant[i] * _subGradiant[i]);
	}
	return theta * (_UB - _LB) / (norm);
}

double Volume2::stop() {
	double violation = 0;
	for (int i = 0; i < _qty; i++) {
		violation += _pi[i] * abs((1 - _x[i]));
	}
	return violation;
}

double Volume2::stopNorme1() {
	double stop1 = 0;
	for (int i = 0; i < _qty; i++) {
		stop1 += pow((1 - _x[i]), 2);
	}
	return sqrt(stop1);
}

double Volume2::stopNorme2() {
	double stop2 = 0;
	for (int i = 0; i < _qty; i++) {
		stop2 += pow((_bestPi[i] - _x[i]), 2);
	}
	return sqrt(stop2);
}

void Volume2::solve(double alpha, double epsilon, double theta) {

	double thetha = theta;
	cout << "hello" << endl;
	double bestResult = 0;

	double K = 0.0;

	_UB = greedy();
	cout << " UB : " << _UB << endl << endl;
	int W = _inst->width();
	Dynamic* knap = new Dynamic();
	for (int i = 0; i < _qty; i++) {
		_pi[i] = (double) _inst->data()[i]->_width / (double) W;
	}

	_newPattern = knap->solve(_inst, _pi);

	vector<double>::iterator it;
	cout << "premier pattern : ";
	for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
		cout << *it << ", ";
		_x[*it] += 1;
	}

	K = alpha;
	cout << endl;
	for (int i = 0; i < _qty; i++) {
		_subGradiant[i] = 1 - _x[i];
	}
	thetha *= 0.95;
	double stepA = step(thetha);
	cout << "Pemier StepA = " << stepA << endl;

	cout << "premier pi :";
	for (int i = 0; i < _qty; i++) {

		_pi[i] = stepA * _subGradiant[i];
		cout << _pi[i] << ", ";
	}
	cout << endl;
	int compteur = 1;
	double arret = stop();
	double result = 0;
	it = _newPattern.begin();
	while (it != _newPattern.end()) {
		result += _pi[*it];
		it++;
	}
	for (int i = 0; i < _qty; i++) {
		_LB += _pi[i];
	}
	if ((1 - result) < 0) {
		for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
			_LB += (1 - _bestPi[*it]);
			//_LB += (1 - result);
		}
	}
	//_LB *= (1 - alpha);
	cout << "Premier LB =  " << _LB << endl << endl;
	_bestLB = _LB;

	while (_LB < _UB) {

		_LB = 0;
		_newPattern = knap->solve(_inst, _pi);
		cout << "nouveau pattern : " << endl;

		for (int i = 0; i < _qty; i++) {
			_LB += _pi[i];
		}
		if ((1 - result) < 0) {

			for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
				_LB += (1 - _bestPi[*it]);
			}
		}
		if (_LB > _bestLB && _LB < _UB) {
			cout << "AMELIORATION, LB =  " << _LB << endl << endl;
			_bestLB = _LB;

		}

		for (int i = 0; i < _qty; i++) {
			_x[i] *= alpha;
		}

		K *= (1 - alpha);
		vector<double>::iterator it;
		for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
			cout << *it << ", ";
			_x[*it] += (1 - alpha);
		}

		K += alpha;
		cout << "K : " << K << endl;
		cout << endl;
		result = 0;
		it = _newPattern.begin();
		while (it != _newPattern.end()) {
			result += _pi[*it];
			it++;
		}
		if (result > bestResult) {
			bestResult = result;
			for (int i = 0; i < _qty; i++) {
				_bestPi[i] = _pi[i];
			}
		}

		for (int i = 0; i < _qty; i++) {
			cout << "x[" << i << "]" << _x[i] << " ";
			_subGradiant[i] = 1 - _x[i];
		}

		//////////////////////////

		double essai = 0;
		for (int i = 0; i < _qty; i++) {
			essai += _x[i] + _pi[i] * _subGradiant[i];

		}
		cout << endl << "essai : " << essai << endl << endl << endl;
		///////////////////////////

		cout << endl;
		thetha *= 0.95;
		stepA = step(thetha);
		cout << "Step : " << stepA << endl << endl;
		cout << "Pi : ";
		for (int i = 0; i < _qty; i++) {
			if (_bestPi[i] + stepA * _subGradiant[i] < 0) {
				_pi[i] = 0;
			} else {
				_pi[i] = _bestPi[i] + stepA * _subGradiant[i];
			}
			cout << i << ": " << _pi[i] << " ,";
		}
		cout << endl;
		compteur++;
		//arret = stop();
		//cout << "stop :" << arret << endl;
	}
	cout << "Compteur : " << compteur << endl;
	cout << "UB : " << _UB << endl;
	cout << "LB : " << _LB << endl;
	cout << "BestLb : " << _bestLB<< endl;
	cout << "K = " << K << endl;

}

