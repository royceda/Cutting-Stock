#ifndef SCE_GRADIANT_H_
#define SCE_GRADIANT_H_
#include "Dynamic.h"


using namespace std;

class SubGrad {

private:
    int            _g;
    vector<double> _solution;
    double*        _pi;
    double*        _bestPi;
    double         _LB;
    int            _UB;
    double*        _subGradiant;
    int            _n;

public:
    SubGrad();
    SubGrad(Instance* inst);
    virtual ~SubGrad();

    double LB(Instance* inst, vector<double> & sol); //calcul de la borne inf


    vector<double> solve(double alpha, Instance * inst); //resolution du problème
    void init_Pi(); //Initialisation de Pi
    void compute_g(); //Calcul du sous gradiant
    int greedy(Instance* inst); //borne sup par algo glouton
    double step(int theta); //calcul d'un pas pour le nouveau Pi
    void compute_Pi(double step); //Calcul du nouveau Pi

};
#endif /* SCE_GRADIANT_H_ */
