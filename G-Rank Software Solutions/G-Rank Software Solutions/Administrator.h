#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <fstream>
#include <iostream>
#include <string>

#include"User.h"
#include"Transaction.h"
#include"Customer.h"
#include"Specialist.h"

using namespace std;

class Administrator : public User {
public:
	Administrator();
	Administrator(string, string, string, string, string, string);
	static vector<Administrator> loadAdministrators();
	void saveAdministrator();
	static void saveAdministratorAll(vector<Administrator>);
	string adminID;
};
#endif
