#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

//credit card details for subsription payments and optionally service transaction

#include"User.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Administrator : public User {
public:
	Administrator();
	Administrator(int, string, string, string, string, time_t, string);
	void returnUser();
	void saveAdministrator();
	int adminID;//C: type can be changed later
private:
	// BankCard cardDetails;
};
#endif
