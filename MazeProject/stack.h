/*************************************************************************
Header File Name: Stack.h
Des:  This file will contain the stucture and methods for the class
	  Stack which is a Stack implemented as a dynamically allocated
	  single linked-list.
Author: Jair Lopez

*************************************************************************/

//Used to store a coordinate in the maze [Row][Column]
struct Coordinate
{
	int Row, Column;
};


//Define a node in a single linked-list. Each node will store a coordinate and a 
//pointer to the next node in the list
struct Node
{
	Coordinate currentCoordinate;
	Node* Next;
};


class Stack
{

	public:
		//Constuct a Stack object
		Stack();

		//Destroy a Stack object
		~Stack();

		//Check if stack is empty
		bool Empty();

		//Place elements on the top of the stack
		bool Push(Coordinate);

		//Remove element off the top of the stack
		bool Pop(Coordinate&);

		//No full function is provided since it is dependent on
		//memory allocation and push will check for that.

	private:
		//A pointer to the first node in the Stak. If the list is empty, Top should be
		//NULL. This private data member can be alerted by Push and Pop functions 
		Node* Top;
};
