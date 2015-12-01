#ifndef SCE_GRADIANT_H_
#define SCE_GRADIANT_H_
#include "Dynamic.h"


using namespace std;

class SubGrad {

private:
    int            _g;
    double         _d;
    vector<double> _solution;
    double*        _pi;
    double*        _piChapo;
    double         _LB;
    int            _UB;
    double*        _subGradiant;

public:
    SubGrad();
    SubGrad(Instance* inst);
    virtual ~SubGrad();
    void solve(double alpha, Instance * inst);


    void computeX(double alpha, vector<double> newPattern);
    void violation(Instance* inst);
    double LB(Instance* inst, vector<double> & sol);
    bool stopCondition(Instance* inst);
    int greedy(Instance* inst);
};










#endif /* SCE_GRADIANT_H_ */
