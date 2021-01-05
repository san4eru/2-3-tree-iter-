#ifndef _INTERIOR_H_
#define _INTERIOR_H_

#include "Node.h"
class Lior_InteriorNode :

	public Lior_Node
{
protected:
	Lior_StringKey* min1, * min2, * min3;
	Lior_Node* left, * mid, * right;

public:
	// Empty Constructor
	Lior_InteriorNode() :left(NULL), mid(NULL), right(NULL), min1(NULL), min2(NULL), min3(NULL)
	{
		SetParent(NULL);
		isleaf = false;
	}
	// Constructor
	Lior_InteriorNode(Lior_Node* l, Lior_Node* m, Lior_Node* r, Lior_StringKey* imin1, Lior_StringKey* imin2, Lior_StringKey* imin3);
	virtual ~Lior_InteriorNode(void)
	{
		delete left;
		delete mid;
		delete right;
	}

	//sets and gets
	void setMin1(Lior_StringKey* min);
	Lior_StringKey* getMin1();
	void setMin2(Lior_StringKey* min);
	Lior_StringKey* getMin2();
	void setMin3(Lior_StringKey* min);
	Lior_StringKey* getMin3();

	void setLeft(Lior_Node* node);
	Lior_Node* getLeft();
	void setMid(Lior_Node* node);
	Lior_Node* getMid();
	void setRight(Lior_Node* node);
	Lior_Node* getRight();

};

#endif