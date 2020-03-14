#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "BasicTool.h"
#include "User.h"

using namespace std;

fstream finout;

vector<Order>allOrder;
vector<Commodity>allList;

Commodity InputList()
{
	Commodity com;
	string comID, comName;
	double price = -1;
	finout >> comID;
	if (comID == " " || comID == "\n")
	{
		com.SetComID("-1");
		return com;
	}
	finout >> comName >> price;
	if (price < 0 || price > 100000)
	{
		com.SetComID("-1");
		return com;
	}
	com.SetComID(comID);
	com.SetComName(comName);
	com.SetComPrice(price);
	return com;
}


//用于读取文件中的订单 
Order InputOrder()
{
	string comID, comName, name, adress, phone;
	double price = -1;
	int year, month, day, hour, modify, num;
	finout >> comID;
	if (comID == " " || comID == "\n")
	{
		Order order;
		order.SetComID("-1");
		return order;
	}
	finout >> comName >> price >> num >> name >> adress >> phone;
	if (price < 0 || price > 100000)
	{
		Order order;
		order.SetComID("-1");
		return order;
	}
	finout >> year >> month >> day >> hour >> modify;
	Date date(year, month, day, hour);
	Order order(comName, comID, price, name, adress, phone, date);
	order.SetNum(num);
	if (!modify)
		order.SetState();
	return order;
}

//卖家 
void SeviceForSeller()
{
	Seller seller;
	Order iOrder;
	Commodity iCom;
	string password;
	finout.open("password.txt", ios::in);
	if (finout.fail())
	{
		cout << endl << "The system can't find the file!" << endl;
		return;
	}
	finout >> password;
	finout.close();
	seller.SetPassword(password);
	cout << "请输入您的密码：";
	string str;
	int num = 5;
	cin >> str;
	while (num-- && str != seller.GetPassword())
	{
		cout << "密码错误，请重新输入：";
		cin >> str;
	}
	if (num <= 0)
	{
		cout << endl << "你已经错误输入5次！" << endl;
		return;
	}
	cout << setw(30) << "1. 增加商品" << setw(20) << "2. 下架商品" << endl;
	cout << setw(30) << "3. 查询订单" << setw(20) << "4.设置密码" << endl;
	cout<<setw(30) << "5.返回主菜单" << endl;
	cout << "请输入您要进行的操作：";
	int choice;
	while (cin >> choice)
	{
		if (choice == 5)
		{
			return;
		}
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 )
		{
			cout << setw(30) << "1. 增加商品" << setw(20) << "2. 下架商品" << endl;
			cout << setw(30) << "3. 查询订单" << setw(20) << "4.设置密码" << endl;
			cout << setw(30) << "5.返回主菜单" << endl;
			cout << "请输入您要进行的操作：";
			continue;
		}
		//从文件读取以初始化菜单信息和订单信息 
		allOrder.clear();
		finout.open("order.txt", ios::in);
		if (finout.fail())
		{
			cout << endl << "The system can't find the file!" << endl;
			break;
		}
		while (!finout.eof())
		{
			iOrder = InputOrder();
			if (iOrder.GetComID() == "-1") break;
			allOrder.push_back(iOrder);
		}
		finout.close();
		allList.clear();
		finout.open("List.txt", ios::in);
		if (finout.fail())
		{
			cout << endl << "The system can't find the file!" << endl;
			break;
		}
		while (!finout.eof())
		{
			iCom = InputList();
			if (iCom.GetComID() == "-1") break;
			allList.push_back(iCom);
		}
		finout.close();


		if (choice == 1)
			seller.AppendCom(allList);
		else if (choice == 2)
			seller.CancelCom(allList);
		else if (choice == 3)
			seller.InquireOrder(allOrder);
		else
		{
			cout  << "1.继续" << setw(20) << "2.返回" << endl;
			string str1, str2;
			while (cin >> str1)
			{
				if (str1 == "2")
					break;
				if (str1 != "1")
				{
					cout << "输入有误！" << endl;
					cout << "1.继续" << setw(20) << "2.返回" << endl;
					continue;
				}
				cout << "请输入您的密码";
				cin >> str1;
				if (str1 == seller.GetPassword())
					break;
				else
				{
					cout << endl << "密码错误！" << endl;
					cout << "1.继续" << setw(20) << "2.返回" << endl;
				}
			}
			if (str1 == "2")
			{
				cout << setw(30) << "1. 增加商品" << setw(20) << "2. 下架商品" << endl;
				cout << setw(30) << "3. 查询订单" << setw(20) << "4.设置密码" << endl;
				cout << setw(30) << "5.返回主菜单" << endl;
				cout << "请输入您要进行的操作：";
				continue;
			}
			cout  << "请输入您的新密码: ";
			cin >> str1;
			cout << endl << "再次输入您的新密码 :";
			cin >> str2;
		
			if (str1 == str2)
			{
				finout.open("password.txt", ios::out);
				if (finout.fail())
				{
					cout << endl << "The system can't find the file!" << endl;
					return;
				}
				finout << str1;
				finout.close();
				seller.SetPassword(str1);
				cout << endl << "密码设置成功！" << endl;
			}
			else
			{
				cout << endl << "两次输入不同，修改失败!" << endl;
			}
		}
		cout << setw(30) << "1. 增加商品" << setw(20) << "2. 下架商品" << endl;
		cout << setw(30) << "3. 查询订单" << setw(20) << "4.设置密码" << endl;
		cout << setw(30) << "5.返回主菜单" << endl;
		cout << "请输入您要进行的操作：";
	}
}




