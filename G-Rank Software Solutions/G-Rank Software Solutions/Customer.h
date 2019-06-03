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
	Customer(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string);
	static Customer* load();
	static vector<Customer> GRSSload();
	void returnUser();
	void saveCustomer();
	string custID;//C: type can be changed later
	string returnSubFlag();
	string getUserName();
private:
	string sub_flag, card_num, security_code, expiry, car_year, car_make, car_model, car_shape, car_colour, car_engine_size;
};

#endif