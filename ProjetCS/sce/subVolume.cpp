#include "../include/SubVolume"


SubGrad();
SubVolume::SubGrad(Instance* inst){
/*utilisation de super et les init des nouvelles var*/
}

virtual SubVolume::~SubGrad(){}

void SubVolume::compute_x(){}
void SubVolume::compute_d(){}
void SubVolume::compute_Pi(double step){}

 void SubVolume::compute_LB(){}

vector<double> solve(double alpha, Instance * inst){
 //Normalement l'Initialisationest faite dans la construction

//Calcul de la solution dual avec Pi[k]

int k = 0;
while(k < _n){
 //iteration k


 //resolution du (KP): z[k]

 //sous gradiant
 compute_g();

 //Borne inf
 compute_LB();


 //Vericafition des conditions d'optimalité


 //MAJ des Pi_chapo et LB


 //Vericafition des conditions d'optimalité pour le  dual

 k++;
}

 return _x;
}
