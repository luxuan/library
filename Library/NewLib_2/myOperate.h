#ifndef MYOPERATE_H
#define MYOPERATE_H


#include<iostream>
#include "db/BookManager.h"
#include "db/CategoryManager.h"
using namespace std;

class myOperate
{
private:
	CategoryManager cm;
    BookManager bm;
public:
	myOperate(string,string);
	void run();

protected:
	bool isContinue();
	char getOperate();
	void show(vector<Book> &);	

	// operate 
	void insertBook();
	void selectBook();
	void deleteBook();
	void borrowBook();
	void modifyBook();
	void statBook();

};

#endif