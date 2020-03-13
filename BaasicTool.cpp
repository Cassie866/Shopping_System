#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "BasicTool.h"
using namespace std;

Date::Date(int year, int month, int day, int hour)
	:_year(year), _month(month), _day(day), _hour(hour)
{}

bool Date::operator==(Date& date)
{
	if (date._year == _year && date._month == _month && date._day == _day && date._hour == _hour)
		return true;
	else
		return false;
}

int Date::GetYear()
{
	return _year;
}

int Date::GetMonth()
{
	return _month;
}

int Date::GetDay()
{
	return _day;
}

int Date::GetHour()
{
	return _hour;
}

void Date::SetYear(int year)
{
	_year = year;
}

void Date::SetMonth(int month)
{
	_month = month;
}

void Date::SetDay(int day)
{
	_day = day;
}

void Date::SetHour(int hour)
{
	_hour = hour;
}

void Date::Print()
{
	cout << _year << '/' << _month << '/' << _day << "-" << _hour << 'h';
}





List::List(string name, string id, double price)
	:_comName(name), _comID(id), _comPrice(price)
{}

string List::GetComName()
{
	return _comName;
}

string List::GetComID()
{
	return _comID;
}

double List::GetComPrice()
{
	return _comPrice;
}

void List::SetComName(string name)
{
	_comName = name;
}

void List::SetComID(string id)
{
	_comID = id;
}

void List::SetComPrice(double price)
{
	_comPrice = price;
}

void List::Print()
{
	cout << setw(20) << _comID << setw(20) << _comName << setw(20) << _comPrice << endl;
}












Order::Order()
{
	_state = true;
	_num = 0;
}

Order::Order(string dishName, string dishID, double price, string customerName, string adress, string phone, Date date)
	:List(dishName, dishID, price), _sendDate(date)
{
	_customerName = customerName;
	_adress = adress;
	_phone = phone;
	_state = true;
	_num = 0;
}

Order::Order(string dishName, string dishID, double price)
	: List(dishName, dishID, price)
{
	_state = true;
	_num = 0;
}

Order::Order(List m, int n)
	: List(m), _num(n)
{
	_state = true;
}

//const bool Order::operator==(Order& order)
//{
//	if (order._dishID != _dishID) return false;
//	if (order._dishName != _dishName) return false;
//	if (order._customerName != _customerName) return false;
//	if (order._phone != _phone) return false;
//	if (order._adress != _adress) return false;
//	if (!(order._bookDate == _bookDate)) return false;
//	return true;
//}

string Order::GetCustomerName()
{
	return _customerName;
}

string Order::GetAdress()
{
	return _adress;
}

string Order::GetPhone()
{
	return _phone;
}

Date Order::GetSendDate()
{
	return _sendDate;
}

bool Order::GetState()
{
	return _state;
}

int Order::GetNum()
{
	return _num;
}

bool Order::SetCustomerName(string customerName)
{
	if (!_state)
	{
		return false;
	}
	_customerName = customerName;
	return true;
}

bool Order::SetAdress(string adress)
{
	if (!_state)
	{
		return false;
	}
	_adress = adress;
	return true;
}

bool Order::SetPhone(string phone)
{
	if (!_state)
	{
		return false;
	}
	_phone = phone;
	return true;
}

void Order::SetState()
{
	_state = false;
}

bool Order::SetSendDate(Date bookDate)
{
	if (!_state)
	{
		return false;
	}
	_sendDate = bookDate;
	return true;
}

bool Order::SetNum(int num)
{
	if (_state)
	{
		return false;
	}
	_num = num;
	return true;
}

void Order::Print()
{
	cout << setw(7) << _comID << setw(10) << _comName<< setw(6) << _comPrice << setw(4) << GetNum();
	cout << setw(8) << _customerName << setw(8) << _phone << setw(12) << _adress;
	GetSendDate().Print();
	if (_state)
	{
		cout << setw(10) << "New" << endl;
	}
	else
	{
		cout << setw(10) << "Approved" << endl;
	}
}