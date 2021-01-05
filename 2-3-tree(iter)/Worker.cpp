#include "Worker.h"

//copy constructor
Lior_Worker::Lior_Worker(const Lior_Worker& otherWorker) throw(char*)
{
	if (otherWorker.name != NULL)
	{
		name = new Lior_StringKey(*otherWorker.name);
		years = otherWorker.years;
		position = otherWorker.position;
	}
	else
	{
		throw "allocation error!";
	}
}



unsigned int Lior_Worker::getseniority()
{
	return this->years;
}

unsigned int Lior_Worker::getPosition()
{
	return this->position;
}

Lior_StringKey* Lior_Worker::GetKey()const
{
	return name;
}

//input ffrom user, reeturn null if error occured
Lior_Worker* Lior_Worker::Read(ifstream& inputFile)
{
	Lior_StringKey* tempSKey;
	Lior_Worker* outWorker;

	try
	{
		tempSKey = Lior_StringKey::Read(inputFile);
	}
	catch (...)
	{
		return NULL;
	}
	if (!tempSKey)
	{
		return NULL;
	}

	outWorker = new Lior_Worker;

	outWorker->name = tempSKey;
	try
	{
		if (!(inputFile >> outWorker->years >> outWorker->position))
		{
			delete outWorker;

			return NULL;
		}
	}
	catch (...)
	{
		delete outWorker;

		return NULL;
	}
	return outWorker;
}