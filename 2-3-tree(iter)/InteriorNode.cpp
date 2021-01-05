#include "InteriorNode.h"

Lior_InteriorNode::Lior_InteriorNode(Lior_Node* l, Lior_Node* m, Lior_Node* r, Lior_StringKey* imin1, Lior_StringKey* imin2, Lior_StringKey* imin3)
{
	min1 = imin1;
	min2 = imin2;
	min3 = imin3;
	left = l;
	mid = m;
	right = r;

	//setting perents
	right->SetParent(this);
	left->SetParent(this);
	mid->SetParent(this);

	isleaf = false;
}

void Lior_InteriorNode::setRight(Lior_Node* node)
{
	right = node;

	if (node != NULL)
		node->SetParent(this);
}

void Lior_InteriorNode::setMid(Lior_Node* node)
{
	mid = node;

	if (node != NULL)
		node->SetParent(this);
}

void Lior_InteriorNode::setLeft(Lior_Node* node)
{
	left = node;

	if (node != NULL)
		node->SetParent(this);
}

Lior_Node* Lior_InteriorNode::getMid()
{
	return mid;
}

Lior_Node* Lior_InteriorNode::getRight()
{
	return right;
}



Lior_Node* Lior_InteriorNode::getLeft()
{
	return left;
}

void Lior_InteriorNode::setMin1(Lior_StringKey* min)
{
	min1 = min;
}

void Lior_InteriorNode::setMin2(Lior_StringKey* min)
{
	min2 = min;
}

void Lior_InteriorNode::setMin3(Lior_StringKey* min)
{
	min3 = min;
}

Lior_StringKey* Lior_InteriorNode::getMin1()
{
	return min1;
}

Lior_StringKey* Lior_InteriorNode::getMin2()
{
	return min2;
}


Lior_StringKey* Lior_InteriorNode::getMin3()
{
	return min3;
}