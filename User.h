#pragma once
#pragma once
#include "BasicTool.h"
#include <vector>



class Seller 
{
public:
	Seller();
	void InquireOrder(vector<Order>& order);
	void AppendCom(vector<Commodity>& list);
	void CancelCom(vector<Commodity>& list);
	void SetPassword(string password);
	string GetPassword();
private:
	string _password;
};




class Buyer
{
public:
	Buyer();
	void BookOrder(vector<Commodity>& list);
	void ModifyOrder();
	void InquireOrder();
	string GetName();
private:
	vector<Order> _myOrder;
	string _name, _adress, _phone;
	Date _sendDate;
};



