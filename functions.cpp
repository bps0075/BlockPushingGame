//this will contain all of the functions
#include "functions.h"

void introduction()
{
	cout << "My name is Brandon Sharp and my UNT email is " << endl << "BrandonSharp@my.unt.edu"<< endl << endl;
        cout << "You are playing a game where you have to push boxes to the home space." << endl;
        cout << "The levels will get more difficult over time." << endl;
}

void makeArray(Background** arr, int size, int& xAv, int& yAv, ifstream& inString)
{
        string letters;

        string fileName;
        cout << "Enter the file name or the saved game file: ";
        cin >> fileName; //type file name
        //opens and compares file
        inString.open(fileName);
        if(!inString.is_open())
        {
                cout << "File will not open." << endl;
                exit(EXIT_FAILURE);//exits if it can not open the file
        }

        for(int i = 0; i < 15; i++)//goes through 15 getlines
        {
                getline(inString, letters);
		int count = 0;
                for(int h = 0; h < 30; h++)
                {
                        switch(letters[h])
                        {
                                case BOX:
                                arr[count][i].tile = BOX;
                                count++;
                                break;
                                case AVATAR:
                                arr[count][i].tile = AVATAR;
                                xAv = count;//make x and y = location of A
                                yAv = i;
                                count++;
                                break;
                                case WALL:
                                arr[count][i].tile = WALL;
                                count++;
                                break;
                                case HOME:
                                arr[count][i].tile = HOME;
                                count++;
                                break;
                                case SPACE:
                                arr[count][i].tile = SPACE;
				count++;
                                break;
                                //default: //code that is executed if input doe$
                                //cout << " ";
                        }
                }
        }
        cout << endl;
}

void showArray(Background** arr, int size)
{
        for(int i = 0; i < size; i++)
        {
                for(int h = 0; h < size; h++)
                {
			if(arr[h][i].tile == SPACE)
                        {
                                cout << ' ' << " ";
                        }
			else if(arr[h][i].tile == WALL)
                        {
                                cout << 'X' << " ";
                        }
                        else if(arr[h][i].tile == BOX)
                        {
                                cout << 'B' << " ";
                        }
			else if(arr[h][i].tile == AVATAR)
                        {
                                cout << 'A' << " ";
                        }
			else if(arr[h][i].tile == HOME)
                        {
                                cout << 'H' << " ";
                        }
			else if(arr[h][i].tile == COMPLETE)
                        {
                                cout << 'B' << " ";
                        }
                        else
                        {
                                cout << arr[h][i].tile << " ";
                        }
			/*if(arr[h][i].tile == COMPLETE)
			{
				cout << 'B' << " ";
			}
			else
			{
				cout << static_cast<char>(arr[h][i].tile) << " ";
			}*/
                }
                cout << endl;
        }
}
bool gameOver(Background** arr, int size)
{
	bool gameCompleted = true;
        for(int i = 0; i < size; i++)
        {
                for(int h = 0;  h < size; h++)
                {
                        if((arr[h][i].tile == HOME) || (arr[h][i].isHomeEmpty == true))
                        {
                                gameCompleted = false;//if it is false then the game will keep going
                        }
                }
        }
        return gameCompleted;
}

