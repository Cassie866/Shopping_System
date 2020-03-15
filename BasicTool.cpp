#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "BasicTool.h"
using namespace std;

Date::Date(int year, int month, int day, int hour)
	:_year(year), _month(month), _day(day), _hour(hour)
{}


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
	cout << _year << '/' << _month << '/' << _day << "-" << _hour << 'h' << endl;
}



Commodity::Commodity(string name, string id, double price)
	:_comName(name), _comID(id), _comPrice(price)
{}

string Commodity::GetComName()
{
	return _comName;
}

string Commodity::GetComID()
{
	return _comID;
}

double Commodity::GetComPrice()
{
	return _comPrice;
}

void Commodity::SetComName(string name)
{
	_comName = name;
}

void Commodity::SetComID(string id)
{
	_comID = id;
}

void Commodity::SetComPrice(double price)
{
	_comPrice = price;
}

void Commodity::Print()
{
	cout << setw(20) << _comID << setw(20) << _comName << setw(20) << _comPrice << endl;
}




Order::Order()
{
	_num = 0;
}

Order::Order(string comName, string comID, double comPrice, string customerName, string adress, string phone, Date date)
	:Commodity(comName, comID, comPrice), _sendDate(date)
{
	_customerName = customerName;
	_adress = adress;
	_phone = phone;
	_num = 0;
}

Order::Order(string comName, string comID, double comPrice)
	: Commodity(comName, comID, comPrice)
{
	_num = 0;
}

Order::Order(Commodity m, int n)
	: Commodity(m), _num(n)
{}


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

int Order::GetNum()
{
	return _num;
}

bool Order::SetCustomerName(string customerName)
{
	_customerName = customerName;
}

bool Order::SetAdress(string adress)
{
	_adress = adress;
	return true;
}

bool Order::SetPhone(string phone)
{
	_phone = phone;
	return true;
}


bool Order::SetSendDate(Date sendDate)
{
	_sendDate = sendDate;
	return true;
}

bool Order::SetNum(int num)
{
	_num = num;
	return true;
}

void Order::Print()
{
	cout << setw(10) << _comID << setw(10) << _comName<< setw(10) << _comPrice << setw(10) << GetNum() << setw(10) << _customerName << setw(15) << _phone << setw(15) << _adress;
	GetSendDate().Print();

}