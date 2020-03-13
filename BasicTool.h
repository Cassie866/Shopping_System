#pragma once
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


class Date
{
public:
	Date(int year = 2020, int month = 3, int day = 1, int hour = 8);
	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	void SetYear(int year);
	void SetMonth(int month);
	void SetDay(int day);
	void SetHour(int hour);
	void Print();
private:
	int _year, _month, _day, _hour;
};



class Commodity
{
public:
	Commodity(string comName = "no", string comID = "no", double comPrice = 0.0);
	string GetComName();
	string GetComID();
	double GetComPrice();
	void SetComName(string comName);
	void SetComID(string comID);
	void SetComPrice(double comPrice);
	void Print();
protected:
	string _comName, _comID;
	double _comPrice;
};




class Order :public Commodity
{
public:
	Order();
	Order(string comName, string comID, double comPrice, string customerName, string adress, string phone, Date bookDate);
	Order(string comName, string comID, double comPrice);
	Order(Commodity, int num);
	string GetCustomerName();
	string GetAdress();
	string GetPhone();
	Date GetSendDate();
	bool GetState();
	int GetNum();
	bool SetCustomerName(string customerName);
	bool SetAdress(string adress);
	bool SetPhone(string phone);
	bool SetNum(int num);
	bool SetSendDate(Date sendDate);
	void SetState();
	void Print();
private:
	string _customerName, _adress, _phone;
	int _num;
	Date _sendDate;
	bool _state;
};