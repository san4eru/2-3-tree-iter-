/*
read before using:
open the program with an argument that represents a txt file
the file shell be located at the same folder as of the project
*/



#ifndef _MAIN_H_
#define _MAIN_H_

#include <fstream>
#include <sstream>
#include "Dictionary.h"

using namespace std;

bool ConvertStringToInt(const string& s, unsigned int& num);

int main(int argc, char* argv[])
{
	
	string outputFile;
	char* pNameOfFile;
	cin >> pNameOfFile;
	outputFile.insert(0, pNameOfFile);

	char* newNameFile;

	string strnewExtension = "Res.txt";
	int nbeginExtension = outputFile.find(".txt");
	outputFile.replace(nbeginExtension, nbeginExtension + 4, strnewExtension);

	newNameFile = new char[outputFile.size() + 1];
	strcpy(newNameFile, outputFile.c_str());
	ifstream ifs; // input file
	ifs.open(pNameOfFile);
	string nextString;
	ofstream ofs; // output file
	ofs.open(outputFile.c_str());


	Lior_Dictionary* d = new Lior_Dictionary();

	unsigned int N;

	while (ifs >> nextString)
	{
		if (nextString == "PrintDictionary")
		{
			d->PrintDictionary(ofs);
		}
		else if (nextString == "FreeAllElements")
		{
			d->FreeAllElements();
		}
		else if (ConvertStringToInt(nextString, N))
		{
			int success;
			unsigned int i;

			for (i = 0; i < N; i++)
			{
				try
				{
					Lior_Worker* currentWorker = Lior_Worker::Read(ifs);

					if (currentWorker != NULL)
					{
						success = d->Insert(currentWorker->GetKey(), currentWorker);

						if (!success)
						{
							delete currentWorker;
						}
					}
					else // error - the input is invalid , commit exit
					{
						cout << "Invalid input file!" << endl;

						ifs.close();
						ofs.close();
						d->FreeAllElements();
						delete d;
						exit(1);
					}
				}
				catch (char* message)
				{
					cout << message << endl;
				}
			}

			break;
		}
		else
		{
			ifs.close();
			ofs.close();
			d->FreeAllElements();
			delete d;

			exit(1); // Invalid input. Exit with error
		}
	}

	//  deletion ,print ,freeElements

	unsigned int M;
	while (ifs >> nextString)
	{
		if (nextString == "PrintDictionary")
		{
			d->PrintDictionary(ofs);
		}
		else if (nextString == "FreeAllElements")
		{
			d->FreeAllElements();
		}
		else if (ConvertStringToInt(nextString, M))
		{
			string name;

			unsigned int i;
			for (i = 0; i < M; i++)
			{
				if (ifs >> name)
				{
					Lior_StringKey* sName = new Lior_StringKey(name);

					Lior_Worker* currentWorker = d->Delete(sName);

					delete currentWorker; // delete worker
					delete sName; //  search only

				}
			}

			break;
		}
		else
		{
			ifs.close();
			ofs.close();
			d->FreeAllElements();
			delete d;

			exit(1); // Invalid input. Exit with error
		}
	}

	// Now print or freeElements

	while (ifs >> nextString)
	{
		if (nextString == "PrintDictionary")
		{
			d->PrintDictionary(ofs);
		}
		else if (nextString == "FreeAllElements")
		{
			d->FreeAllElements();
		}
		else
		{
			ifs.close();
			ofs.close();
			d->FreeAllElements();
			delete d;

			exit(1); // Invalid input. Exit with error
		}
	}

	// Close all file streams
	ifs.close();
	ofs.close();

	// If not specified by the user in the file, Free memory of data 
	d->FreeAllElements();
	delete d; // delete dictionary

	return 0; // success
}

bool ConvertStringToInt(const string& s, unsigned int& num)
{
	istringstream myStream(s);

	if (myStream >> num) // did insert into unsigned int succeeded
		return true;
	else
		return false;
}

#endif