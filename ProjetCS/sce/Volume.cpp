/*
 * Volume.cpp
 *
 *  Created on: 20 nov. 2015
 *      Author: rduclos
 */

#include "../include/Volume.h"

Volume::Volume() {
}

Volume::Volume(Instance* inst) {
    // TODO Auto-generated constructor stub
    int qty = inst->qty();
    _pi = new double[qty];
    _piChapo = new double[qty];
    _subGradiant = new double[qty];
    _solution.reserve(qty);
}

Volume::~Volume() {
    // TODO Auto-generated destructor stub
}

int Volume::greedy(Instance* inst) {
    vector<int> remaining;
    int qty = inst->qty();
    int W = inst->width();
    std::cout<<"W="<<W<<"\n";
    for (int i = 0; i < qty; i++) {
        cout<<"item "<<i<<" : "<<inst->data()[i]->_width <<"\n";
    }

    remaining.push_back(W);
    bool done = false;
    for (int i = 0; i < qty; i++) {
        int j = 0;
        done = false;
        while((j<remaining.size())&&(!done)){
            cout<<i<<" "<<j<<" : "<<(remaining[j] - inst->data()[i]->_width)<<"?"<<((remaining[j] - inst->data()[i]->_width) >= 0)<<"\n";
            if ((remaining[j] - inst->data()[i]->_width) >= 0) {
                remaining[j] -= inst->data()[i]->_width;
                cout<<"mmmmmmmmm\n";
                _solution[i] = j;
                done = true;
            }
            j++;
        }
        if (!done) {
            cout<<"NEEEEEW\n";
            remaining.push_back(W - inst->data()[i]->_width);
            _solution[i] = remaining.size() - 1;
        }
    }
    for (int i = 0; i < qty; i++) {
        cout<<"sol["<<i<<"]="<<_solution[i]<<"\n";
    }

    return remaining.size();
}

void Volume::computeX(double alpha, vector<double> newPattern) {
    for (int i = 0; i < (int) _solution.size(); i++) {
        _solution[i] = _solution[i] * alpha + newPattern[i] * (1 - alpha);
    }
}

bool Volume::stopCondition(Instance* inst) {
    double epsilon = 0.0001;
    int qty = inst->qty();
    for (int i = 0; i < qty; i++) {
        if ((-epsilon < _subGradiant[i]) && (_subGradiant[i] < epsilon))
            return true;
    }
    return false;
}

void Volume::violation(Instance* inst) {
    int qty = inst->qty();
    double st;
    int theta = 1; //between 0 and 2
    for (int i = 0; i < qty; i++) {
        _subGradiant[i] = 1 - _solution[i];
        cout<<"vio["<<i<<"]="<<_solution[i]<<"\n";
    }
    double norm = 0.0;
    for (int i = 0; i < qty; i++) {
        norm += (_subGradiant[i] * _subGradiant[i]);
    }
    st = theta * (_UB - _LB) / norm;
    for (int i = 0; i < qty; i++) {
        _pi[i] = _piChapo[i] + st * _subGradiant[i];
    }
}

double Volume::LB(Instance* inst, vector<double> & sol) {
    int qty = inst->qty();
    double sum = 0.0;
    double* comple = new double[qty];
    double temp = 0.0;
    double L = 0.0;
    for (int i = 0; i < qty; i++) {
        sum += _pi[i];
        comple[i] = 1 - _pi[i];
        temp += comple[i] * sol[i];
        L += sum + temp;
    }
    return L;
}

void Volume::solve(double alpha, Instance * inst) {
    
    int qty = inst->qty();
    _pi = new double[qty];

    // x zero
    _UB = greedy(inst);

    // pi zero
    for (int i = 0; i < qty; i++) {
        _pi[i] = (double) inst->data()[i]->_width / (double) inst->width();
    }

    Dynamic* knap = new Dynamic();

    cout << "Dynamic";
    // z zero
    vector<int> newPattern;
    newPattern = knap->solve(inst, _pi);

    // LB = l chapeau
    _LB = LB(inst, _solution);
    // pi chapeau
    for (int i = 0; i < qty; i++) {
        _piChapo[i] = _pi[i];
    }

    violation(inst);

    computeX(alpha, _solution);
    int iteration = 0;
    while (/*!stopCondition(inst)*/iteration<5) {
        newPattern.clear();
        newPattern = knap->solve(inst, _pi);
        int lowerBound = LB(inst, _solution);
        if (_LB <= lowerBound) {
            _LB = lowerBound;
            for (int i = 0; i < qty; i++) {
                _piChapo[i] = _pi[i];
            }
        }
        violation(inst);

        computeX(alpha, _solution);
        iteration ++;
        cout<<"iteration"<<iteration<<"\n";
            for (int i = 0; i < qty; i++) {
        cout << "g[" << i << "] = " << _subGradiant[i] << "\n";
    }
    }

    cout << " \n finished\n";

}

