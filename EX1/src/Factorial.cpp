/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n) {

	if (n > 1)
		return n * factorialRecurs(n - 1);
	return n;
}

int factorialDinam(int n)
{
	int res = n;
	for (int i = 1; i < n; ++i){
		res *= i;
	}
	return res;
}
