/*
 * Partioning.cpp
 */

#include "Partitioning.h"

#include <iostream>

int s_recursive(int n,int k)
{
	if (k > 1 && k < n){
		int val = s_recursive(n-1, k-1) + k*s_recursive(n-1, k);
		return val;

	}
	else return 1;
}

int s_dynamic(int n,int k)
{

	return 1;
}


int b_recursive(int n)
{
	static int k = 0;
	++k;
	if (k > n)
		return 0;

	return s_recursive(n, k) + b_recursive(n);
}

int b_dynamic(int n)
{
	unsigned int total = 0;
	for (int i = 1; i <= n; ++i){
		total += s_recursive(n, i);
	}
	return total;
}


