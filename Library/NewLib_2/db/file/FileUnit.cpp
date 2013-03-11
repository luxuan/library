#include "stdafx.h"
#include "FileUnit.h"
#include <string>
#include <iostream>
using namespace std;
Unit::Unit(int page)
{
	this->page=page;	
	for(int i=0;i<UNIT_SIZE;i++)
	{
		this->buffer[i]=0;
	}
	this->offset=0;
}

string Unit::getString(int count)
{
	// -->
	string value="";
	for(int i=0;i<count;i++)
	{
	    if(this->buffer[i+this->offset]==0)break;
		value=value+this->buffer[i+this->offset];
	}
	this->offset=this->offset+count;
	return value;
}

bool Unit::writeString(string value,int length)
{
	// -->	
	int i;
    int min;
    if(length<value.length())
    {
        min=length;
    }
    else
    {
        min=value.length();
    }
	for(i=0;i<min;i++)
	{
		this->buffer[i+this->offset]=value[i];
	}
	if(min<length)
	{
		this->buffer[i+this->offset]=0;
	}
    this->offset=this->offset+length;
	return true;
}

bool Unit::seekg(int value)
{
	this->offset=value;
	return true;
}
int Unit::tellg()
{
	return this->offset;
}

bool Unit::setBuffer(char * p)
{
	for(int i=0;i<UNIT_SIZE;i++)
	{
		this->buffer[i]=p[i];		
	}
	return true;
}