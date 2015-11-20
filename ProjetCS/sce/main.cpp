/*
 * main.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

//#include "../include/Instance.h"
#include "../include/Dynamic.h"

using namespace std;

int main(int argc, char** argv) {

	Instance* inst = new Instance();
	inst->generate(50, 200);
	cout << (*inst) << endl;




	return 0;
}





