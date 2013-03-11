#ifndef DBFILEUNIT_H
#define DBFILEUNIT_H

#include <string>
using namespace std;
#define UNIT_SIZE 65536			//64KB
class Unit
{

public :
	Unit(int);

	template <class type>
	bool get(type *value)	
	{
		char *a=reinterpret_cast<char *> (value);
		for(int i=0;i<(sizeof(type)/sizeof(char));i++)
		{
			*(a+i)=this->buffer[this->offset+i];
		}
		value=reinterpret_cast<type *> (a);		
		this->offset=this->offset+sizeof(type);
		return true;
	}

	string getString(int);
	
	template <class type>
	bool write(type value)		
	{
		char *a=reinterpret_cast<char *> (&value);	
		for(int i=0;i<(sizeof(type)/sizeof(char));i++)
		{
			this->buffer[this->offset+i]=*(a+i);
		}
		this->offset=this->offset+sizeof(type);
		return true;
	}	

	bool writeString(string,int);

	bool seekg(int);
	int tellg();
	
	bool setBuffer(char * p);
	char buffer[UNIT_SIZE];
private :
	int offset;
	int page;
	
};


#endif