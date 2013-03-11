#include "stdafx.h"
#include "myOperate.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;


myOperate::myOperate(string CategoryPath,string BookPath):cm(CategoryPath),bm(BookPath)
{}

void myOperate::run()
{
    cout<<endl<<"图书馆共有 "<<bm.getBookCount()<<" 本图书,有 "<<cm.getCategoryCount()<<" 个图书种类"<<endl;
    
	// run until ch==7
	while(true)
	{
		char ch=this->getOperate()-'0';
		switch(ch)
		{
		case 1:
			insertBook();
			break;
		case 2:
			selectBook();
			break;
		case 3:
			deleteBook();
			break;
		case 4:
			modifyBook();
			break;
		case 5:
			borrowBook();
			break;
		case 6:
			statBook();
			break;
		case 7:
			cout<<"请不要关闭系统,保存数据中.........."<<endl;
			return;
		default:
			cout<<"对不起，您输入的操作最终还是有误，无法完成相应的操作！！"<<endl;
		}
	}
}

char myOperate::getOperate()
{
    string mark;
    cout<<endl<<"***********************************"<<endl;

	cout<<"1 添加图书"<<endl;
	cout<<"2 查询图书"<<endl;
	cout<<"3 删除图书"<<endl;
	cout<<"4 修改图书"<<endl;
	cout<<"5 借阅归还"<<endl;
	cout<<"6 统计图书"<<endl;
	cout<<"7 退出系统"<<endl;

	cout<<"请输入您要进行的操作：";
    cin>>mark;
    while(mark.length()!=1)
    {
        cout<<"对不起，您输入的操作码位数有误，请重新输入"<<endl;
        cin>>mark;
    }
	return mark[0];
}

bool myOperate::isContinue()
{
	string mark;
	cout<<"1- 继续此操作\t其它键- 返回上层"<<endl;
    cin>>mark;
    while(mark.length()!=1)
    {
        cout<<"对不起，您输入的操作码位数有误，请重新输入"<<endl;
        cin>>mark;
    }
	if(mark[0]=='1')return true;
	else return false;
}

/////////////////////////////////////////////////////////////////////
void myOperate::insertBook()
{
	do
	{
		cout<<endl<<"新增图书，请输入您要新增书本的详细信息......"<<endl;
		Book book;
		cout<<"输入书名：";
		cin>>book.name;
		cout<<"输入价格：";
		float p;
		cin>>p;
		book.price=p;
		cout<<"输入数目：";
		int t;
		cin>>t;
		book.count=(char)t;
		cout<<"输入isbn编号：";
		cin>>book.isbn;
		cout<<"请输入年份：";
		cin>>book.year;
		cout<<"输入关键字：";
		cin>>book.keyword;
		cout<<"输入目录编号：";
		cin>>book.categoryId;
		
		cout<<"请输入月份：";
		int m;
		cin>>m;
		book.month=char(m);
		cout<<"索书号：";
		cin>>book.searchNum;
		cout<<"标题：";
		cin>>book.title;
		cout<<"输入出版社：";
		cin>>book.press;
	    
		if(!bm.insert(book))
			cout<<"对不起，新增图书失败！"<<endl;
		else
		{
			cout<<"恭喜，已经成功添加该书本！"<<endl;
		}
	}while(isContinue());
   
}


void myOperate::borrowBook()
{
	do
	{
		cout<<endl<<"1 借阅图书"<<endl;
		cout<<"2 归还图书"<<endl;
		int num;
		cin>>num;
		vector<Book> bk;
		string isbn;
		switch(num)
		{
		case(1):
			cout<<"输入你要借阅图书ISBN"<<endl;			
			cin>>isbn;
			bm.select(bk,"|||"+isbn);
			if(bk.size()==0)
			cout<<"没有该图书，请重新确定你的ISBN是否正确。"<<endl;
			else
			{
				if((int)bk[0].count==0)
				{
					cout<<"非常抱歉，该书已被借完。"<<endl;
				}
				else
				{
					bk[0].count--;
					bm.update(bk[0]);
					cout<<"恭喜，借阅成功,剩余该书"<<(int)bk[0].count<<"本"<<endl;
				}
			}
			break;
		case(2):
			cout<<"输入你要归还图书ISBN"<<endl;			
			cin>>isbn;
			bm.select(bk,"|||"+isbn);
			if(bk.size()==0)
			cout<<"没有该图书，请重新确定你的ISBN是否正确。"<<endl;
			else
			{
				bk[0].count++;
				bm.update(bk[0]);
				cout<<"恭喜，归还成功,剩余该书"<<(int)bk[0].count<<"本"<<endl;
			}
			
			//bm.flush();
			break;
		default:
			cout<<"输入有误"<<endl;
			break;
		}
	}while(isContinue());
}

