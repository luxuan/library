#ifndef IMPORTBOOK_H
#define IMPORTBOOK_H

#define Book_Char_Size 1000
#define Category_Char_Size 50

#include "BookManager.h"
#include "Book.h"
#include "Category.h"
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ImportBook:public BookManager
{
public :
	
	ImportBook(string);
	~ImportBook();
    void flush();

	// [string]=filename
	// vector<Book>&=return book detail information
	void getBook(vector<Book>& , const string);

private :
	void filterCategory(Category &,char *);
	void filterBook(Book &,char *);
	char getBookCount();
};

#endif