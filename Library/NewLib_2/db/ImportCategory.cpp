#include "stdafx.h"
#include "ImportCategory.h"
#include "BookManager.h"
#include "CategoryManager.h"

#include <stdlib.h>



void ImportCategory::saveCategory()
{
	string categoryFile="data_/chinapub-book-category.txt";
	CategoryManager cm("data/2.rg");

	vector<Category> categoryVector;
	getCategory(categoryVector,categoryFile);

	vector<Category>::iterator cp;
	int index;
	for(cp=categoryVector.begin();cp!=categoryVector.end();cp++)
	{
		index=0;
		while(cp->name[index]!='\t')index++;
		cp->name[index]='|';
		cm.insert(*cp);
		cout<<"save:"<<(cp->id)<<"\t"<<(cp->name)<<endl;
	}
}


void ImportCategory::getCategory(vector<Category>& categoryVector , const string filename)
{
	ifstream input;
	input.open(filename.data());
	char line[200];
	while(!input.eof())
	{
		input.getline(line,200,'\n');
		Category c;
		filterCategory(c,line);
		categoryVector.push_back(c);
	}
	input.close();
}


void ImportCategory::filterCategory(Category & category,char* p)
{
	char str[Category_Char_Size];
	int index=0;
	while(p[index]!='\t'){str[index]=p[index];index++;}
	str[++index]='\0';
	category.id=atoi(str);

	int t=0;
	while(p[index]!='\t')
	{
		str[t++]=p[index++];
	}
	
	str[t++]=p[index++];

	while(p[index]!='\t'){str[t]=p[index];index++;t++;}
	str[++t]='\0';
	//cout<<"str= "<<str<<endl;
	category.name=(string)str;
	
}
