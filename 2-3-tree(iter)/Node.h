#ifndef _NODE_H_
#define _NODE_H_

#include "Worker.h"

class Lior_Node
{

protected:

	Lior_Node* parent;
	int isleaf;

public:
	// Constructors
	Lior_Node()
	{
	}

	// Destructor
	virtual ~Lior_Node()
	{
	}

	int IsLeaf(); // suppose the node is a leaf return true.  false otherwise.

	//perents methods
	void SetParent(Lior_Node* p);
	Lior_Node* getParent();
};

#endif