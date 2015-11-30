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

double Volume2::step(int theta) {
	double norm = 0.0;
	for (int i = 0; i < _qty; i++) {
		norm += (_subGradiant[i] * _subGradiant[i]);
	}
	return theta * (_UB - _LB) / (norm * norm);
}

double Volume2::stop() {
	double violation = 0;
	for (int i = 0; i < _qty; i++) {
		violation += _pi[i] * (1 - _x[i]);
	}
	return violation;
}

void Volume2::solve(double alpha, double epsilon, int theta) {

	cout << "hello" << endl;

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
	cout << endl;
	for (int i = 0; i < _qty; i++) {
		_subGradiant[i] = 1 - _x[i];
	}

	double stepA = step(theta);

	cout << "premier pi :" ;
	for (int i = 0; i < _qty; i++) {
		cout << _pi[i] << ", ";
		_pi[i] = _pi[i] + stepA * _subGradiant[i];
	}
	cout << endl;
	int compteur = 0;
	double arret = stop();
	for (int i = 0; i < _qty; i++) {
		if (_x[i] > 0) {
			_LB += _pi[i] + (1 - _pi[i]) * (_x[i]);
		}
	}
	cout << "Premier LB =  " << _LB << endl << endl;
	_LB = 0;
	while (arret > epsilon && compteur < 30) {

		_LB = 0;
		_newPattern = knap->solve(_inst, _pi);
		cout << "nouveau pattern : " << endl;
		vector<double>::iterator it;
		for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
			cout << *it << ", ";
			_x[*it] += alpha * _x[*it] + (1 - alpha);
		}
		cout << endl;
		for (int i = 0; i < _qty; i++) {
			if (_x[i] > 0) {
				_LB += _pi[i] + (1 - _pi[i]) * (_x[i]);
			}
		}
		if (_LB > _bestLB) {
			cout << "AMELIORATION, LB =  " << _LB << endl << endl;
			_bestLB = _LB;
			for (int i = 0; i < _qty; i++) {
				_bestPi[i] = _pi[i];
			}
		}
		for (int i = 0; i < _qty; i++) {
			cout << "x[" << i + 1 << "]" << _x[i] << " ";
			_subGradiant[i] = 1 - _x[i];
		}
		cout << endl;
		stepA = step(theta);
		cout << "Pi : ";
		for (int i = 0; i < _qty; i++) {
			cout << _pi[i] << " ,";
			_pi[i] = _bestPi[i] + stepA * _subGradiant[i];
		}
		cout << endl;
		compteur++;
		arret = stop();
		cout << "stop :" << arret << endl;
	}

}

