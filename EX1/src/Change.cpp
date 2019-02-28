/*
 * Change.cpp
 */

#include "Change.h"


int min_coins(int *coinValues, int ind, int value){

	int coins = 0;

	while (value > 0){
		if (coinValues[ind] <= value){

			value -= coinValues[ind];
			++coins;
		}
		else --ind;
	}
	return coins;
}

string calcChange(int m, int numCoins, int *coinValues) {

	if (!m)
		return "";

	if (coinValues[0] > m)
		return "-";

	//Specific amount
	int best = 0;
	int coin_amount = 0;

	for (int i = 0; i < numCoins; ++i){
		int coins = min_coins(coinValues, i, m);
		if (coins < coin_amount || coin_amount == 0){
			coin_amount = coins;
			best = i;
		}
	}

	//Parse string
	//int ind = best[m];
	int ind = best;
	stringstream ss;
	while (m > 0){
		if (coinValues[ind] <= m){
			m -= coinValues[ind];
			ss << coinValues[ind] << ';';
		}
		else --ind;
	}

	return ss.str();
}





//Formulate table

/*int best [m + 1];
int coin_amount[m + 1];

for (int i = 0; i < numCoins; ++i){
	for (int j = 1; j <= m; ++j ){
		int coins = min_coins(coinValues, i, j);
		if (coins < coin_amount[j] || coin_amount[j] == 0){
			coin_amount[j] = coins;
			best[j] = i;
		}
	}
}
*/


//int ind = best[m];
