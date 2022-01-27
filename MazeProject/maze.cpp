/*************************************************************************
Program Name: maze.cpp
Des: This program allows a person to read mazes with their respective 
	 dimensions, and coordinates in order to go though all the possible
	 moves and determine whether the maze can be solved or not.
	 This program uses the help of the Stack class to implement the solution.
	 The stack object pushes all the possible moves and when they become the 
	 current coordinate they are poped from the stack. So when the program 
	 goes through all the maze and finds a way out, the stack should be empty
	 to prove that the maze is solvable.


Author: Jair Lopez
Due Date: 11/10/19
*************************************************************************/

#include <fstream>
#include <iostream>
#include<vld.h> 

//contains List class definition which will be needed to provide a solution
#include "stack.h"

using namespace std;


/*************************************************************************
GLOBAL DECLARATIONS
*************************************************************************/
const short int MAXROWS = 80;
const short int MAXCOLUMNS = 80;
  
/*************************************************************************
Function Name: PrintSolvedMazes
Des: This function is responsible for printing the output into a text 
	 file called mazeSolutions.txt. After printing out with fstream, 
	 mazeSolutions.txt should have the presentation of the program the
	 author, and all the maze solved indicating if they could be solved 
	 or not. The maze should now be printed with the breadcrumbs that 
	 the program introduced in each move that was 
*************************************************************************/
void printSolvedMazes(int col, int row, int mazeCount, char maze[][MAXCOLUMNS], bool wasSolved, ofstream& fout)
{
	fout << "MAZE NUMBER " << mazeCount << endl << endl;
	for (int rIndex = 0; rIndex < row; rIndex++)
	{
		for (int cIndex = 0; cIndex < col; cIndex++)
		{
			fout << maze[rIndex][cIndex];
		}
		fout << endl;
	}

	if(wasSolved)
		fout << "\nThere IS a way out\n" << endl;
	else
		fout << "\nThere IS NOT a way out\n" << endl;

}

/*************************************************************************
Function Name: saveMove
Des: This function is responsible for checking the possible moves from the 
	 current position. It checks the four cardinal directions and push onto
	 the move stack any available move. It checks the possibility of the move
	 by looking for '0' or 'E'. If there is a available move, the program 
	 creates a temporary variable that is pushed into the move stack.
	 If the pushing cannot be done, an error message will be displayed.
*************************************************************************/
void saveMove(Coordinate& currentCoordinate, char maze[][MAXCOLUMNS], Stack& moveStack)
{

	//check the four cardinal directions and push onto the move stack any available moves from
	//the current coordinate
	
	//don't go out of bounds to the north
	if (maze[currentCoordinate.Row - 1] >= 0)
	{
		//check if north coordinate is either a '0' or 'E'; an available move
		if (maze[currentCoordinate.Row - 1][currentCoordinate.Column] == '0' ||
			maze[currentCoordinate.Row - 1][currentCoordinate.Column] == 'E')
		{
			//create a temporary north Coordinate variable and push it onto the move stack
			//adjust row in north variable so it is north from where we are currently
			Coordinate northCoordinate = currentCoordinate;
			northCoordinate.Row--;
			if (!moveStack.Push(northCoordinate))
			{
				//push didn't work, memory allocation error...exit program
				cerr << "C++ memory allocation error…program exiting" << endl;
				exit(EXIT_FAILURE);
			}		
		}
	}

	//don't go out of bounds to the south
	if (maze[currentCoordinate.Row + 1] >= 0)
	{
		//check if north coordinate is either a '0' or 'E'; an available move
		if (maze[currentCoordinate.Row + 1][currentCoordinate.Column] == '0' ||
			maze[currentCoordinate.Row + 1][currentCoordinate.Column] == 'E')
		{
			//create a temporary north Coordinate variable and push it onto the move stack
			//adjust row in south variable so it is south from where we are currently
			Coordinate southCoordinate = currentCoordinate;
			southCoordinate.Row++;
			if (!moveStack.Push(southCoordinate))
			{
				//push didn't work, memory allocation error...exit program
				cerr << "C++ memory allocation error…program exiting" << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	//don't go out of bounds to the east
	if (maze[currentCoordinate.Column + 1] >= 0)
	{
		//check if north coordinate is either a '0' or 'E'; an available move
		if (maze[currentCoordinate.Row][currentCoordinate.Column + 1] == '0' ||
			maze[currentCoordinate.Row][currentCoordinate.Column + 1] == 'E')
		{
			//create a temporary east Coordinate variable and push it onto the move stack
			//adjust row in east variable so it is east from where we are currently
			Coordinate eastCoordinate = currentCoordinate;
			eastCoordinate.Column++;
			if (!moveStack.Push(eastCoordinate))
			{
				//push didn't work, memory allocation error...exit program
				cerr << "C++ memory allocation error…program exiting" << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	//don't go out of bounds to the west
	if (maze[currentCoordinate.Column - 1] >= 0)
	{
		//check if north coordinate is either a '0' or 'E'; an available move
		if (maze[currentCoordinate.Row][currentCoordinate.Column - 1] == '0' ||
			maze[currentCoordinate.Row][currentCoordinate.Column - 1] == 'E')
		{
			//create a temporary west Coordinate variable and push it onto the move stack
			//adjust row in west variable so it is west from where we are currently
			Coordinate westCoordinate = currentCoordinate;
			westCoordinate.Column--;
			if (!moveStack.Push(westCoordinate))
			{
				//push didn't work, memory allocation error...exit program
				cerr << "C++ memory allocation error…program exiting" << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

}

/*************************************************************************
MAIN PROGRAM
*************************************************************************/
int main()
{
	char maze[MAXROWS][MAXCOLUMNS];
	int row, col, rIndex, cIndex;
	int mazeCount = 0;
	bool wasSolved = false;
	Stack moveStack;
	Coordinate currentCoordinate;
	ifstream fin("maze.txt");
	
	//Create text file to print solutions
	ofstream fout;
	fout.open("mazeSolutions.txt");
	fout << "Solutions to A-MAZE-ING Stacks Assignment" << endl;
	fout << "By: Jair Lopez" << endl;
	fout << endl;

	//Read maze dimensions
	fin >> row >> col;

	//Read coordinates and solve mazes until input is equal to "-1 -1"
	while (row != -1 && col != -1)
	{
		//Count how many mazes are we evaluating
		mazeCount++;

		//read maze into twoD array
		for (rIndex = 0; rIndex < row; rIndex++)
		{
			for (cIndex = 0; cIndex < col; cIndex++)
			{
				fin >> maze[rIndex][cIndex];
			}
		}

		//read current starting location in the maze
		fin >> currentCoordinate.Row >> currentCoordinate.Column;

		//Check possible moves until current coordinate is the exit
		while (maze[currentCoordinate.Row][currentCoordinate.Column] != 'E')
		{
			saveMove(currentCoordinate, maze, moveStack);

			//Drop a breadcrumb
			maze[currentCoordinate.Row][currentCoordinate.Column] = '.';
			
			//Determine if maze has a solution or not
			if (!moveStack.Pop(currentCoordinate))
			{
				wasSolved = false;
				break;
			}
			else
				wasSolved = true;
		}

		//Print out solutions into textfile
		printSolvedMazes(col, row, mazeCount, maze, wasSolved, fout);


		//Read dimensions of next maze
		fin >> row >> col;

	}
	
	fout.close();
	fin.close();
	

	return 0;
}