#include "Node.h"

int Lior_Node::IsLeaf()
{
	return isleaf;
}

void Lior_Node::SetParent(Lior_Node* p)
{
	parent = p;
}

Lior_Node* Lior_Node::getParent()
{
	return parent;
}