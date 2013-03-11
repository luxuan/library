#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include "file/FileReader.h"
#include "file/FileUnit.h"

#include "Category.h"
#include <string>
#include <list>
using namespace std;

class CategoryManager
{
 public :
    CategoryManager(string);
    ~CategoryManager();

    int getCategoryCount();

    int getId(string);	//get Category.id by Category.name=[string];
    string getName(int);  //get Category.name by Category.id=[int];
    
    bool insert(const Category &);	// why can't return bool type??
    
    bool update(const Category &);
    
    bool remove(int);	//remove Category where Category.id=[int];

    void flush(); 
protected:    
    int categorySize;
    list<Category> categoryList;
    FileReader reader;	// int "file/FileReader.h"

    void read(int);
	void writeCategory(Unit &,Category &);
    void getCategory(Unit &,Category &);

private :

};

#endif