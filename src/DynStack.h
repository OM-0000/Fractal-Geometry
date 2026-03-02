// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include "Node.h"
class DynStack
{
private:

	Node* top; //points to the top element of the stack, or NULL if the stack is empty
	int count;
public:
	DynStack() //constructor sets top to null
	{
		top = nullptr;
		count = 0;
	}
	~DynStack(); // destructor prototype. will delete pointers, freeing up memory allocated by list
	//Stack operations
	bool push(void*);
	bool pop(void**);
	bool isEmpty() const;
	Node* traverse(Node* last) const;
	int getSize() const;
};


