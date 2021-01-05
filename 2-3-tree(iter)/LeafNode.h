#ifndef _LEAF_H_
#define _LEAF_H_

#include "Node.h"
class Lior_LeafNode :
	public Lior_Node
{
private:
	Lior_Worker* worker;
	Lior_StringKey* key;

public:
	// constructors
	Lior_LeafNode()
	{
		isleaf = true;
	}

	Lior_LeafNode(Lior_StringKey* k, Lior_Worker* d);

	Lior_Worker* Data()const; // Returns  current node data
	Lior_StringKey* Key()const; // Returns current node key

	~Lior_LeafNode(void)
	{
	} // Destructor

};

#endif