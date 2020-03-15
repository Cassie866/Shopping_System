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
	cout << "�������Ʒ?  Y/N" << endl;
	string ch;
	while (cin >> ch)
	{
		if (ch == "N" || ch == "n")
		{
			break;
		}
		if (ch != "Y" && ch != "y")
		{
			cout << "����������������룺" << endl;
			continue;
		}
		cout << "��������Ʒ���ƣ�";
		string str;
		cin >> str;
		Commodity com;
		com.SetComName(str);
		cout << "��������Ʒ��ţ�";
		cin >> str;
		com.SetComID(str);
		cout << "��������Ʒ�۸�";
		double d;
		cin >> d;
		com.SetComPrice(d);
		list.push_back(com);
		cout << "��Ʒ��ӳɹ���" << endl;
		cout << "�Ƿ�������? Y/N" << endl;
	}

	inout.open("List.txt", ios::app);
	if (inout.fail())
	{
		cout  << "�򲻿� List �ļ���" << endl;
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
	cout << "�¼���Ʒ? Y/N" << endl;
	string ch;
	vector<Commodity>::iterator it = list.begin();
	while (cin >> ch)
	{
		it = list.begin();
		if (ch == "N" || ch == "n")
			break;
		if (ch != "Y" && ch != "y")
		{
			cout << "�����������������!" << endl;
			continue;
		}

		cout << "������Ʒ :" << endl;
		cout << setw(20) << "��Ʒ���" << setw(20) << "��Ʒ����" << setw(20) << "��Ʒ�۸�" << endl;
		for (int i = 0; i < list.size(); ++i)
		{
			list[i].Print();
		}
		cout << "������Ҫ�¼ܵ���Ʒ��ţ�";
		string str;
		cin >> str;
		int i = 0;
		for (i = 0; i < list.size(); ++i)
		{
			if (list[i].GetComID() == str)
			{
				list.erase(it + i);
				cout << "��Ʒ�¼ܳɹ���" << endl;
				cout << "�Ƿ�����¼���Ʒ? Y/N" << endl;
				break;
			}
		}

		if (i == list.size())
		{
			cout << "û�и���Ʒ��" << endl;
			cout << "�Ƿ�����¼���Ʒ? Y/N" << endl;
		}
	}

	inout.open("List.txt", ios::out);
	if (inout.fail())
	{
		cout << "�򲻿� List �ļ���" << endl;
		return;
	}
	for (int i = 0; i < list.size(); ++i)
	{
		inout << list[i].GetComID() << ' ' << list[i].GetComName() << ' ' << list[i].GetComPrice() << endl;
	}
	inout.close();
}



//���Ҳ�ѯ���� 
void Seller::InquireOrder(vector<Order>& order)
{
	if (order.size() == 0)
	{
		cout << "û�ж�����" << endl;
		return;
	}
	cout << "���Ƕ�����" << endl;
	cout << setw(7) << "��Ʒ���" << setw(10) << "��Ʒ����" << setw(6) << "��Ʒ�۸�" << setw(4) << "��������" << setw(8) << "�ͻ�����" << setw(8) << "��ϵ�绰" << setw(12) << "��ַ";
	cout << setw(15) << "����" << endl;
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
		cout << "��Ǹ��û�пɹ������Ʒ!" << endl;
		return;
	}
	cout << "����ȫ������Ʒ :" << endl;
	cout << setw(20) << "��Ʒ���" << setw(20) << "��Ʒ����" << setw(20) << "�۸�" << endl;
	for (int i = 0; i < list.size(); ++i)
	{
		list[i].Print();
	}
	cout << "1.������Ʒ" << setw(20) << "2.����" << endl;
	int n;
	while (cin >> n)
	{
		can = 1;
		if (n == 2) 
			break;
		cout << "��������Ʒ��ţ�";
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
			cout << "û����Ҫ�������Ʒ!" << endl;
			cout << "1.��������" << setw(20) << "2.����" << endl;
			can = 0;
		}
		if (!can)
			continue;
		appNum++;
		cout  << "��������Ҫ�����������";
		cin >> m;
		_myOrder[_myOrder.size() - 1].SetNum(m);
		cout << "1.��������" << setw(20) << "2.����" << endl;
	}

	if (appNum == 0)
	{
		cout << endl << "��û�й�������Ʒ��" << endl;
		return;
	}

	cout << "�������ѹ������Ʒ��" << endl;
	cout << setw(10) << "��Ʒ���" << setw(10) << "��Ʒ����" << setw(10) << "��Ʒ�۸�" << setw(10) << "��������" << endl;
	for (int i = 0; i < _myOrder.size(); ++i)
	{
		_myOrder[i].Print();
	}

	if (_name == "no" || _adress == "no")
	{
		cout << "����������������";
		cin >> _name;
		cout << "�������������͵�ַ��";
		cin >> _adress;
		cout << "������������ϵ�绰��";
		cin >> _phone;
	}
	cout << "������������������ʱ�䣺" << endl;
	cout << "���� 2013/5/2 14 (year/month/day hour) : " << endl;
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
		cout << "��ʲô��û����" << endl;
		return;
	}
	cout << "�������������Ʒ :" << endl;
	cout << setw(10) << "��Ʒ���" << setw(10) << "��Ʒ����" << setw(10) << "��Ʒ�۸�" << setw(10) << "��������" << setw(10) << "�ͻ�����" << setw(15) << "��ϵ�绰" << setw(15) << "��ַ";
	cout << setw(15) << "����" << endl;
	for (int i = 0; i < _myOrder.size(); ++i)
	{
		_myOrder[i].Print();
	}
}


//���ȡ������ 
void Buyer::ModifyOrder()
{
	if (_myOrder.size() == 0)
	{
		cout << "��ʲô��û����" << endl;
		return;
	}
	cout << "�������������Ʒ :" << endl;
	cout << setw(10) << "��Ʒ���" << setw(10) << "��Ʒ����" << setw(10) << "��Ʒ�۸�" << setw(10) << "��������" << setw(10) << "�ͻ�����" << setw(15) << "��ϵ�绰" << setw(15) << "��ַ";
	cout << setw(15) << "����" << endl;
	for (int i = 0; i < _myOrder.size(); ++i)
	{
		_myOrder[i].Print();
	}
	cout << "1.����" << setw(20) << "2.����" << endl;
	string str;
	while (cin >> str)
	{
		if (str == "2")
			break;
		if (str != "1")
		{
			cout << "�������!" << endl;
			cout  << "1.����" << setw(20) << "2.����" << endl;
			continue;
		}
		cout << "��������Ҫȡ������Ʒ��� : ";
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
			cout << "1.����" << setw(20) << "2.����" << endl;
		}
		else
		{
			cout << "ȡ���ɹ���" << endl;
			cout << "1.����" << setw(20) << "2.����" << endl;
		}
	}

	//�����µĶ���д���ļ� 
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