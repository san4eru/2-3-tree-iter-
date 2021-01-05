#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <fstream>
#include "Node.h"
#include "InteriorNode.h"
#include "LeafNode.h"
#include "TransitoryNode.h"

using namespace std;

class Lior_Dictionary
{
private:
	Lior_Node* root;

	void AddChild(Lior_TransitoryNode* trans); // adds a 4 node to the dictionary and splits it so it's valid
	Lior_TransitoryNode* MakeTransitoryNode(Lior_InteriorNode* parent, Lior_LeafNode* child); // creates a temp 4 node

	void freeAllElementsHelper(Lior_Node* node); // frees all elements recursively
	void Update(Lior_InteriorNode* node); // updates a node's min1, min2, min3 till the root

	Lior_InteriorNode* FindParent(Lior_StringKey* key); // finds a node's parent

	void print23(ofstream& outputFile, Lior_Node* node); // prints recursively in the right order

public:
	//constructor
	Lior_Dictionary() :root(0)
	{
	}

	//destructor
	~Lior_Dictionary()
	{
		//  delete left, mid and right nodes recursivaly
		delete root;
	}

	// Inserts a worker
	int Insert(Lior_StringKey* k, Lior_Worker* d);

	// Deletes a worker by name
	Lior_Worker* Delete(Lior_StringKey* k);

	// Finds a worker by name
	Lior_Worker* Find(Lior_StringKey* k);

	// Frees all elements in the dictionary
	void FreeAllElements();
	// Prints the dictionary in alphabetical order

	void PrintDictionary(ofstream& outputFile);

	int IsEmpty();// Check if the dictionary is empty, if empty return 1(true), else return 0 (false)

};

#endif