bool directionChoice(Background** arr, int size, int& xAv, int& yAv, int& numMoves, ifstream& inString)
{
        bool quitGame = false; //helps determine if the user quit the game
        cout << endl << "Avatar location: " << (xAv + 1) << ", " << (yAv + 1) << endl;
        cout << "Number of moves used: " << numMoves << endl;
        string direction;
        cout << "Which direction do you want to go (up, down, left, right)? You can also quit by typing the letter Q? " << endl;
	cout << "If you can not win, then you can also choose to reset the board by typing the letter R? " << endl; //extra credit reset option
	cout << "If you also want to save your game then type the letter S? "; //extra creding for saving a game option
        cin >> direction; //what the player chooses to do
        bool isMoved = false;
        if(direction == "up")//if the player goes up
        {
                isMoved = up(arr, 15, xAv, yAv);
                if(isMoved == true)
                {
                        numMoves++;
                }
        }
        else if(direction == "down")//if the player goes down
        {
                isMoved = down(arr, 15, xAv, yAv);
                if(isMoved == true)
                {
                        numMoves++;
                }
        }
        else if(direction == "left")//if the player moves left
        {
                isMoved = left(arr, 15, xAv, yAv);
                if(isMoved == true)
                {
                        numMoves++;
                }
        }
        else if(direction == "right")//if the player moves right
        {
                isMoved = right(arr, 15, xAv, yAv);
                if(isMoved == true)
                {
                        numMoves++;
                }
        }
	else if(direction == "Q")//if the player quits
        {
                cout << "You gave up." << endl;
                quitGame = true;
        }
	else if(direction == "R")//if the player resets
	{
		inString.close();
		makeArray(arr, 15, xAv, yAv, inString);//calls the main function reset the board
		numMoves = 0;
		cout << "Congradulations, you have reset the game." << endl;
	}
	else if(direction == "S")//if the player saves the game
	{
		//output array to file, make sure it does not equal the original input file
		char gameFile[20];
		arr[0][0].gameSaved = true;
		cout << "What do you want your save file to be? " << endl;
		cin >> gameFile;

		fstream ioString;
		ioString.open(gameFile, fstream::out);
		if(!ioString.is_open())
        	{
                	cout << "File will not save." << endl;
                	exit(EXIT_FAILURE);//exits if it can not open the file
        	}
		//I could not exactly figure out how to compare inString to gameFile
		// so I used "input1.txt" as a default string
		if(strcmp(gameFile,"input1.txt") != 0)
		{
			for(int i = 0; i < size; i++)
        		{
                		for(int h = 0; h < size; h++)
                		{
					if(arr[h][i].tile == COMPLETE)
                			{
                		        	ioString << 'B' << ",";
                			}
                			else
                			{
                	        		ioString << static_cast<char>(arr[h][i].tile) << ",";
                			}
				}
				ioString << endl;
			}
			cout << "You have saved the game." << endl;
			ioString.close();
		}
		else
		{
			cout << "Can not name save file as input file." <<  endl;
                	directionChoice(arr, 15, xAv, yAv, numMoves, inString);
		}
	}
        else
        {
                cout << "This is invalid, try again." << endl;
                directionChoice(arr, 15, xAv, yAv, numMoves, inString);
        }
        return quitGame;
}

bool up(Background** arr, int size, int& xAv, int& yAv)
{
        bool isMoved = false;
        if(arr[xAv][yAv - 1].tile == SPACE)
        {
                cout << endl << "You moved up." << endl;
                arr[xAv][yAv].tile = SPACE;
                yAv = yAv - 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

		if(arr[xAv][yAv + 1].isHomeEmpty == true) //this is when leaving the home space
                {
                        arr[xAv][yAv + 1].tile = HOME;
                        arr[xAv][yAv + 1].isHomeEmpty = false;
                }
	}
	else if(arr[xAv][yAv - 1].tile == HOME) //this is when entering the home space
        {
                cout << endl << "You moved to the home space." << endl;
                arr[xAv][yAv].tile = SPACE;
                yAv = yAv - 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

                arr[xAv][yAv].isHomeEmpty = true;
                cout << arr[xAv][yAv].isHomeEmpty << endl;
        }
        else if(arr[xAv][yAv - 1].tile == COMPLETE)
        {
                cout << endl << "You cannot move the box once it is home" << endl;
        }
        else if(arr[xAv][yAv - 1].tile == WALL)
        {
                cout << endl << "There is a wall so it is invalid. " << endl;
        }
        else if(arr[xAv][yAv - 1].tile == BOX)
	{
                if(arr[xAv][yAv - 2].tile == BOX)
                {
                        cout << endl << "There are 2 boxes in a row, you can not move." << endl;
                }
                else if(arr[xAv][yAv - 2].tile == WALL)
                {
                        cout << endl << "You cannot push the box into the wall." << endl;
                }
                else if(arr[xAv][yAv - 2].tile == HOME)
                {
                        cout << endl <<"You got a box home." << endl;
                        arr[xAv][yAv - 2].tile = COMPLETE;

                        arr[xAv][yAv].tile = SPACE;
                        yAv = yAv - 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;
                }
                else if(arr[xAv][yAv - 2].tile == SPACE)
                {
                        cout << endl << "You pushed the box one space." << endl;
                        arr[xAv][yAv - 2].tile = BOX;

                        arr[xAv][yAv].tile = SPACE;
                        yAv = yAv - 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;

			if(arr[xAv][yAv + 1].isHomeEmpty == true) //this is when leaving the home space
                	{
                        	arr[xAv][yAv + 1].tile = HOME;
                        	arr[xAv][yAv + 1].isHomeEmpty = false;
                	}
		}
        }
        return isMoved;
}

