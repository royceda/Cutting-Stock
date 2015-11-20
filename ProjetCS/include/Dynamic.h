/*
 * Dynamic.h
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */


#include "../include/Instance.h"
#include <vector>



#ifndef SCE_DYNAMIC_H_
#define SCE_DYNAMIC_H_


using namespace std;

class Dynamic {
public:
	Dynamic();
	virtual ~Dynamic();
	int solve(Instance* instance, double * price, vector<double> & newPattern);
};

#endif /* SCE_DYNAMIC_H_ */
