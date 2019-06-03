#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

//credit card details for subsription payments and optionally service transaction

#include"User.h"
#include"Transaction.h"
#include"Customer.h"
#include"Specialist.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Administrator : public User {
public:
	Administrator();
	Administrator(int, string, string, string, string, time_t, string);
	static vector<Administrator> loadAdministrators();
	void returnUser();
	void saveAdministrator();
	void viewTransactions(vector<Transaction>);
	void suspendUser(string, vector<Customer>);
	void suspendUser(string, vector<Specialist>);

	int adminID;//C: type can be changed later
private:
	// BankCard cardDetails;
};
#endif
