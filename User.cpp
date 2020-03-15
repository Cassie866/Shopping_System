#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include "BasicTool.h"
#include "User.h"
using namespace std;

fstream inout;


Seller::Seller()
{
	_password = "12345678";
}

void Seller::AppendCom(vector<Commodity>& list)
{
	int oldsize = list.size();
	cout << "添加新商品?  Y/N" << endl;
	string ch;
	while (cin >> ch)
	{
		if (ch == "N" || ch == "n")
		{
			break;
		}
		if (ch != "Y" && ch != "y")
		{
			cout << "输入错误，请重新输入：" << endl;
			continue;
		}
		cout << "请输入商品名称：";
		string str;
		cin >> str;
		Commodity com;
		com.SetComName(str);
		cout << "请输入商品编号：";
		cin >> str;
		com.SetComID(str);
		cout << "请输入商品价格：";
		double d;
		cin >> d;
		com.SetComPrice(d);
		list.push_back(com);
		cout << "商品添加成功！" << endl;
		cout << "是否继续添加? Y/N" << endl;
	}

	inout.open("List.txt", ios::app);
	if (inout.fail())
	{
		cout  << "打不开 List 文件！" << endl;
		return;
	}
	for (int i = oldsize; i <list.size(); ++i)
	{
			inout << list[i].GetComID() << ' ' << list[i].GetComName() << ' ' << list[i].GetComPrice() << endl;
	}
	inout.close();
	return;
}


void Seller::CancelCom(vector<Commodity>& list)
{
	cout << "下架商品? Y/N" << endl;
	string ch;
	vector<Commodity>::iterator it = list.begin();
	while (cin >> ch)
	{
		it = list.begin();
		if (ch == "N" || ch == "n")
			break;
		if (ch != "Y" && ch != "y")
		{
			cout << "输入错误，请重新输入!" << endl;
			continue;
		}

		cout << "所有商品 :" << endl;
		cout << setw(20) << "商品编号" << setw(20) << "商品名称" << setw(20) << "商品价格" << endl;
		for (int i = 0; i < list.size(); ++i)
		{
			list[i].Print();
		}
		cout << "请输入要下架的商品编号：";
		string str;
		cin >> str;
		int i = 0;
		for (i = 0; i < list.size(); ++i)
		{
			if (list[i].GetComID() == str)
			{
				list.erase(it + i);
				cout << "商品下架成功！" << endl;
				cout << "是否继续下架商品? Y/N" << endl;
				break;
			}
		}

		if (i == list.size())
		{
			cout << "没有该商品！" << endl;
			cout << "是否继续下架商品? Y/N" << endl;
		}
	}

	inout.open("List.txt", ios::out);
	if (inout.fail())
	{
		cout << "打不开 List 文件！" << endl;
		return;
	}
	for (int i = 0; i < list.size(); ++i)
	{
		inout << list[i].GetComID() << ' ' << list[i].GetComName() << ' ' << list[i].GetComPrice() << endl;
	}
	inout.close();
}



//卖家查询订单 
void Seller::InquireOrder(vector<Order>& order)
{
	if (order.size() == 0)
	{
		cout << "没有订单！" << endl;
		return;
	}
	cout << "这是订单！" << endl;
	cout << setw(7) << "商品编号" << setw(10) << "商品名称" << setw(6) << "商品价格" << setw(4) << "购买数量" << setw(8) << "客户姓名" << setw(8) << "联系电话" << setw(12) << "地址";
	cout << setw(15) << "日期" << endl;
	for (int i = 0; i < order.size(); ++i)
	{
		order[i].Print();
	}
	return;
}



void Seller::SetPassword(string password)
{
	_password = password;
}

string Seller::GetPassword()
{
	return _password;
}



Buyer::Buyer()
{
	_name = "no";
	_adress = "no";
}

string Buyer::GetName()
{
	return _name;
}

