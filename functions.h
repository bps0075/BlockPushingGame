//this will contain all of the libraries, type definitions, structure definitions, and the list of function prototypes
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

enum actualObjects{BOX = 'B', AVATAR = 'A', WALL = 'X', HOME = 'H', SPACE = ' ', COMPLETE = 'C'};

struct Background
{
        actualObjects tile;
        bool isHomeEmpty = false;
	bool gameSaved;
};

void introduction();

void makeArray(Background**, int, int&, int&, ifstream&);

void showArray(Background**, int);

bool gameOver(Background**, int);

bool directionChoice(Background**, int, int&, int&, int&, ifstream&);

bool up(Background**, int, int&, int&);
bool down(Background**, int, int&, int&);
bool left(Background**, int, int&, int&);
bool right(Background**, int, int&, int&);

#endif
