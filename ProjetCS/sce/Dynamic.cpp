/*
 * Dynamic.cpp
 *
 *  Created on: 16 nov. 2015
 *      Author: rduclos
 */

#include "../include/Dynamic.h"

Dynamic::Dynamic() {
	// TODO Auto-generated constructor stub

}

Dynamic::~Dynamic() {
	// TODO Auto-generated destructor stub
}

vector<double> Dynamic::solve(Instance* instance, vector<double> & price) {
	int qty = instance->qty();
	vector<double> newPattern;
	int width = instance->width();
	double** tab = new double*[qty+1];

	for (int i = 0; i < qty+1; i++) {
		tab[i] = new double[width + 1];

	}
	for (int j = 0; j < width + 1; j++) {
		tab[0][j] = 0;
	}

	for (int i = 1; i < qty+1; i++) {
		for (int j = 0; j < width + 1; j++) {
			if (j >= instance->data()[i - 1]->_width) {
				tab[i][j] = max(tab[i - 1][j],
						tab[i - 1][j - instance->data()[i - 1]->_width]
								+ price[i - 1]);
			} else {
				tab[i][j] = tab[i - 1][j];

			}
		}
	}

	int profit = 0;
	// width--;
	for (int i = qty; i > 0; i--) {
		if (tab[i - 1][width] != tab[i][width]) {
			newPattern.push_back(instance->data()[i-1]->_id);
			profit += price[i-1];
			width -= instance->data()[i-1]->_width;

		}
		if (width < 0)
			break;
	}
	/*
	 vector<item*>::iterator it;
	 int tot = 0;
	 cout << "newPattern : ";
	 for(it = newPattern.begin(); it != newPattern.end(); it++){
	 tot += instance->data()[(*it)->_id]->_width;
	 cout << (*it)->_id << "- " ;
	 }
	 cout << "Largeur : " << tot << endl;
	 */
	return newPattern;

}