void myOperate::statBook()
{
	do
	{
		cout<<endl;
		cout<<"1 统计某一价格段的图书信息"<<endl;
		cout<<"2 统计某一类图书的平均价格"<<endl;
		int num;
		vector<Book> bk;
		cin>>num;
		switch(num)
		{
		case(1):
			cout<<"输入两个价格，从低到高"<<endl;
			float low;
			float high;
			cin>>low>>high;
			bm.selectBetween(bk,low,high);
			this->show(bk);
			break;
		case(2):
			cout<<"输入图书类别"<<endl;
			int category;
			cin>>category;
			cout<<"此类书籍的平均价格为："<<bm.averagePrice(category)<<endl;
			break;
		default:
			cout<<"输入码有误"<<endl;
			break;
		}
	}while(isContinue());
}

void myOperate::modifyBook()
{
	do
	{
		string modifyISBN;
		cout<<endl<<"这里您可以修改图书资料，请输入您要修改图书的isbn编号......"<<endl;
		cin>>modifyISBN;
		
		vector<Book> bk;
		bm.select(bk,"|||"+modifyISBN);

		if(bk.size()>0)
		{
			cout<<endl<<"以下是系统为您查询到该书的全部资料，";
			
			cout<<"请输入您要修改的字段对应的操作码！"<<endl;
			vector<Book>::iterator p;
			Book rBook;
			for(p=bk.begin();p!=bk.end();p++)
			{
				rBook=(*p);
			    
				cout<<"********************"<<endl;
				cout<<"****   1 修改书名："<<rBook.name<<endl;
				cout<<"****   2 修改价格："<<rBook.price<<"元"<<endl;
				cout<<"****   3 修改数目："<<(int)rBook.count<<endl;
				cout<<"****   4 修改所属科目："<<rBook.categoryId<<endl;
				cout<<"****   5 修改检索号："<<rBook.searchNum<<endl;
				cout<<"********************"<<endl;	        
			    
			}
			int tmpId;
			cin>>tmpId;
			char c;
			if(tmpId==1)
			{
				cout<<"请输入新书名：";
				cin>>rBook.name;
			}
			else if(tmpId==2)
			{
				cout<<"请输入新价格：";
				cin>>rBook.price;
			}
			else if(tmpId==3)
			{
				cout<<"请输入新数目：";
				int tmpInt;
				cin>>tmpInt;
				rBook.count=(char)tmpInt;
			}
			else if(tmpId==4)
			{
				cout<<"请输入新科目号：";
				cin>>rBook.categoryId;
			}
			else if(tmpId==5)
			{
				cout<<"请输入新检索号：";
				cin>>rBook.searchNum;
			}
			if(bm.update(rBook))
			{
				cout<<"修改成功"<<endl;
			}
			else
			{
				cout<<"图书修改失败，请联系管理员@"<<endl;
			}
		}
		else
		{
			cout<<"抱歉，系统查不到该本书！"<<endl;
		}
	}while(isContinue());

}

void myOperate::selectBook()
{
	do
	{
		int index;
		cout<<endl<<"****** 查询图书，请输入您要查询图书的字段 ********"<<endl;
		cout<<"1\t输入查询图书的名字"<<endl;
		cout<<"2\t输入查询图书的作者"<<endl;
		cout<<"3\t输入查询图书的出版社"<<endl;
		cout<<"4\t输入查询图书的ISBN"<<endl;
		cout<<"5\t输入查询图书的年份"<<endl;
		cout<<"6\t输入查询图书的月份"<<endl;
		cout<<"7\t输入查询图书的索书号"<<endl;
		cout<<"9\t输入查询图书的价格"<<endl;
		cout<<"10\t输入查询图书的关键字"<<endl;
		cout<<"11\t输入查询图书的标题"<<endl;

		vector<Book> bk;
		string str;
		cin>>index;
		if(index==1)
		{
			cout<<"请输入您要查询的书名：";
			getchar();
			getline(cin,str);
			bm.select(bk,""+str);
		}
		else if(index==2)
		{
			cout<<"请输入您要查询书的作者：";
			cin>>str;
			bm.select(bk,"|"+str);
		}
		else if(index==3)
		{
			cout<<"请输入您要查询书的出版社：";
			cin>>str;
			bm.select(bk,"||"+str);
		}
		else if(index==4)
		{
			cout<<"请输入您要查询书的isbn：";
			cin>>str;
			bm.select(bk,"|||"+str);
		}
		else if(index==5)
		{
			cout<<"请输入您要查询书的年份：";
			cin>>str;
			bm.select(bk,"||||"+str);
		}
		else if(index==6)
		{
			cout<<"请输入您要查询书的月份：";
			cin>>str;
			bm.select(bk,"|||||"+str);
		}
		else if(index==7)
		{
			cout<<"请输入您要查询书的索书号：";
			cin>>str;
			bm.select(bk,"||||||"+str);
		}
		else if(index==8)
		{
			cout<<"请输入您要查询书的价格：";
			cin>>str;
			bm.select(bk,"|||||||"+str);
		}
		else if(index==9)
		{
			cout<<"请输入您要查询书的关键字：";
			cin>>str;
			bm.select(bk,"||||||||"+str);
		}
		else if(index==10)
		{
			cout<<"请输入您要查询书的标题：";
			cin>>str;
			bm.select(bk,"|||||||||"+str);
		}
		else
		{
			cout<<"您输入的操作符有误！"<<endl;
		}
		show(bk);
	}while(isContinue());

}

