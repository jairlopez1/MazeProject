#include <iostream>
#include "stack.h"
using namespace std;

/***************************************************************************************
Function Name: List (constructor)
Des: This constructor will create a Stack object.
****************************************************************************************/
Stack::Stack()
{
	Top = NULL;
}

/***************************************************************************************
Function Name: ~List (destructor)
Des: This function will destroy a Stack object.
***************************************************************************************/
Stack::~Stack()
{
	Node* temp = Top;
	Node* Next;

	while (temp != NULL)
	{
		Next = temp->Next;
		delete temp;
		temp = Next;
	}
}

/***************************************************************************************
Function Name: Push
Des: This function creates a new node and introduce it at the top of the stack. The node
	 will contain the current coordinate into its info field. If the stack is empty the 
	 new node will be pointed by Top. If there are already other elements into the stack,
	 The new node will be inserted at the front and pointed by Top.
***************************************************************************************/
bool Stack::Push(Coordinate info) 
{
	Node* new_node = new Node;
	if (new_node == nullptr) return false;

	new_node->currentCoordinate = info;
	new_node->Next = nullptr;

	if (Empty()) {
		Top = new_node;
	}
	else {
		new_node->Next = Top;
		Top = new_node;
	}
	return true;
}

/***************************************************************************************
Function Name: Pop
Des:This function evaluates wheter the stack can be poped or not. If the stack is empty,
	 it return false. If it has elements, a Coordinate variable passed by reference is
	 in charge of save the information on the Top of the stack and return it. After saving
	 the content of top, we delete the top node and we make Top point to the successive element.
***************************************************************************************/
bool Stack::Pop(Coordinate& info) 
{
	if (Empty()) return false;
	info = Top->currentCoordinate;

	Node* del_node = Top;
	Top = Top->Next;
	delete del_node;
	return true;
}

/***************************************************************************************
Function Name: Empty
Des: This function returns true or false by evaluating if the content in the top element 
	 of the stack is equal to null or if it has some content 
***************************************************************************************/
bool Stack::Empty() 
{
	return (Top == NULL);
}