#ifndef _STRING_KEY_H_
#define _STRING_KEY_H_


#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

//#pragma warning(disable: 4290)

using namespace std;

class Lior_StringKey
{
private:
	string strK;
	unsigned Mult(unsigned a, unsigned p, unsigned x); // For hash function (without overflow)
	unsigned Add(unsigned a, unsigned b, unsigned x); // For hash function (without overflow)

public:
	Lior_StringKey() {}// Empty constructor
	Lior_StringKey(const Lior_StringKey& otherStringKey) // Copy constructor
	{
		strK = otherStringKey.strK;
	}

	// Constructor that gets a string
	Lior_StringKey(const string& strString)
	{
		strK = strString;
	}

	~Lior_StringKey() {} // Destructor


	unsigned Hash();

	//alphabetical Compare between 2 strings
	int Compare(const Lior_StringKey* s)const;
	string getString()const; // Return str

	// Read stringKey from a file. null if there was an error in reading
	static Lior_StringKey* Read(ifstream& inputFile);

};
#endif