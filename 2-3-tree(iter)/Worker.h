#ifndef _WORKER_H_
#define _WORKER_H_

#include "StringKey.h"

class Lior_Worker
{
private:
	Lior_StringKey* name;
	unsigned int years;
	unsigned int position;
public:
	// Constructor
	Lior_Worker() :name(0), years(0), position(0) {}

	Lior_Worker(Lior_StringKey* name, unsigned int years, unsigned int position) :name(name), years(years), position(position) {}

	//destructor
	~Lior_Worker()
	{
		delete name;
	}

	Lior_Worker(const Lior_Worker& otherWorker)throw(char*); // Copy constructor. Throws exception if other worker's name is null

	// Returns the key (the name of the worker)
	Lior_StringKey* GetKey()const;

	//read input worker from the file. null if there was an error reading
	static Lior_Worker* Read(ifstream& inputFile);

	//operator << for output
	friend ostream& operator<<(ostream& out, const Lior_Worker& worker)
	{
		out << worker.name->getString() << "\t " << worker.years
			<< "\t " << worker.position;
		return out;
	}


	unsigned int getseniority(); // Returns the years
	unsigned int getPosition(); // Returns the position
};

#endif