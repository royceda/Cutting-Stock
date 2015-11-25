/*
 * main.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

//#include "../include/Instance.h"
#include "../include/Dynamic.h"
#include "../include/Volume.h"

using namespace std;

int main(int argc, char** argv) {

	Instance* inst = new Instance();
	inst->generate(50, 200);
	//cout << (*inst) << endl;

	Volume* volume = new Volume(inst);
	volume->solve(0.1, inst);


	return 0;
}





