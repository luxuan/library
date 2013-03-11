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
    cout<<endl<<"ͼ��ݹ��� "<<bm.getBookCount()<<" ��ͼ��,�� "<<cm.getCategoryCount()<<" ��ͼ������"<<endl;
    
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
			cout<<"�벻Ҫ�ر�ϵͳ,����������.........."<<endl;
			return;
		default:
			cout<<"�Բ���������Ĳ������ջ��������޷������Ӧ�Ĳ�������"<<endl;
		}
	}
}

char myOperate::getOperate()
{
    string mark;
    cout<<endl<<"***********************************"<<endl;

	cout<<"1 ���ͼ��"<<endl;
	cout<<"2 ��ѯͼ��"<<endl;
	cout<<"3 ɾ��ͼ��"<<endl;
	cout<<"4 �޸�ͼ��"<<endl;
	cout<<"5 ���Ĺ黹"<<endl;
	cout<<"6 ͳ��ͼ��"<<endl;
	cout<<"7 �˳�ϵͳ"<<endl;

	cout<<"��������Ҫ���еĲ�����";
    cin>>mark;
    while(mark.length()!=1)
    {
        cout<<"�Բ���������Ĳ�����λ����������������"<<endl;
        cin>>mark;
    }
	return mark[0];
}

bool myOperate::isContinue()
{
	string mark;
	cout<<"1- �����˲���\t������- �����ϲ�"<<endl;
    cin>>mark;
    while(mark.length()!=1)
    {
        cout<<"�Բ���������Ĳ�����λ����������������"<<endl;
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
		cout<<endl<<"����ͼ�飬��������Ҫ�����鱾����ϸ��Ϣ......"<<endl;
		Book book;
		cout<<"����������";
		cin>>book.name;
		cout<<"����۸�";
		float p;
		cin>>p;
		book.price=p;
		cout<<"������Ŀ��";
		int t;
		cin>>t;
		book.count=(char)t;
		cout<<"����isbn��ţ�";
		cin>>book.isbn;
		cout<<"��������ݣ�";
		cin>>book.year;
		cout<<"����ؼ��֣�";
		cin>>book.keyword;
		cout<<"����Ŀ¼��ţ�";
		cin>>book.categoryId;
		
		cout<<"�������·ݣ�";
		int m;
		cin>>m;
		book.month=char(m);
		cout<<"����ţ�";
		cin>>book.searchNum;
		cout<<"���⣺";
		cin>>book.title;
		cout<<"��������磺";
		cin>>book.press;
	    
		if(!bm.insert(book))
			cout<<"�Բ�������ͼ��ʧ�ܣ�"<<endl;
		else
		{
			cout<<"��ϲ���Ѿ��ɹ���Ӹ��鱾��"<<endl;
		}
	}while(isContinue());
   
}


void myOperate::borrowBook()
{
	do
	{
		cout<<endl<<"1 ����ͼ��"<<endl;
		cout<<"2 �黹ͼ��"<<endl;
		int num;
		cin>>num;
		vector<Book> bk;
		string isbn;
		switch(num)
		{
		case(1):
			cout<<"������Ҫ����ͼ��ISBN"<<endl;			
			cin>>isbn;
			bm.select(bk,"|||"+isbn);
			if(bk.size()==0)
			cout<<"û�и�ͼ�飬������ȷ�����ISBN�Ƿ���ȷ��"<<endl;
			else
			{
				if((int)bk[0].count==0)
				{
					cout<<"�ǳ���Ǹ�������ѱ����ꡣ"<<endl;
				}
				else
				{
					bk[0].count--;
					bm.update(bk[0]);
					cout<<"��ϲ�����ĳɹ�,ʣ�����"<<(int)bk[0].count<<"��"<<endl;
				}
			}
			break;
		case(2):
			cout<<"������Ҫ�黹ͼ��ISBN"<<endl;			
			cin>>isbn;
			bm.select(bk,"|||"+isbn);
			if(bk.size()==0)
			cout<<"û�и�ͼ�飬������ȷ�����ISBN�Ƿ���ȷ��"<<endl;
			else
			{
				bk[0].count++;
				bm.update(bk[0]);
				cout<<"��ϲ���黹�ɹ�,ʣ�����"<<(int)bk[0].count<<"��"<<endl;
			}
			
			//bm.flush();
			break;
		default:
			cout<<"��������"<<endl;
			break;
		}
	}while(isContinue());
}

