#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book 
{
public :
    string name;
    string author;
    string press;
    string isbn;
    int year;
    char month;
    int searchNum;
    float price;
    string keyword;
    string title;
    char count;
    int categoryId; 
    //void operator=(const Book&);  
};
/*
void Book::operator=(const Book& book)
{
    this->name=book.name;
    this->author=book.author;
    this->press=book.press;
    this->isbn=book.isbn;
    this->year=book.year;
    this->month=book.month;
    this->searchNum=book.searchNum;
    this->price=book.price;
    
}
*/
#endif