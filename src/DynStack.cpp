// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "DynStack.h"
DynStack::~DynStack()
{
	//Destructor. Frees up space allocated by DynStack.
	void* temp = nullptr;
	while (pop(&temp))
	{

	}
}
//Stack operations
bool DynStack::push(void* pData)
{
	Node* n = new Node;
	n->pData = pData;
	n->next = nullptr;
	if (isEmpty())
	{
		top = n;
	}
	else
	{
		n->next = top;
		top = n;
	}
	++count;
	return true; //Always returns true because it's assumed there would be no errors; but, in the future, having the function like this would allow for error handling.
}
bool DynStack::pop(void** pData)
{
	Node* temp;
	if (isEmpty())
	{
		return false; //indicates that the stack was empty, the operation did not complete
	}
	else
	{
		*pData = top->pData; // stores value in "pData"
		temp = top;
		top = top->next;
		delete temp;
		--count;
		return true; // indicates successful completion of operation
	}
}
bool DynStack::isEmpty() const
{
	return top == nullptr;
}
Node* DynStack::traverse(Node* last) const
{
	//Pass in nullptr to start from the top
	//IF this function returns nullptr, the bottom has been reached
	//This function will not change any data
	Node* curr;
	if (last == nullptr)
	{
		curr = top;
	}
	else
	{
		curr = last->next;
	}
	return curr;
}
int DynStack::getSize() const
{
	return count;
}