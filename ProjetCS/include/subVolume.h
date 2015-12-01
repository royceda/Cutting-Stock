#ifndef SCE_SUBVOLUME_H_
#define SCE_SUBVOLUME_H_
#include "SubGrad.h"

using namespace std;

class SubVolume: public SubGrad {

private:
 double*  _piChapo;
 double   _d;
 double   _x;

public:
 SubGrad();
 SubGrad(Instance* inst);
 virtual ~SubGrad();

 vector<double> solve(double alpha, Instance * inst); //resolution du problème
 void compute_x(); //calcul de x
 void compute_d();//Calcul de d
 void compute_Pi(double step); //Calcul du nouveau Pi


 void compute_LB();//calcul de la borne inf

 void computeX(double alpha, vector<double> newPattern);
 void violation(Instance* inst);

 bool stopCondition(Instance* inst);
}





#endif /* SCE_SUBVOLUME_H_ */
