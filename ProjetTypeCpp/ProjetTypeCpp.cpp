/*
* @author clement amphoux

* @file hanoi

* @date 27.10.2018

* @brief solves hanoi tower in the most efficient way, using a binary count

*/

#include "stdafx.h"

#include "Utils/Utils.hpp"

#include <iostream>
#include <fstream>
using namespace std;

void DisplayTowers(int** tab, int blockNb)
{
	for (int j = blockNb - 1; j >= 0; j--)
	{
		cout << '\t';
		for (int i = 0; i < 3; i++)
		{
			if (tab[i][j] != -1)
			{
				cout << tab[i][j] << " ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << endl;
	}
}

void Increment(int* tab, int index, int max)
{
	if (tab[index] == 0)
	{
		tab[index] = 1;
	}
	else
	{
		if (index < max)
		{
			tab[index] = 0;
			Increment(tab, index + 1, max);
		}
	}
}

void DisplayBinary(int* tab, int max)
{
	for (int i = max - 1; i >= 0; i--)
	{
		cout << tab[i];
	}
}

//update old tab + count nb of differencies
int NbOfRolls(int* tab, int* old, int max)
{
	int out = 0;
	for (int i = 0; i < max; i++)
	{
		if (tab[i] != old[i])
		{
			out++;
			old[i] = tab[i];
		}
	}
	return out;
}

struct Vector2i
{
	int x;
	int y;
};

Vector2i GetPoleOfBlockID(int** tab, int ID, int blockNb)
{
	Vector2i sortie;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < blockNb; j++)
		{
			if (tab[i][j] == ID)
			{
				sortie.x = i;
				sortie.y = j;
			}
		}
	}
	return sortie;
}

int FindLastIndexOfPole(int** tab, int index, int blockNb)
{
	int sortie = 0;
	for (int j = 0; j < blockNb; j++)
	{
		if (tab[index][j] != -1)
		{
			sortie = j;
		}
	}
	return sortie;
}

bool CanAddToPole(int** tab, int index, int ID, int blockNb)
{
	bool sortie = false;

	int lastIndex = FindLastIndexOfPole(tab, index, blockNb);
	if (ID < tab[index][lastIndex] || tab[index][lastIndex] == -1)
	{
		sortie = true;
	}
	return sortie;
}

int main()
{
	int blockNb;
	cout << "Enter nb of blocks ";
	cin >> blockNb;
	cin.clear(); cin.ignore(1000, '\n');

	//allocation 
	int* poles[3];
	for (int i = 0; i < 3; i++)
	{
		poles[i] = new int[blockNb];
	}

	//init a -1
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < blockNb; j++)
		{
			poles[i][j] = -1;
		}
	}

	//positionne tous les blocks dans l ordre sur le premier pole
	for (int i = 0; i < blockNb; i++)
	{
		poles[0][i] = blockNb - i;
	}
	DisplayTowers(poles, blockNb);

	//init le compteur binaire actu et precedent
	int* preBinary = new int[blockNb];
	int* binary = new int[blockNb];
	for (int i = 0; i < blockNb; i++)
	{
		binary[i] = 0;
		preBinary[i] = 0;
	}

	int totalMoves = 0;

	system("pause");
	system("cls");

	for (int i = 0; i < pow(2, blockNb) - 1; i++)
	{
		totalMoves++;
		system("cls");
		Increment(binary, 0, blockNb);
		DisplayBinary(binary, blockNb);
		cout << "\t total mooves: " << totalMoves << endl << endl;
		DisplayTowers(poles, blockNb);


		int pieceToMove = NbOfRolls(binary, preBinary, blockNb);

		Vector2i columPos = GetPoleOfBlockID(poles, pieceToMove, blockNb);
		poles[columPos.x][columPos.y] = -1;

		if (CanAddToPole(poles, (columPos.x + 1) % 3, pieceToMove, blockNb))
		{
			int lastIndex = FindLastIndexOfPole(poles, (columPos.x + 1) % 3, blockNb);
			if (poles[(columPos.x + 1) % 3][lastIndex] != -1)
			{
				lastIndex++;
			}
			poles[(columPos.x + 1) % 3][lastIndex] = pieceToMove;
		}
		else if (CanAddToPole(poles, (columPos.x + 2) % 3, pieceToMove, blockNb))
		{
			int lastIndex = FindLastIndexOfPole(poles, (columPos.x + 2) % 3, blockNb);
			if (poles[(columPos.x + 2) % 3][lastIndex] != -1)
			{
				lastIndex++;
			}
			poles[(columPos.x + 2) % 3][lastIndex] = pieceToMove;
		}
		system("pause");
	}
	system("cls");
	Increment(binary, 0, blockNb);
	DisplayBinary(binary, blockNb);
	cout << "\t total mooves: " << totalMoves << endl << endl;
	DisplayTowers(poles, blockNb);


	system("pause");
	return 0;
}

