#include "LeafNode.h"

Lior_LeafNode::Lior_LeafNode(Lior_StringKey* k, Lior_Worker* d)
{
	key = d->GetKey();
	worker = d;

	isleaf = true;
}

Lior_Worker* Lior_LeafNode::Data()const
{
	return worker;
}

Lior_StringKey* Lior_LeafNode::Key()const //return the key of current node (Name)
{
	return worker->GetKey();
}