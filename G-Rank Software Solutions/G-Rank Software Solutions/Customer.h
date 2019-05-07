// inherits User
#ifndef CUSTOMER_H
#define CUSTOMER_H

//credit card details for subsription payments and optionally service transaction
//(ask if there should be the option to pay cash(yes that means someone would be carrying around a lot of cash))
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
