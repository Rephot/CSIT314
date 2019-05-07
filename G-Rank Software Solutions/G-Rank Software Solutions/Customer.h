#ifndef CUSTOMER_H
#define CUSTOMER_H

//credit card details for subsription payments and optionally service transaction

#include"User.h"
using namespace std;

class Customer : public User{
public:
	Customer();
	Customer(string, string, string, string, time_t, string);
private:
	// BankCard cardDetails;
};
#endif