void myOperate::statBook()
{
	do
	{
		cout<<endl;
		cout<<"1 ͳ��ĳһ�۸�ε�ͼ����Ϣ"<<endl;
		cout<<"2 ͳ��ĳһ��ͼ���ƽ���۸�"<<endl;
		int num;
		vector<Book> bk;
		cin>>num;
		switch(num)
		{
		case(1):
			cout<<"���������۸񣬴ӵ͵���"<<endl;
			float low;
			float high;
			cin>>low>>high;
			bm.selectBetween(bk,low,high);
			this->show(bk);
			break;
		case(2):
			cout<<"����ͼ�����"<<endl;
			int category;
			cin>>category;
			cout<<"�����鼮��ƽ���۸�Ϊ��"<<bm.averagePrice(category)<<endl;
			break;
		default:
			cout<<"����������"<<endl;
			break;
		}
	}while(isContinue());
}

void myOperate::modifyBook()
{
	do
	{
		string modifyISBN;
		cout<<endl<<"�����������޸�ͼ�����ϣ���������Ҫ�޸�ͼ���isbn���......"<<endl;
		cin>>modifyISBN;
		
		vector<Book> bk;
		bm.select(bk,"|||"+modifyISBN);

		if(bk.size()>0)
		{
			cout<<endl<<"������ϵͳΪ����ѯ�������ȫ�����ϣ�";
			
			cout<<"��������Ҫ�޸ĵ��ֶζ�Ӧ�Ĳ����룡"<<endl;
			vector<Book>::iterator p;
			Book rBook;
			for(p=bk.begin();p!=bk.end();p++)
			{
				rBook=(*p);
			    
				cout<<"********************"<<endl;
				cout<<"****   1 �޸�������"<<rBook.name<<endl;
				cout<<"****   2 �޸ļ۸�"<<rBook.price<<"Ԫ"<<endl;
				cout<<"****   3 �޸���Ŀ��"<<(int)rBook.count<<endl;
				cout<<"****   4 �޸�������Ŀ��"<<rBook.categoryId<<endl;
				cout<<"****   5 �޸ļ����ţ�"<<rBook.searchNum<<endl;
				cout<<"********************"<<endl;	        
			    
			}
			int tmpId;
			cin>>tmpId;
			char c;
			if(tmpId==1)
			{
				cout<<"��������������";
				cin>>rBook.name;
			}
			else if(tmpId==2)
			{
				cout<<"�������¼۸�";
				cin>>rBook.price;
			}
			else if(tmpId==3)
			{
				cout<<"����������Ŀ��";
				int tmpInt;
				cin>>tmpInt;
				rBook.count=(char)tmpInt;
			}
			else if(tmpId==4)
			{
				cout<<"�������¿�Ŀ�ţ�";
				cin>>rBook.categoryId;
			}
			else if(tmpId==5)
			{
				cout<<"�������¼����ţ�";
				cin>>rBook.searchNum;
			}
			if(bm.update(rBook))
			{
				cout<<"�޸ĳɹ�"<<endl;
			}
			else
			{
				cout<<"ͼ���޸�ʧ�ܣ�����ϵ����Ա@"<<endl;
			}
		}
		else
		{
			cout<<"��Ǹ��ϵͳ�鲻���ñ��飡"<<endl;
		}
	}while(isContinue());

}

