/*
 * Instance.h
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#ifndef INCLUDE_INSTANCE_H_
#define INCLUDE_INSTANCE_H_

using namespace std;

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ostream>
#include <iostream>

struct item {
    int _id;
    int _width;

    item(int id, int width) {
        _id = id;
        _width = width;
    }
};

class Instance {
private:
    int _itemQty;
    vector<item*> _data;
    int _masterWidth;
    int _K;
public:
    Instance();
    virtual ~Instance();
    void manual();
    void generate();
    void generate(int itemQty, int W);
    vector<item*> & data();
    int qty();
    int width();
    int K();
    friend ostream & operator<<(ostream & os, Instance & instance);
};



#endif /* INCLUDE_INSTANCE_H_ */
