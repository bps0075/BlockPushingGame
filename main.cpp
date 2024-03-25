//Brandon Sharp
//This program is about pushing boxes from their original location to the home loction
//Got help from Joseph Helsing
#include "functions.h"

int main()
{
	introduction();

	ifstream inString;

	//initializing array pointer memory space
	Background** arr = new Background*[15];
	for(int i = 0; i < 15; i++)
	{
		arr[i] = new Background[15];
	}

	int numMoves = 0;
	int xAv;
	int yAv;
	arr[0][0].gameSaved = false;

	makeArray(arr, 15, xAv, yAv, inString);//calls the function to set up the board

	do
	{

	        showArray(arr, 15);//calls the function that outputs the array throughout the game

	}while((directionChoice(arr, 15, xAv, yAv, numMoves, inString) == false) && (gameOver(arr, 15) == false) && (arr[0][0].gameSaved == false));

	showArray(arr, 15);

	if(gameOver(arr, 15) == true)
	{
		cout << "Great job, you won the game in " << numMoves << " moves!" << endl;
	}

	inString.close();
	delete[] arr;

	return 0;
}
