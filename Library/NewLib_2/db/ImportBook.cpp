
#include "stdafx.h"
#include "ImportBook.h"
#include "CategoryManager.h"
#include "ImportCategory.h"
#include <stdlib.h>
#include <time.h>


ImportBook::ImportBook(string datafile):BookManager(datafile)
{

}

ImportBook::~ImportBook()
{
	reader.close();
}

// override;
void ImportBook::flush()
{
	string categoryFile="data_/chinapub-book-category.txt";
	string bookFileDir="data_/book-detail/";
	string bookFile;

	///// from BookManager
	Unit unit(0);
    int unitSize=0;
    int unitPage=0;
    // bookCount=count of Book in file
    int bookCount=0;    
    unit.write(bookCount);
    unitSize+=sizeof(int);
    ///// from BookManager

	///*


	vector<Category> categoryVector;
	ImportCategory::getCategory(categoryVector,categoryFile);

	vector<Category>::iterator cp;
	
	int searchNumber=0;
	//int a=1,b=10;
	for(cp=categoryVector.begin();cp!=categoryVector.end();cp++)
	{
		//if(cp->id<a)continue;
		//if(cp->id>b)break;
		char str[4];
		itoa(cp->id, str, 10);
		bookFile=bookFileDir+str+".txt";
		
		cout<<"open: "<<bookFile<<endl;

		vector<Book> bookVector;
		getBook(bookVector,bookFile);

		vector<Book>::iterator bp;	
		for(bp=bookVector.begin();bp!=bookVector.end();bp++)
		{
			///// from BookManager
			Book book=*bp;			
			book.categoryId=cp->id;
			book.searchNum=++searchNumber;
			book.count=getBookCount();
			//cout<<book.name<<"\t"<<book.keyword<<endl;

			unitSize+=bookSize;	//bookSize <-BookManager
			if(unitSize>=UNIT_SIZE)	//UNIT_SIZE <-BookManager
			{
				reader.write(unit,unitPage);
				unitPage++;
				unit.seekg(0);
				unitSize=bookSize;    //be import! 
			}
			writeBook(unit,book); // write to another space of Unit
			bookCount++;
			///// from BookManager
		}
	}
	reader.write(unit,unitPage);	//write the last page
	Unit *unit1=reader.read(0);
	unit1->write(bookCount);
	reader.write(*unit1,0);
    delete(unit1);
	cout<<"ImportBook.flush.bookCount="<<bookCount<<endl;
}


void ImportBook::getBook(vector<Book>& bookVector , const string filename)
{
	ifstream input;
	input.open(filename.data());
	if(input.fail())
	{
		cout<<filename<<" not exsit."<<endl;
		return;
	}
	char line[Book_Char_Size];
	while(!input.eof())
	{
		input.getline(line,Book_Char_Size,'\n');
		Book book;
		if(line[0]=='/')
		{
			filterBook(book,line);

			if(book.year>0)
			{
			    bookVector.push_back(book);
			    //cout<<"price="<<book.price<<"\tname="<<book.name<<"\tyear="<<book.year<<"\tmonth="<<(int)book.month<<endl;
			}
		}
	}
	input.close();	
}


void ImportBook::filterBook(Book & book,char* p)
{
	char str[50];
	int index=0;
	while(p[index]!='\t'){index++;}
	
	// book name
	int t=0;	
	index++;
	index++;
	while(p[index]!='\t')
	{
		book.name+=p[index++];
	}
	
	// price
	t=0;
	index++;
	index++;
	while(p[index]!='\t')
	{
		str[t++]=p[index++];
	}
	str[++t]='\0';
	book.price=atof(str);

	// author
	t=0;
	index++;
	index++;
	while(p[index]!='\t')
	{
		book.author+=p[index++];
	}

	// title ´ÔÊéÃû
	t=0;
	index++;
	index++;
	while(p[index]!='\t')
	{
		book.title+=p[index++];
	}

	// press
	t=0;
	index++;
	index++;
	while(p[index]!='\t')
	{
		book.press+=p[index++];
	}


	// isbn
	t=0;
	index++;
	index++;
	while(p[index]!='\t')
	{
		book.isbn+=p[index++];
	}

	// skep 2003-11-12
	index++;
	while(p[index]!='\t'){index++;}

	// year and month;
	t=0;
	index++;
	index++;
	//cout<<"index="<<index;
	//cout<<"\tprice="<<book.price<<"\tname="<<book.name<<"\tisbn="<<book.isbn<<endl;
	while(p[index]!='\t')
	{
		str[t++]=p[index++];
	}
	str[++t]='\0';
	char ym[5];
	// year
	for(char i=0;i<4;i++)ym[i]=str[i];
	ym[4]='\0';
	book.year=atoi(ym);
	// month
	ym[0]=str[7];
	if(str[8]<'3'&&str[8]>='0')
	{
		ym[1]=str[8];
		ym[2]='\0';
	}
	else
	{
		ym[1]='\0';
	}
	book.month=atoi(ym);

	// skep kaiben
	index++;
	while(p[index]!='\t'){index++;}
	// skep page
	index++;
	while(p[index]!='\t'){index++;}
	// skep banci
	index++;
	while(p[index]!='\t'){index++;}

	// keyword
	t=0;
	index++;
	while(p[index]!='\0')
	{
		book.keyword+=p[index++];
	}
	book.keyword+='\0';
}

char ImportBook::getBookCount()
{
	srand(time(0));
	char b=rand()%64+2;
	return b;
}