void SeviceForBuyer()
{
	Buyer ibuyer;
	Commodity iMenu;
	Order iOrder;
	cout << setw(20) << "1. 购买商品" << setw(20) << "2.查询订单" << endl;
	cout << setw(20) << "3. 修改订单" << setw(20) << "4.返回主菜单 " << endl;
	cout << "请输入要进行的操作：";
	int n;
	while (cin >> n)
	{
		if (n == 4)
			return;
		if (n != 1 && n != 2 && n != 3)
		{
			cout << endl << "请输入要进行的操作：";
			continue;
		}

		allOrder.clear();
		finout.open("order.txt", ios::in);
		if (finout.fail())
		{
			cout << endl << "The system can't find the file!" << endl;
			break;
		}
		while (!finout.eof())
		{
			iOrder = InputOrder();
			if (iOrder.GetComID() == "-1")
				break;
			allOrder.push_back(iOrder);
		}
		finout.close();
		allList.clear();
		finout.open("List.txt", ios::in);
		if (finout.fail())
		{
			cout << endl << "The system can't find the file!" << endl;
			break;
		}
		while (!finout.eof())
		{
			iMenu = InputList();
			if (iMenu.GetComID() == "-1")
				break;
			allList.push_back(iMenu);
		}
		finout.close();

		if (n == 1)
			ibuyer.BookOrder(allList);
		else if (n == 2)
			ibuyer.InquireOrder();
		else if (n == 3)
			ibuyer.ModifyOrder();
		cout << setw(20) << "1. 购买商品" << setw(20) << "2.查询订单" << endl;
		cout << setw(20) << "3. 修改订单" << setw(20) << "4.返回主菜单 " << endl;
		cout << "请输入要进行的操作：";
	}
}


void SystemMenu()
{
	cout << "欢迎使用购物系统" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "1.买家入口" << setw(15) << "2.卖家入口" << setw(15) << "3.退出系统" << endl;
	cout << "请输入您要进行的操作：";
}



int main()
{
	int n;
	bool success = 0;
	SystemMenu();
	while (cin >> n)
	{
		allOrder.clear();
		allList.clear();
		if (n == 3)
			break;
		if (n != 1 && n != 2)
		{
			SystemMenu();
			continue;
		}
		if (n == 1)
			SeviceForBuyer();
		else 
			SeviceForSeller();
		SystemMenu();
	}
	return 0;
}