void myOperate::deleteBook()
{
	do
	{
		string deleteISBN;
		cout<<endl<<"这里您可以删除图书，请输入您要删除图书的isbn编号......"<<endl;
		cin>>deleteISBN;

		if(!bm.remove(deleteISBN))
		{
			cout<<"对不起，不存在该isbn的图书，无法删除！"<<endl;
		}
		else
		{
			cout<<"恭喜，已经将该本书删除干净！"<<endl;
		}
		getchar();	
	}while(isContinue());
}



void myOperate::show(vector<Book> &bk)
{
    if(bk.size()>0)
    {
		cout<<endl<<"共查到了 "<<bk.size()<<" 本书籍，是否要全部打印？Y/N"<<endl;

		char tmp;
		cin>>tmp;
		if(tmp=='Y'||tmp=='y')
		{
			if(bk.size()>1){
				int index;
				cout<<endl<<"选择显示图书的方式......"<<endl;
				cout<<"1- 按年份从小到大"<<"\t 2- 按年份从大到小"<<endl;
				cout<<"3- 按月份从小到大"<<"\t 4- 按月份从大到小"<<endl;
				cout<<"5- 按书名从小到大"<<"\t 6- 按书名从大到小"<<endl;
				cout<<"7- 按作者从小到大"<<"\t 8- 按作者从大到小"<<endl;
				cout<<"9- 按检索号从小到大"<<"\t 10- 按检索号从大到小"<<endl;
				cout<<"11- 按ISBN从小到大"<<"\t 12- 按ISBN从大到小"<<endl;
				
				cin>>index;
				if(index==1)
				{
					bm.sort(bk,4,0);
				}
				else if(index==2)
				{
					bm.sort(bk,4,1);
				}
				else if(index==3)
				{
					bm.sort(bk,5,0);
				}
				else if(index==4)
				{
					bm.sort(bk,5,1);
				}
				else if(index==5)
				{
					bm.sort(bk,0,0);
				}
				else if(index==6)
				{
					bm.sort(bk,0,1);
				}
				else if(index==7)
				{
					bm.sort(bk,1,0);
				}
				else if(index==8)
				{
					bm.sort(bk,1,1);
				}
				else if(index==9)
				{
					bm.sort(bk,6,0);
				}
				else if(index==10)
				{
					bm.sort(bk,6,1);
				}
				else if(index==11)
				{
					bm.sort(bk,3,0);
				}
				else if(index==12)
				{
					bm.sort(bk,3,1);
				}
				else 
				{
					cout<<"您输入的操作码有误！"<<endl;
				}
			}

			vector<Book>::iterator p;
			for(p=bk.begin();p!=bk.end();p++)
			{
				Book rBook=(*p);
			    
				cout<<"********************"<<endl;
				cout<<"****书名："<<rBook.name<<endl;
				cout<<"****价格："<<rBook.price<<"元"<<endl;
				cout<<"****数目："<<(int)rBook.count<<endl;
				cout<<"****年份："<<(int)rBook.year<<endl;
				cout<<"****月份："<<(int)rBook.month<<endl;
				cout<<"****isbn编号："<<rBook.isbn<<endl;
				cout<<"****所属科目："<<rBook.categoryId<<endl;
				cout<<"****检索号："<<rBook.searchNum<<endl;
				cout<<"****作者："<<rBook.author<<endl;
				cout<<"****出版社："<<rBook.press<<endl;
				cout<<"********************"<<endl;	        
			    
			}
		}
    }
    else
    {
        cout<<"对不起，根据此输入信息查不到相应的图书"<<endl;
    }
}