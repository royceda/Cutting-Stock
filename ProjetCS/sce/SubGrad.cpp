#include "../include/SubGrad.h"

SubGrad::SubGrad() {
	// TODO Auto-generated constructor stub

}

SubGrad::~SubGrad() {
	// TODO Auto-generated destructor stub
}

SubGrad::SubGrad(Instance* inst) {

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

	_n = 1000;

	for (int i = 0; i < qty; i++) {
		_x[i] = 0;
		_bestPi[i] = 0;
	}
	_UB  = greedy();
	cout << "UB: "<< _UB << endl;
}


double SubGrad::greedy() {
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


//compute (UB-LB(t))/norm(g(t))^2
double SubGrad::step(int theta) {
	double norm = 0.0;
	for (int i = 0; i < _qty; i++) {
		norm += (_subGradiant[i] * _subGradiant[i]);
	}
	return theta * (_UB - _LB) / (norm);
}



//violation de contraintes
double SubGrad::stop() {
	double violation = 0;
	for (int i = 0; i < _qty; i++) {
		violation += _pi[i] * (1 - _x[i]);
	}
	return violation;
}


void SubGrad::compute_Pi(double step){
	for (int i = 0; i < _qty; i++) {
		cout << _pi[i] << " ,";
		//evolution lente: pb de sub grad ???
		_pi[i] = _pi[i] + step * _subGradiant[i];
	}


void SubGrad::compute_g(){
	for (int i = 0; i < _qty; i++) {
		cout << "x[" << i + 1 << "]" << _x[i] << " ";
		_subGradiant[i] = 1 - _x[i];
	}
	cout << endl;
}


void SubGrad::init_Pi(){
	for (int i = 0; i < _qty; i++) {
		_pi[i] = (double) _inst->data()[i]->_width / (double) W;
	}
}

vector<double> SubGrad::solve(double alpha, double epsilon, int ) {
	//Initialisation (Normalement dans constructor)
	cout << "Begin " << endl;

	int W = _inst->width();
	Dynamic *knap = new Dynamic();

	//init du Pi[0]
	init_Pi();

	int k = 0;
	while(k < _n){
		//Une iteration k

		//Resolution de l'instance par (KP)
		_newPattern = knap->solve(_inst, _pi);
		cout << "New pattern:  " <<endl

		//La suite va différer des volumes mais la structure est identique

		//Calcul du sous-gradiant g[k] = (1 - x[k]) (vecteur)
		compute_g();

		//Calcul du pas s[k]
		stepA = step(theta);

		//Calcul du nouveau Pi[k]
		compute_Pi(stepA);

		k++;
	}
	//on renvoi la meilleur solution c'est à dire x[n] ( par convergence)
	return _x;
}
