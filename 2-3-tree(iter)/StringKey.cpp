#include "StringKey.h"

string Lior_StringKey::getString()const // Return str
{
	return strK;
}

// alphabetical Compare between 2 strings 
int Lior_StringKey::Compare(const Lior_StringKey* s)const
{
	return (strK.compare(s->strK));
}

unsigned Lior_StringKey::Hash()
{
	unsigned long i = 0;
	unsigned long length = strK.length();

	unsigned int p = 128;
	unsigned int x = (unsigned int)pow(2.0, 32) - 1; // range (2^32)-1 = 4294967295 

	unsigned int k = 0;
	unsigned int currChar;
	for (i = 0; i < length; i++) // loop over the whole string
	{
		currChar = unsigned int(strK[i]); // transform the char to unsigned int
		k = Add(k, Mult(currChar, (unsigned int)pow(p, (length - i - 1.0)), x), x);
	}

	return k;
}

// Read from file
Lior_StringKey* Lior_StringKey::Read(ifstream& inputFile)
{
	string inKey;
	Lior_StringKey* outKey = NULL;

	if (inputFile >> inKey)
	{
		outKey = new Lior_StringKey(inKey);

		return outKey;
	}

	return NULL;
}

unsigned Lior_StringKey::Mult(unsigned a, unsigned p, unsigned x)// a,p < x, p is a power of 2 (like 128)
{
	unsigned uAdd = Add(a, a, x);
	if (p == 1)
	{
		return a;
	}
	return (Mult(uAdd, p / 2, x)); // recursive
}

unsigned Lior_StringKey::Add(unsigned a, unsigned b, unsigned x) //  a,b < x
{
	if (a >= x - b)
	{
		return (b - (x - a)); //avoid overflow
	}
	else
	{
		return (a + b);
	}
}
