/*
 * Instance.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#include "../include/Instance.h"
using namespace std;

Instance::Instance() {
    _itemQty = 0;
    _masterWidth = 0;

}

Instance::~Instance() {
    _data.clear();
}

void Instance::generate() {

}

void Instance::manual(){
	_itemQty = 12;
	_data.push_back(new item(0,8));
	_data.push_back(new item(1,10));
	_data.push_back(new item(2,8));
	_data.push_back(new item(3,10));
	_data.push_back(new item(4,8));
	_data.push_back(new item(5,10));
	_data.push_back(new item(6,4));
	_data.push_back(new item(7,4));
	_data.push_back(new item(8,4));
	_data.push_back(new item(9,4));
	_data.push_back(new item(10,4));
	_data.push_back(new item(11,4));
	_masterWidth = 20;
}

void Instance::generate(int itemQty, int W) {
    _masterWidth = W;
    _itemQty = itemQty;
    _data.reserve(W);
    srand(time(NULL));

    int qty = _itemQty;
    int minWidth = W / 10;
    int id = 0;
    while (qty >= 0) {
        int width = minWidth + rand() % (W/2 );
        _data.push_back(new item(id, width));
        id++;
        qty--;
    }
}
int Instance::K(){
    return _K;
}

vector<item*> & Instance::data() {
    return _data;
}

int Instance::qty() {
    return _itemQty;
}

int Instance::width() {
    return _masterWidth;
}

ostream & operator<<(ostream & os, Instance & instance) {
    std::vector<item*>::iterator it;
    for (it = instance.data().begin(); it != instance.data().end();
            it++) {
        os << " item " << (*it)->_id;
        os << " width : " << (*it)->_width
                << endl;
    }
    return os;
}

