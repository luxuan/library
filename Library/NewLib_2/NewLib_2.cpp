// NewLib_2.cpp : 定义控制台应用程序的入口点。
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
	cout<<"谢谢使用,数据已保存,按任意键退出！"<<endl;
	getchar();
	getchar();
	return 0;
}

void welcome()//用户登录界面,选择登录身份
{
	cout<<endl;
	cout<<endl;
	cout<<"                      ***************************\n"; 
	cout<<"                         欢迎使用图书管理系统\n"; 
	cout<<"                      ***************************\n"; 
	cout<<endl;
	cout<<endl;
}

void operate()
{
	myOperate a("data/2.rg","data/1.rg");
	a.run();
}




