#include "stdafx.h"
#include "BookManager.h"

#include <stdlib.h> 
#include <math.h> 
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

// string=file name
BookManager::BookManager(string filename):reader(filename)
{
    bookSize=(sizeof(char)*(208+2));
    bookSize+=(sizeof(int)*3);
    bookSize+=sizeof(float);
    this->read(0);
}
BookManager::~BookManager()
{
    this->flush();
    reader.close();
}

int BookManager::getBookCount()
{
    return this->bookList.size();
}

void BookManager::select(vector<Book> & bookVector,string condition)
{
    list<Book>::iterator iter;
	string field[12];	
	int i;	
	int fieldNum=0;
	for(i=0;i<condition.length();i++)
	{	
		if(condition[i]=='|')
		{
			fieldNum++;		
			continue;
		}
		if(fieldNum>12)
			break;
		field[fieldNum]=field[fieldNum]+condition[i];
	}
	int spaceNum=0;
	for(i=0;i<condition.length();i++)
	{	
		if(condition[i]==' ')
			spaceNum++;
	}
	
	spaceNum++;
	string *name=new string[spaceNum];
	int loopNum=0;
	for(i=0;i<condition.length();i++)
	{	
		if(condition[i]!=' ')
		name[loopNum]=name[loopNum]+condition[i];
		else
		loopNum++;
	}	
	bool selected=true;
	for(iter=bookList.begin();iter!=bookList.end();iter++)
	{
	    selected=true;
		if(field[0].length()!=0)
		{
			for(i=0;i<spaceNum;i++)
			{
				selected=selected&&(*iter).name.find(name[i])!=string::npos;	
			}
		}	
		if(field[1].length()!=0)
		selected=selected&&(*iter).author.find(field[1])!=string::npos;
		if(field[2].length()!=0)
		selected=selected&&(*iter).press.find(field[2])!=string::npos;
		if(field[3].length()!=0)
		{
			selected=selected&&(strcmp((*iter).isbn.data(),field[3].data())==0);
			if(selected)
			{
			   bookVector.push_back(*iter); 
			   return;
			}
		}
		//selected=selected&&(*iter).isbn.find(field[3])!=string::npos;		
		if(field[4].length()!=0)
		selected=selected&&((*iter).year==atoi(field[4].data()));
		if(field[5].length()!=0)
		selected=selected&&((int)(*iter).month==atoi(field[5].data()));
		if(field[6].length()!=0)
		selected=selected&&((*iter).searchNum==atoi(field[6].data()));
		if(field[7].length()!=0)
		{
		    float f;
		    f=atof(field[7].c_str());
		    selected=selected&&((*iter).price==f);
		}
		if(field[8].length()!=0)
		selected=selected&&(*iter).keyword.find(field[8])!=string::npos;
		if(field[9].length()!=0)
		selected=selected&&(*iter).title.find(field[9])!=string::npos;
		if(field[10].length()!=0)
		selected=selected&&(int)((*iter).count==atoi(field[10].data()));
		if(field[11].length()!=0)
		selected=selected&&((*iter).categoryId==atoi(field[11].data()));
	
	    if(selected)
	    {
			//Book *p=new Book;
	       //*p=*iter;
	       bookVector.push_back(*iter); 	       
	    }
		
	}
	delete []name;
	
	
}


void BookManager::selectBetween(vector<Book> & bookVector,float low,float high)
{
    list<Book>::iterator iter;	
	int i;	
	for(iter=bookList.begin();iter!=bookList.end();iter++)
	{
	    if((*iter).price>low&&(*iter).price<high)
	    {
	       bookVector.push_back(*iter); 
	    }
	}
	
}

void BookManager::sort(vector<Book> &bookVector,int fieldNum,int orderBy)
{
    int total=bookVector.size();
    int i,j;
   for(i=0;i<total-1;++i)  
   {
	for(j=0;j<total-1-i;++j)
	  {
	    switch(fieldNum)
		{
			case(0):	
				if(orderBy==0)
				{
					if(bookVector[j].name.compare(bookVector[j+1].name)>0)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].name.compare(bookVector[j+1].name)<0)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(1):	
				if(orderBy==0)
				{
					if(bookVector[j].author.compare(bookVector[j+1].author)>0)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].author.compare(bookVector[j+1].author)<0)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(2):	
				if(orderBy==0)
				{
					if(bookVector[j].press.compare(bookVector[j+1].press)>0)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].press.compare(bookVector[j+1].press)<0)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(3):
				if(orderBy==0)
				{
					if(bookVector[j].isbn.compare(bookVector[j+1].isbn)>0)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].isbn.compare(bookVector[j+1].isbn)<0)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(4):
				if(orderBy==0)
				{
					if(bookVector[j].year>bookVector[j+1].year)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].year<bookVector[j+1].year)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(5):
				if(orderBy==0)
				{
					if(bookVector[j].month>bookVector[j+1].month)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].month<bookVector[j+1].month)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(6):
				if(orderBy==0)
				{
					if(bookVector[j].searchNum>bookVector[j+1].searchNum)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].searchNum<bookVector[j+1].searchNum)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(7):
				if(orderBy==0)
				{
					if(bookVector[j].price>bookVector[j+1].price)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].price<bookVector[j+1].price)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(8):
				if(orderBy==0)
				{
					if(bookVector[j].keyword.compare(bookVector[j+1].keyword)>0)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].keyword.compare(bookVector[j+1].keyword)<0)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(9):
				if(orderBy==0)
				{
					if(bookVector[j].title.compare(bookVector[j+1].title)>0)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].title.compare(bookVector[j+1].title)<0)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(10):
				if(orderBy==0)
				{
					if(bookVector[j].count>bookVector[j+1].count)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].count<bookVector[j+1].count)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			case(11):
				if(orderBy==0)
				{
					if(bookVector[j].categoryId>bookVector[j+1].categoryId)
					swap(bookVector[j],bookVector[j+1]);
				}
				else
				{
					if(bookVector[j].categoryId<bookVector[j+1].categoryId)
					swap(bookVector[j],bookVector[j+1]);
				}
				break;
			default:
			cout<<"Error:no this field"<<endl;
			break;
		}   
	 }
   }         
  
		
	
	
    

   
} 