bool down(Background** arr, int size, int& xAv, int& yAv)
{
        bool isMoved = false;
        if(arr[xAv][yAv + 1].tile == SPACE)
        {
                cout << endl << "You moved down." << endl;
                arr[xAv][yAv].tile = SPACE;
                yAv = yAv + 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

		if(arr[xAv][yAv - 1].isHomeEmpty == true) //this is when leaving the home space
                {
                        arr[xAv][yAv - 1].tile = HOME;
                        arr[xAv][yAv - 1].isHomeEmpty = false;
                }
	}
	else if(arr[xAv][yAv + 1].tile == HOME) //this is when entering the home space
        {
                cout << endl << "You moved to the home space." << endl;
                arr[xAv][yAv].tile = SPACE;
                yAv = yAv + 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

                arr[xAv][yAv].isHomeEmpty = true;
                cout << arr[xAv][yAv].isHomeEmpty << endl;
        }
        else if(arr[xAv][yAv + 1].tile == WALL)
        {
                cout << endl << "There is a wall so it is invalid. " << endl;
        }
        else if(arr[xAv][yAv + 1].tile == COMPLETE)
        {
                cout << endl << "You cannot move the box once it is home" << endl;
        }
        else if(arr[xAv][yAv + 1].tile == BOX)
	{
		if(arr[xAv][yAv + 2].tile == BOX)
                {
                        cout << endl << "There are 2 boxes in a row, you can not move." << endl;
                }
                else if(arr[xAv][yAv + 2].tile == WALL)
                {
                        cout << endl << "You cannot push the box into the wall." << endl;
                }
                else if(arr[xAv][yAv + 2].tile == HOME)
                {
                        cout << endl << "You got a box home." << endl;
                        arr[xAv][yAv + 2].tile = COMPLETE;

                        arr[xAv][yAv].tile = SPACE;
                        yAv = yAv + 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;
                }
		else if(arr[xAv][yAv + 2].tile == SPACE)
                {
                        cout << endl << "You pushed the box one space." << endl;
                        arr[xAv][yAv + 2].tile = BOX;

                        arr[xAv][yAv].tile = SPACE;
                        yAv = yAv + 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;

			if(arr[xAv][yAv - 1].isHomeEmpty == true) //this is when leaving the home space
                	{
                        	arr[xAv][yAv - 1].tile = HOME;
                        	arr[xAv][yAv - 1].isHomeEmpty = false;
                	}
                }
        }
        return isMoved;
}

