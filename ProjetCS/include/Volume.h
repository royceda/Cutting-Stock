/*
 * Volume.h
 *
 *  Created on: 20 nov. 2015
 *      Author: rduclos
 */

#ifndef SCE_VOLUME_H_
#define SCE_VOLUME_H_
#include "Dynamic.h"

using namespace std;

class Volume {
	private :
	int _g;
	double _d;
	vector<int> _solution;


public:
	Volume();
	virtual ~Volume();
	void solve(double alpha, Instance * inst);
	int greedy(Instance* inst);
};

#endif /* SCE_VOLUME_H_ */
