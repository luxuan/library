#include "stdafx.h"
#include "CategoryManager.h"

#include <iostream>
using namespace std;



// string=file name
CategoryManager::CategoryManager(string filename):reader(filename)
{
    categorySize=(sizeof(char)*(32));
    categorySize+=sizeof(int);
    this->read(0);
}
CategoryManager::~CategoryManager()
{
    this->flush();
    reader.close();
}
int CategoryManager::getCategoryCount()
{
	return this->categoryList.size();
}

string CategoryManager::getName(int id)
{
    string rName("");
    list<Category>::iterator iter;
	for(iter=categoryList.begin();iter!=categoryList.end();iter++)
	{
	    //cout<<" name= "<<iter->name<<endl;
	    if(id==(*iter).id)
	    {
	       rName=(*iter).name;
	       break; 
	    }
	}
	return rName;
}
int CategoryManager::getId(string name)
{
    int rId=-1;
    list<Category>::iterator iter;
	for(iter=categoryList.begin();iter!=categoryList.end();iter++)
	{
	    if(name.compare((*iter).name)==0)
	    {
	       rId=(*iter).id; 
	       break;
	    }
	}
	return rId;
}



bool CategoryManager::insert(const Category &category)
{
	list<Category>::iterator p;
	for(p=categoryList.begin();p!=categoryList.end();p++)
	{
	    if(category.id==p->id)
	    {
	       return false;
	    }
	}
    this->categoryList.push_back(category);
	return true;
}

// isbn can't changed;
bool CategoryManager::update(const Category & category)
{
    list<Category>::iterator iter;
	for(iter=categoryList.begin();iter!=categoryList.end();iter++)
	{
	    if(category.id==(*iter).id)
	    {
	       (*iter).name=category.name;
	    }
	}
	return true;
}


// string=isbn
bool CategoryManager::remove(int id)
{
    list<Category>::iterator iter;
	for(iter=categoryList.begin();iter!=categoryList.end();iter++)
	{
	    if(id==(*iter).id)
	    {
	       categoryList.erase(iter);
	    }
	}   
	return true;
}
 
void CategoryManager::flush()
{
    Unit unit(0);
    int unitSize=0;
    int unitPage=0;
    // CategoryCount=count of Category in file
    int categoryCount=0;    
    unit.write(categoryCount);
    unitSize+=sizeof(int);
    
    list<Category>::iterator iter;
	for(iter=categoryList.begin();iter!=categoryList.end();iter++)
	{
	    int t=unit.tellg();
	    Category category=*iter;
	    unitSize+=this->categorySize;
	    if(unitSize>=UNIT_SIZE)
	    {
	        reader.write(unit,unitPage);
	        unitPage++;
	        unit.seekg(0);
	        unitSize=this->categorySize;    //be import
	    }
	    this->writeCategory(unit,category); // write to another space of Unit
	    categoryCount++;
	}
	reader.write(unit,unitPage);
	///*
	Unit *unit1=reader.read(0);
	unit1->write(categoryCount);
	reader.write(*unit1,0);
    delete(unit1);
	//*/
}

void CategoryManager::read(int page)
{
	Unit *unit=reader.read(page);
	int countUnitSize=0,readCount=0;
	int categoryCount;
    unit->get(&categoryCount);
	countUnitSize+=sizeof(int);

	while(readCount<categoryCount)
	{
	    countUnitSize+=this->categorySize;
	    if(countUnitSize>=UNIT_SIZE)
	    {
	        delete(unit);
	        unit=reader.read(++page);
	        countUnitSize=this->categorySize;   ////////////////////////
	    }
	    Category category;
	    getCategory(*unit,category);
	    categoryList.push_back(category);
	    readCount++;
	}

	delete(unit);
}

void CategoryManager::writeCategory(Unit &unit,Category &category)
{
    unit.write(category.id);
    unit.writeString(category.name,32);
}

void CategoryManager::getCategory(Unit &unit,Category &category)
{
    unit.get(&category.id);
    category.name=unit.getString(32);
}
 