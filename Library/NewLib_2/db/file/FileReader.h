#ifndef DBFILEREADER_H
#define DBFILEREADER_H
#define UNIT_BUFFER_SIZE 256

#include "FileUnit.h"
#include <fstream>
#include <string>
using namespace std;
class FileReader
{
public:
	
	//string=database file name
	FileReader(string);
	
	//read data in the [index] point block;
	Unit * read(int);	// ---change

	//write data to the [index] point block,and should be written immediately;
	int write(Unit&,int);
	bool close();
private:
	string fileName;
	Unit *units[UNIT_BUFFER_SIZE];	//2^8	
	fstream fileRW;
};

#endif

