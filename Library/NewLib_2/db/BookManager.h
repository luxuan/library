#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include "file/FileReader.h"
#include "file/FileUnit.h"

#include "Book.h"
#include <string>
#include <list>
#include <vector>
using namespace std;

// 100 books should be 600M space;
class BookManager
{
public :
    // string=file name
    BookManager(string);
    ~BookManager();
    
	int getBookCount();

    // string= select condtion;
	// select Books depend on condition=[string]
    void select(vector<Book> &,string);

	void selectBetween(vector<Book> &,float low,float high);
    
    void sort(vector<Book> &,int fieldNum,int orderBy);
    
	float averagePrice(int);

    bool insert(const Book &);
    
    // isbn can't changed;
    bool update(const Book &); 
    
    // string=isbn,remove Book where Book.isbn=[string]
    bool remove(string);

    void flush(); 
protected:    
    int bookSize;
    list<Book> bookList;
    FileReader reader;// int "file/FileReader.h"

	void read(int);   
	void writeBook(Unit &,Book &);
    void getBook(Unit &,Book &);
};
  
#endif