void myOperate::selectBook()
{
	do
	{
		int index;
		cout<<endl<<"****** ��ѯͼ�飬��������Ҫ��ѯͼ����ֶ� ********"<<endl;
		cout<<"1\t�����ѯͼ�������"<<endl;
		cout<<"2\t�����ѯͼ�������"<<endl;
		cout<<"3\t�����ѯͼ��ĳ�����"<<endl;
		cout<<"4\t�����ѯͼ���ISBN"<<endl;
		cout<<"5\t�����ѯͼ������"<<endl;
		cout<<"6\t�����ѯͼ����·�"<<endl;
		cout<<"7\t�����ѯͼ��������"<<endl;
		cout<<"9\t�����ѯͼ��ļ۸�"<<endl;
		cout<<"10\t�����ѯͼ��Ĺؼ���"<<endl;
		cout<<"11\t�����ѯͼ��ı���"<<endl;

		vector<Book> bk;
		string str;
		cin>>index;
		if(index==1)
		{
			cout<<"��������Ҫ��ѯ��������";
			getchar();
			getline(cin,str);
			bm.select(bk,""+str);
		}
		else if(index==2)
		{
			cout<<"��������Ҫ��ѯ������ߣ�";
			cin>>str;
			bm.select(bk,"|"+str);
		}
		else if(index==3)
		{
			cout<<"��������Ҫ��ѯ��ĳ����磺";
			cin>>str;
			bm.select(bk,"||"+str);
		}
		else if(index==4)
		{
			cout<<"��������Ҫ��ѯ���isbn��";
			cin>>str;
			bm.select(bk,"|||"+str);
		}
		else if(index==5)
		{
			cout<<"��������Ҫ��ѯ�����ݣ�";
			cin>>str;
			bm.select(bk,"||||"+str);
		}
		else if(index==6)
		{
			cout<<"��������Ҫ��ѯ����·ݣ�";
			cin>>str;
			bm.select(bk,"|||||"+str);
		}
		else if(index==7)
		{
			cout<<"��������Ҫ��ѯ�������ţ�";
			cin>>str;
			bm.select(bk,"||||||"+str);
		}
		else if(index==8)
		{
			cout<<"��������Ҫ��ѯ��ļ۸�";
			cin>>str;
			bm.select(bk,"|||||||"+str);
		}
		else if(index==9)
		{
			cout<<"��������Ҫ��ѯ��Ĺؼ��֣�";
			cin>>str;
			bm.select(bk,"||||||||"+str);
		}
		else if(index==10)
		{
			cout<<"��������Ҫ��ѯ��ı��⣺";
			cin>>str;
			bm.select(bk,"|||||||||"+str);
		}
		else
		{
			cout<<"������Ĳ���������"<<endl;
		}
		show(bk);
	}while(isContinue());

}

void myOperate::deleteBook()
{
	do
	{
		string deleteISBN;
		cout<<endl<<"����������ɾ��ͼ�飬��������Ҫɾ��ͼ���isbn���......"<<endl;
		cin>>deleteISBN;

		if(!bm.remove(deleteISBN))
		{
			cout<<"�Բ��𣬲����ڸ�isbn��ͼ�飬�޷�ɾ����"<<endl;
		}
		else
		{
			cout<<"��ϲ���Ѿ����ñ���ɾ���ɾ���"<<endl;
		}
		getchar();	
	}while(isContinue());
}



void myOperate::show(vector<Book> &bk)
{
    if(bk.size()>0)
    {
		cout<<endl<<"���鵽�� "<<bk.size()<<" ���鼮���Ƿ�Ҫȫ����ӡ��Y/N"<<endl;

		char tmp;
		cin>>tmp;
		if(tmp=='Y'||tmp=='y')
		{
			if(bk.size()>1){
				int index;
				cout<<endl<<"ѡ����ʾͼ��ķ�ʽ......"<<endl;
				cout<<"1- ����ݴ�С����"<<"\t 2- ����ݴӴ�С"<<endl;
				cout<<"3- ���·ݴ�С����"<<"\t 4- ���·ݴӴ�С"<<endl;
				cout<<"5- ��������С����"<<"\t 6- �������Ӵ�С"<<endl;
				cout<<"7- �����ߴ�С����"<<"\t 8- �����ߴӴ�С"<<endl;
				cout<<"9- �������Ŵ�С����"<<"\t 10- �������ŴӴ�С"<<endl;
				cout<<"11- ��ISBN��С����"<<"\t 12- ��ISBN�Ӵ�С"<<endl;
				
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
					cout<<"������Ĳ���������"<<endl;
				}
			}

			vector<Book>::iterator p;
			for(p=bk.begin();p!=bk.end();p++)
			{
				Book rBook=(*p);
			    
				cout<<"********************"<<endl;
				cout<<"****������"<<rBook.name<<endl;
				cout<<"****�۸�"<<rBook.price<<"Ԫ"<<endl;
				cout<<"****��Ŀ��"<<(int)rBook.count<<endl;
				cout<<"****��ݣ�"<<(int)rBook.year<<endl;
				cout<<"****�·ݣ�"<<(int)rBook.month<<endl;
				cout<<"****isbn��ţ�"<<rBook.isbn<<endl;
				cout<<"****������Ŀ��"<<rBook.categoryId<<endl;
				cout<<"****�����ţ�"<<rBook.searchNum<<endl;
				cout<<"****���ߣ�"<<rBook.author<<endl;
				cout<<"****�����磺"<<rBook.press<<endl;
				cout<<"********************"<<endl;	        
			    
			}
		}
    }
    else
    {
        cout<<"�Բ��𣬸��ݴ�������Ϣ�鲻����Ӧ��ͼ��"<<endl;
    }
}