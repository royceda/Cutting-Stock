/*
 * main.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

//#include "../include/Instance.h"
#include "../include/Dynamic.h"
#include "../include/Volume2.h"
#include "../include/Volume3.h"
//#include "../include/SousGradient.h"

using namespace std;

int main(int argc, char** argv) {
    Instance* inst = new Instance();
   // inst->generate(100, 13);
    inst->manual();
    //cout << (*inst) << endl;

    //Volume* volume = new Volume(inst);
   // volume->solve(0.1, inst);

    //Volume2* volume2 = new Volume2(inst);
    //volume2->solve(0.1,0.01,0.8);

    Volume3* vol = new Volume3(inst);
    vol->solve(0.1,0.01,0.8);
   // SousGradient* ssG = new SousGradient(inst);
   // ssG->solve();

    return 0;


}





