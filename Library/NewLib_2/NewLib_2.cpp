// NewLib_2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdio.h"
#include "stdafx.h"
#include "db/BookManager.h"
#include "myOperate.h"
#include "db/CategoryManager.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void welcome();
void operate();

int main()
{
    welcome();    
	operate();
	cout<<"ллʹ��,�����ѱ���,��������˳���"<<endl;
	getchar();
	getchar();
	return 0;
}

void welcome()//�û���¼����,ѡ���¼���
{
	cout<<endl;
	cout<<endl;
	cout<<"                      ***************************\n"; 
	cout<<"                         ��ӭʹ��ͼ�����ϵͳ\n"; 
	cout<<"                      ***************************\n"; 
	cout<<endl;
	cout<<endl;
}

void operate()
{
	myOperate a("data/2.rg","data/1.rg");
	a.run();
}




