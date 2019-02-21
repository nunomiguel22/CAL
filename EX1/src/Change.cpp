/*
 * Change.cpp
 */

#include "Change.h"

#include <iostream>

string calcChange(int m, int numCoins, int *coinValues) {

	if (m <= 0) return "";

	for (int i = numCoins - 1; i >= 0; --i){
		if (coinValues[i] <= m){
			cout << coinValues[i] << endl;


			return to_string(coinValues[i]) + ';' + calcChange(m - coinValues[i], numCoins, coinValues);
		}
	}

	return "-";
}


