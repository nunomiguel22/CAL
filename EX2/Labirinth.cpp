/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}

void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{

	if (labirinth[x][y] == 2){
		return true;

	}
	if (!visited[x][y]){
		visited[x][y] = true;

		//Celula abaixo
		if (labirinth[x][y - 1])
			if (findGoal(x, y - 1))
				return true;
		//Celula acima
		if (labirinth[x][y + 1])
			if (findGoal(x, y + 1))
				return true;
		//Celula a esquerda
		if (labirinth[x - 1][y])
			if (findGoal(x - 1, y))
				return true;
		//Celula a direita
		if (labirinth[x + 1][y])
			if (findGoal(x + 1, y))
				return true;
	}

	return false;
}