void Buyer::BookOrder(vector<Commodity>& list)
{
	int oldsize = _myOrder.size();
	int m = 0, appNum = 0;
	bool can = 1;
	if (!list.size())
	{
		cout << "抱歉，没有可购买的商品!" << endl;
		return;
	}
	cout << "这是全部的商品 :" << endl;
	cout << setw(20) << "商品编号" << setw(20) << "商品名称" << setw(20) << "价格" << endl;
	for (int i = 0; i < list.size(); ++i)
	{
		list[i].Print();
	}
	cout << "1.购买商品" << setw(20) << "2.返回" << endl;
	int n;
	while (cin >> n)
	{
		can = 1;
		if (n == 2) 
			break;
		cout << "请输入商品编号：";
		string str;
		cin >> str;
		int i = 0;
		for ( i = 0; i < list.size(); ++i)
		{
			if (list[i].GetComID() == str)
			{
				_myOrder.push_back(Order(list[i], m));
				break;
			}
		}
		if (i == list.size())
		{
			cout << "没有您要购买的商品!" << endl;
			cout << "1.继续购买" << setw(20) << "2.返回" << endl;
			can = 0;
		}
		if (!can)
			continue;
		appNum++;
		cout  << "请输入您要购买的数量：";
		cin >> m;
		_myOrder[_myOrder.size() - 1].SetNum(m);
		cout << "1.继续购买" << setw(20) << "2.返回" << endl;
	}

	if (appNum == 0)
	{
		cout << endl << "您没有购买新商品！" << endl;
		return;
	}

	cout << "这是您已购买的商品：" << endl;
	cout << setw(10) << "商品编号" << setw(10) << "商品名称" << setw(10) << "商品价格" << setw(10) << "购买数量" << endl;
	for (int i = 0; i < _myOrder.size(); ++i)
	{
		_myOrder[i].Print();
	}

	if (_name == "no" || _adress == "no")
	{
		cout << "请输入您的姓名：";
		cin >> _name;
		cout << "请输入您的派送地址：";
		cin >> _adress;
		cout << "请输入您的联系电话：";
		cin >> _phone;
	}
	cout << "请输入您期望的派送时间：" << endl;
	cout << "例如 2013/5/2 14 (year/month/day hour) : " << endl;
	char ch;
	int year, month, day, hour;
	cin >> year >> ch >> month >> ch >> day >> hour;
	_sendDate.SetYear(year);
	_sendDate.SetMonth(month);
	_sendDate.SetDay(day);
	_sendDate.SetHour(hour);


	for (int i = oldsize; i < _myOrder.size(); ++i)
	{
		_myOrder[i].SetCustomerName(_name);
		_myOrder[i].SetAdress(_adress);
		_myOrder[i].SetPhone(_phone);
		_myOrder[i].SetSendDate(_sendDate);
	}

	inout.open("order.txt", ios::app);
	if (inout.fail())
	{
		cout << endl << "The system can't find the file!" << endl;
		return;
	}
	for (int i = oldsize; i < _myOrder.size(); ++i)
	{
		Date date = _myOrder[i].GetSendDate();
		inout << _myOrder[i].GetComID() << ' ' << _myOrder[i].GetComName() << ' ' << _myOrder[i].GetComPrice() << ' ' << _myOrder[i].GetNum() << endl;
		inout << _myOrder[i].GetCustomerName() << ' ' << _myOrder[i].GetAdress() << ' ' << _myOrder[i].GetPhone() << endl;
		inout << date.GetYear() << ' ' << date.GetMonth() << ' ' << date.GetDay() << ' ' << date.GetHour() << ' ' << _myOrder[i].GetState() << endl;
	}
	inout.close();
}



void Buyer::InquireOrder()
{
	if (_myOrder.size() == 0)
	{
		cout << "您什么都没有买！" << endl;
		return;
	}
	cout << "这是您购买的商品 :" << endl;
	cout << setw(10) << "商品编号" << setw(10) << "商品名称" << setw(10) << "商品价格" << setw(10) << "购买数量" << setw(10) << "客户姓名" << setw(15) << "联系电话" << setw(15) << "地址";
	cout << setw(15) << "日期" << endl;
	for (int i = 0; i < _myOrder.size(); ++i)
	{
		_myOrder[i].Print();
	}
}


//买家取消订单 
void Buyer::ModifyOrder()
{
	if (_myOrder.size() == 0)
	{
		cout << "您什么都没有买！" << endl;
		return;
	}
	cout << "这是您购买的商品 :" << endl;
	cout << setw(10) << "商品编号" << setw(10) << "商品名称" << setw(10) << "商品价格" << setw(10) << "购买数量" << setw(10) << "客户姓名" << setw(15) << "联系电话" << setw(15) << "地址";
	cout << setw(15) << "日期" << endl;
	for (int i = 0; i < _myOrder.size(); ++i)
	{
		_myOrder[i].Print();
	}
	cout << "1.继续" << setw(20) << "2.返回" << endl;
	string str;
	while (cin >> str)
	{
		if (str == "2")
			break;
		if (str != "1")
		{
			cout << "输入错误!" << endl;
			cout  << "1.继续" << setw(20) << "2.返回" << endl;
			continue;
		}
		cout << "请输入您要取消的商品编号 : ";
		cin >> str;
		vector<Order>::iterator it = _myOrder.begin();
		int i = 0;
		for (i = 0; i < _myOrder.size(); ++i)
		{
			if (_myOrder[i].GetComID() == str)
			{
				_myOrder.erase(it + i);
			}
		}
		if (i == _myOrder.size())
		{
			cout << "1.继续" << setw(20) << "2.返回" << endl;
		}
		else
		{
			cout << "取消成功！" << endl;
			cout << "1.继续" << setw(20) << "2.返回" << endl;
		}
	}

	//将更新的订单写入文件 
	inout.open("order.txt", ios::out);
	if (inout.fail())
	{
		cout << "The system can't find the file!" << endl;
		return;
	}
	for (int i = 0; i < _myOrder.size(); ++i)
	{
		Date date = _myOrder[i].GetSendDate();
		inout << _myOrder[i].GetComID() << ' ' << _myOrder[i].GetComName() << ' ' << _myOrder[i].GetComPrice() << ' ' << _myOrder[i].GetNum() << endl;
		inout << _myOrder[i].GetCustomerName() << ' ' << _myOrder[i].GetAdress() << ' ' << _myOrder[i].GetPhone() << endl;
		inout << date.GetYear() << ' ' << date.GetMonth() << ' ' << date.GetDay() << ' ' << date.GetHour() << ' ' << _myOrder[i].GetState() << endl;
	}
	inout.close();
}