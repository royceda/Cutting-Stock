<<<<<<< .mine
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
	_LB = 1;
	_bestLB = 1;
	_UB = 0;
	for (int i = 0; i < qty; i++) {
		_x[i] = 1;
		_bestPi[i] = 0;
		_pi[i] = 0;
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
	stepA = thetha * (((double) _UB - (double) _LB) / norm);
	cout << "step : " << stepA << endl;
	if (stepA < 0) {
		return 0;
	}
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

void Volume3::printNewPattern() {
	vector<double>::iterator it;
	cout << "NewPattern : ";
	for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
		cout << *it << " , ";
	}
	cout << endl;
}
void Volume3::MajLB(int compt, float alpha) {
	_LB = 0;
	double inf = 0.0;
	for (int i = 0; i < _qty; i++) {
		inf += _pi[i];
	}
	double result = 0.0;
	vector<double>::iterator it;
	for (it = _newPattern.begin(); it != _newPattern.end(); it++) {
		result += _pi[*it];
	}
	if (1 - result < 0) {
		cout << " !!!!!!!!!!!!" << endl;
		inf += _LB * (1 - result) ;
	}
	/*double result = 0.0;
	 for (int i = 0; i < _qty; i++) {
	 result += (1 - _pi[i]) * _x[i];
	 }
	 if(result < 0){
	 cout << " !!!!!!!!!!!!" << endl;
	 inf += result;
	 }
	 */

	if (inf > _bestLB) {
		for (int i = 0; i < _qty; i++) {
			_bestPi[i] = _pi[i];
		}
		if (compt > 1)
			_bestLB = inf;
	}
	_LB = inf;
	cout << "LB = " << _LB << endl;

}

double Volume3::NormeGradiant() {
	double norm = 0;
	for (int i = 0; i < _qty; i++) {
		norm += pow(_subGradiant[i], 2);
	}
	return sqrt(norm);
}

double Volume3::arret() {
	double arret = 0;
	for (int i = 0; i < _qty; i++) {
		arret += _pi[i] * _subGradiant[i];
	}
	return arret;
}

double Volume3::arret2() {
	double arret2 = 0;
	for (int i = 0; i < _qty; i++) {
		arret2 += _x[i] - _bestPi[i];
	}
	return arret2;
}

double Volume3::arret3(){
	double arret = 0;
	for(int i=0; i < _qty; i++){
		arret += _x[i];
	}
	return arret;
}

void Volume3::solve(double alpha, double epsilon, double theta,
		ofstream & log) {

	Dynamic* knp = new Dynamic;
	double thetha = theta;
	_LB =0;
	for (int i = 0; i < _qty; i++) {
		_pi[i] = (double) _inst->data()[i]->_width / (double) _inst->width();
		_bestPi[i] = _pi[i];
		_LB += _pi[i];
	}

	cout << "First LB = " << _LB << endl;
	printPi();

	_UB = greedy();
//_UB = _qty;
	_newPattern = knp->solve(_inst, _pi);
	//_newPattern = cplx.solve(_inst, _pi);
	printNewPattern();

	MajX(alpha);
	printX();

	MajLB(0, alpha);

	Gradiant();
	MajPi(thetha);
	printPi();

	MajLB(0, alpha);



//MajPi(thetha);
//printPi();

//MajLB(1);
//for (int i = 0; i < _qty; i++) {
//	_bestPi[i] = _pi[i];
//}
	cout << endl << endl;
	int compt = 1;

	while (compt < 100) { // && Step(thetha) > epsilon) { // && (_LB - arret()) > epsilon) { // && arret2() >0) {

		//_newPattern = knp->solve(_inst, _pi);

		//MOI
		Gradiant();

		MajPi(thetha);
		printPi();
		_newPattern.clear();
		_newPattern = knp->solve(_inst, _pi);
		//_newPattern = cplx.solve(_inst, _pi);
		printNewPattern();
		MajX(alpha);
		printX();
		MajLB(compt, alpha);

		thetha *= 0.9;

		//Ordre Remi
		/*_newPattern = cplx.solve(_inst,_pi);
		 printNewPattern();

		 Gradiant();


		 MajLB(compt);

		 MajPi(thetha);
		 printPi();

		 MajX(alpha);
		 printX();
		 */
		//thetha *= 0.95;
		compt++;

		log << compt << ";" << _LB << "\n";

		cout << "compteur = " << compt << endl;
		cout << "norme = " << NormeGradiant() << endl;
		cout << "arret = " << arret() << endl;
		cout << "arret2 = " << arret2() << endl;
		cout << "arret3 = " << arret3() << endl;
		cout << " UB = " << _UB << endl;
		//_UB *= alpha;

		cout << endl << endl;
	}
	cout << " Best = " << _bestLB << endl;
	cout << "LB = " << _LB << endl;
	cout << "arret = " << arret() << endl;

}
||||||| .r0
=======
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
>>>>>>> .r30
