#include "stdafx.h"
#include "FileReader.h"
#include <iostream>
#include <fstream>
using namespace std;

FileReader::FileReader(string fileName)
{
	this->fileName=fileName;
	this->fileRW.open(fileName.data(),ios::in|ios::out|ios::ate|ios::binary);
	this->fileRW.seekg(0,ios::beg);
	this->fileRW.seekp(0,ios::beg);
	//cout<<"FileReader.fileName="<<fileName<<endl;
}
	
Unit* FileReader::read(int index)
{
	//init unit
	//cout<<"FileReader "<<index<<endl;
	char buffer[UNIT_SIZE];
	Unit *unit;
	unit=new Unit(index);
	fileRW.seekg(index*UNIT_SIZE*sizeof(char),ios::beg);
	fileRW.seekp(index*UNIT_SIZE*sizeof(char),ios::beg);
	fileRW.read(reinterpret_cast<char *>(&buffer),UNIT_SIZE*sizeof(char));
	(*unit).setBuffer(buffer);	
	return unit;
}


int FileReader::write(Unit& unit,int index)
{
	// write to file,index to the next page;
	fileRW.seekp(index*UNIT_SIZE*sizeof(char),ios::beg);
	fileRW.seekg(index*UNIT_SIZE*sizeof(char),ios::beg);
	fileRW.write(reinterpret_cast<char *>(&(unit.buffer)),UNIT_SIZE*sizeof(char));
	
	return ++index;
}
bool FileReader::close()
{
	this->fileRW.close();
	return true;
}