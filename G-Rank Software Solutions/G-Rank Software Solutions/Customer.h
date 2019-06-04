#ifndef CUSTOMER_H
#define CUSTOMER_H

//credit card details for subsription payments and optionally service transaction

#include <fstream>
#include <iostream>
#include <vector>

#include "User.h"

using namespace std;

class Customer : public User{
public:
	Customer();
	Customer(int, string, string, string, string, time_t, string);
	Customer(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string);
	static Customer* load();
	static vector<Customer> GRSSload();
	void returnUser();
	void saveCustomer();
	static void saveCustomerAll(vector<Customer>);
	string custID;//C: type can be changed later
	string returnSubFlag();
	string getCardNumber();
	string getCardSec();
	string getCardExpiry();
	string getCarYear();
	string getCarMake();
	string getCarModel();
	string getCarShape();
	string getCarEngineSize();
	string getCarColour();
	void setSubFlag(string);
	void setCardNumber(string);
	void setCardSec(string);
	void setCardExpiry(string);
	void setCarYear(string);
	void setCarMake(string);
	void setCarModel(string);
	void setCarShape(string);
	void setCarEngineSize(string);
	void setCarColour(string);
private:
	string sub_flag, card_num, security_code, expiry, licPlate, car_year, car_make, car_model, car_shape, car_colour, car_engine_size;
};

#endif