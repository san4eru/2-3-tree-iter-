#include "TransitoryNode.h"

//sets

void Lior_TransitoryNode::setMin4(Lior_StringKey* min)
{
	min4 = min;
}

void Lior_TransitoryNode::setBiggest(Lior_Node* node)
{
	biggest = node;

	if (node != NULL)
		node->SetParent(this);
}

//gets

Lior_StringKey* Lior_TransitoryNode::getMin4()
{
	return min4;
}

Lior_Node* Lior_TransitoryNode::getBiggest()
{
	return biggest;
}


