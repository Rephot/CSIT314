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
	Administrator(string, string, string, string, string, string);
	static vector<Administrator> loadAdministrators();
	void returnUser();
	void saveAdministrator();
	static void saveAdministratorAll(vector<Administrator>);
	void viewTransactions(vector<Transaction>);
	void suspendUser(string, vector<Customer>);
	void suspendUser(string, vector<Specialist>);
	void viewUsers(vector<Specialist>, vector<Customer>);

	string adminID;//C: type can be changed later
private:
	// BankCard cardDetails;
};
#endif
