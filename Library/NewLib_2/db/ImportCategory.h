#ifndef IMPORTCATEGORY_H
#define IMPORTCATEGORY_H

#define Book_Char_Size 1000
#define Category_Char_Size 50


#include "Book.h"
#include "Category.h"
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ImportCategory
{
public :

	static void saveCategory();
	// [string]=filename
	// vector<string>&=return book category
	static void getCategory(vector<Category>& , const string);

	// [string]=filename
	// vector<Book>&=return book detail information

private :
	static void filterCategory(Category &,char *);
	static void filterBook(Book &,char *);
};

#endif