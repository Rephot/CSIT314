#ifndef SPECIALIST_H
#define SPECIALIST_H

// inherits user

//create a roadside assistance professional account{
//	bank account details
//	preferred area of operation
//	generated identifier
//	based on user creation for login account
//}

#include<string>
#include"User.h"

using namespace std;

//class User;

class Specialist : public User{
public:
	Specialist();
	Specialist(string, string, string, string, time_t, string, string, int);
	void viewRequests();
	void selectRequest();
private:
	// bankAccountClass details;
	string operationalArea;
	int specialistID;
	// User loginAccount;
};
#endif
