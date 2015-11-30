/*
 * Dynamic.h
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#ifndef SCE_DYNAMIC_H_
#define SCE_DYNAMIC_H_

#include "../include/Instance.h"
#include <vector>


using namespace std;

class Dynamic {
public:
    Dynamic();
    virtual ~Dynamic();
    vector<double> solve(Instance* instance,vector<double> & price);
};

#endif /* SCE_DYNAMIC_H_ */