bool BookManager::insert(const Book &book)
{
	list<Book>::iterator p;
	for(p=bookList.begin();p!=bookList.end();p++)
	{
		if(book.isbn.compare(p->isbn)==0)
	    {
	       return false;
	    }
	}
    this->bookList.push_back(book);
	return true;
}

// isbn can't changed;
bool BookManager::update(const Book & book)
{
    list<Book>::iterator iter;
	for(iter=bookList.begin();iter!=bookList.end();iter++)
	{
	    if(book.isbn.compare((*iter).isbn)==0)
	    {
	       *iter=book;
		   return true;
	    }
	}
	return false;
}



// string=isbn
bool BookManager::remove(string isbn)
{
    list<Book>::iterator iter;
	for(iter=bookList.begin();iter!=bookList.end();iter++)
	{
	    if(isbn.compare((*iter).isbn)==0)
	    {
	       bookList.erase(iter);
	       return true;
	    }
	}
	return false;
}
 
void BookManager::flush()
{
    Unit unit(0);
    int unitSize=0;
    int unitPage=0;
    // bookCount=count of Book in file
    int bookCount=0;    
    unit.write(bookCount);
    unitSize+=sizeof(int);
    
    list<Book>::iterator iter;
	for(iter=bookList.begin();iter!=bookList.end();iter++)
	{
	    //int t=unit.tellg();
	    Book book=*iter;
	    unitSize+=this->bookSize;
	    if(unitSize>=UNIT_SIZE)
	    {
	        reader.write(unit,unitPage);
	        unitPage++;
	        unit.seekg(0);
	        unitSize=this->bookSize;    //be import
	    }
	    this->writeBook(unit,book); // write to another space of Unit
	    bookCount++;
	}
	reader.write(unit,unitPage);	//write the last page;
	///*
	Unit *unit1=reader.read(0);
	unit1->write(bookCount);
	reader.write(*unit1,0);
    delete(unit1);

	//cout<<"bookManager.flush.bookCount="<<bookCount<<endl;
	//*/
}

void BookManager::read(int page)
{
	Unit *unit=reader.read(page);
	int countUnitSize=0,readCount=0;
	int bookCount;
    unit->get(&bookCount);
	countUnitSize+=sizeof(int);
	
	while(readCount<bookCount)
	{
		if(readCount%256==0){
			if(readCount%5120==0)cout<<"\nLoad: "<<(readCount*1.0/bookCount*100)<<"% ";
			cout<<". ";
		}
	    countUnitSize+=this->bookSize;
	    if(countUnitSize>=UNIT_SIZE)
	    {
	        delete(unit);
	        unit=reader.read(++page);
	        countUnitSize=this->bookSize;   ////////////////////////
	    }
	    Book book;
	    getBook(*unit,book);
	    bookList.push_back(book);
	    readCount++;
	}
	delete(unit);
	cout<<endl;

}

void BookManager::writeBook(Unit &unit,Book &book)
{
    unit.writeString(book.name,64);
    unit.writeString(book.author,16);
    unit.writeString(book.press,32);
    unit.writeString(book.isbn,16);
    unit.write(book.year);
    unit.write(book.month);
    unit.write(book.searchNum);
    unit.write(book.price);
    unit.writeString(book.keyword,48);
    unit.writeString(book.title,32);
    unit.write(book.count);
    unit.write(book.categoryId);
}

void BookManager::getBook(Unit &unit,Book &book)
{
    book.name=unit.getString(64);
    book.author=unit.getString(16);
    book.press=unit.getString(32);
    book.isbn=unit.getString(16);
    unit.get(&book.year);
    unit.get(&book.month);
    unit.get(&book.searchNum);
    unit.get(&book.price);
    book.keyword=unit.getString(48);
    book.title=unit.getString(32);
    unit.get(&book.count);
    unit.get(&book.categoryId);
}

//coded by jzw
float BookManager:: averagePrice(int categoryId)
{
	list<Book>::iterator iter;	
	int i;	
	float average=0;
	int num=0;
	for(iter=bookList.begin();iter!=bookList.end();iter++)
	{
	    if((*iter).categoryId==categoryId)
	    {
			num++;
			average=((*iter).price-average)/num+average;
	    }
		
	}
	if(num==0)
	{
		cout<<"没有此类书籍"<<endl;
	}
	return average;
}