bool left(Background** arr, int size, int& xAv, int& yAv)
{
        bool isMoved = false;
        if(arr[xAv - 1][yAv].tile == SPACE)
        {
                cout << endl << "You moved left." << endl;
                arr[xAv][yAv].tile = SPACE;
                xAv = xAv - 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

		cout << "The isHomeEmpty value is " << arr[xAv][yAv].isHomeEmpty << endl;
		if(arr[xAv + 1][yAv].isHomeEmpty == true)
		{
      			arr[xAv + 1][yAv].tile = HOME;
    			arr[xAv + 1][yAv].isHomeEmpty = false;
    		}
        }
        else if(arr[xAv - 1][yAv].tile == HOME)
        {
                cout << endl << "You moved to the home space." << endl;
                arr[xAv][yAv].tile = SPACE;
                xAv = xAv - 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

                arr[xAv][yAv].isHomeEmpty = true;
                cout << arr[xAv][yAv].isHomeEmpty << endl;
        }
        else if(arr[xAv - 1][yAv].tile == WALL)
        {
                cout << endl << "There is a wall so it is invalid. " << endl;
        }
	else if(arr[xAv - 1][yAv].tile == COMPLETE)
        {
                cout << endl << "You cannot move the box once it is home" << endl;
        }
        else if(arr[xAv - 1][yAv].tile == BOX)
        {
                if(arr[xAv - 2][yAv].tile == BOX)
                {
                        cout << endl << "There are 2 boxes in a row, you can not move." << endl;
                }
                else if(arr[xAv - 2][yAv].tile == WALL)
                {
                        cout << endl << "You cannot push the box into the wall." << endl;
                }
                else if(arr[xAv - 2][yAv].tile == HOME)
                {
                        cout << endl << "You got a box home." << endl;
                        arr[xAv - 2][yAv].tile = COMPLETE;

                        arr[xAv][yAv].tile = SPACE;
                        xAv = xAv - 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;
                }
		else if(arr[xAv - 2][yAv].tile == SPACE)
                {
                        cout << endl << "You pushed the box one space." << endl;
                        arr[xAv - 2][yAv].tile = BOX;

                        arr[xAv][yAv].tile = SPACE;
                        xAv = xAv - 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;

			if(arr[xAv + 1][yAv].isHomeEmpty == true)
                	{
                        	arr[xAv + 1][yAv].tile = HOME;
                        	arr[xAv + 1][yAv].isHomeEmpty = false;
                	}
                }
        }
        return isMoved;
}

bool right(Background** arr, int size, int& xAv, int& yAv)
{
        bool isMoved = false;
        if(arr[xAv + 1][yAv].tile == SPACE)
        {
                cout << endl << "You moved right." << endl;
                arr[xAv][yAv].tile = SPACE;
                xAv = xAv + 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

		if(arr[xAv - 1][yAv].isHomeEmpty == true) //this is when leaving the home space
                {
                        arr[xAv - 1][yAv].tile = HOME;
                        arr[xAv - 1][yAv].isHomeEmpty = false;
                }
        }
	else if(arr[xAv + 1][yAv].tile == HOME) //this is for when the home space is landed on
        {
                cout << endl << "You moved to the home space." << endl;
                arr[xAv][yAv].tile = SPACE;
                xAv = xAv + 1;
                arr[xAv][yAv].tile = AVATAR;
                isMoved = true;

                arr[xAv][yAv].isHomeEmpty = true;
                cout << arr[xAv][yAv].isHomeEmpty << endl;
        }
        else if(arr[xAv + 1][yAv].tile == WALL)
        {
                cout << endl << "There is a wall so it is invalid. " << endl;
        }
        else if(arr[xAv + 1][yAv].tile == COMPLETE)
        {
                cout << endl << "You cannot move the box once it is home" << endl;
        }
        else if(arr[xAv + 1][yAv].tile == BOX)
        {
                if(arr[xAv + 2][yAv].tile == BOX)
                {
                        cout << endl << "There are 2 boxes in a row, you can not move." << endl;
                }
                else if(arr[xAv + 2][yAv].tile == WALL)
                {
                        cout << endl << "You cannot push the box into the wall." << endl;
                }
		else if(arr[xAv + 2][yAv].tile == HOME)
                {
                        cout << endl << "You got a box home." << endl;
                        arr[xAv + 2][yAv].tile = COMPLETE;

                        arr[xAv][yAv].tile = SPACE;
                        xAv = xAv + 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;
                }
                else if(arr[xAv + 2][yAv].tile == SPACE)
                {
                        cout << endl << "You pushed the box one space." << endl;
                        arr[xAv + 2][yAv].tile = BOX;

                        arr[xAv][yAv].tile = SPACE;
                        xAv = xAv + 1;
                        arr[xAv][yAv].tile = AVATAR;
                        isMoved = true;

			if(arr[xAv - 1][yAv].isHomeEmpty == true) //this is when leaving the home space
                	{
                        	arr[xAv - 1][yAv].tile = HOME;
                        	arr[xAv - 1][yAv].isHomeEmpty = false;
                	}
                }
        }
        return isMoved;
}
