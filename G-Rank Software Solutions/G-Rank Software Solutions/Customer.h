#ifndef CUSTOMER_H
#define CUSTOMER_H

//credit card details for subsription payments and optionally service transaction

#include"User.h"

using namespace std;

class Customer : public User{
public:
	Customer();
	Customer(int, string, string, string, string, time_t, string);
	void returnUser();
	void saveCustomer();
	int custID;//C: type can be changed later
private:
	// BankCard cardDetails;
};

#endif