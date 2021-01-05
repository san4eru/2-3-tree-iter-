#ifndef _TRANS_H_
#define _TRANS_H_

#include "Node.h"
#include "InteriorNode.h"

class Lior_TransitoryNode :
	public Lior_InteriorNode
{
private:
	// minimum of "biggest"
	Lior_StringKey* min4;
	// Forth child which is bigger than his "Right Child"
	Lior_Node* biggest;

public:

	//constructor
	Lior_TransitoryNode() :biggest(NULL), min4(NULL)
	{
	};

	//Destructor
	~Lior_TransitoryNode(void)
	{
	};

	//gets and sets
	void setMin4(Lior_StringKey* min); // sets min4
	void setBiggest(Lior_Node* node); // sets the biggest child


	Lior_StringKey* getMin4(); // gets min4
	Lior_Node* getBiggest(); // returns biggest 
};

#endif