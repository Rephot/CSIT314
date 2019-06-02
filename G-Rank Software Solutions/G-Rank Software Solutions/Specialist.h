#ifndef SPECIALIST_H
#define SPECIALIST_H

//create a roadside assistance professional account{
//	bank account details
//	preferred area of operation
//	generated identifier
//	based on user creation for login account
//}
//create a roadside assistance professional account{
//rating out of 10 ?
//reveiw description(max char length ? )
//customer username / name
//pulls request identifier
//pulls customer identifier
//pulls specialist identifier
//}

#include "User.h"
#include <vector>
#include "ServiceRequest.h"
//#include"common.h"

using namespace std;

//class User;

class Specialist : public User{
public:
	Specialist();
	Specialist(string, string, string, string, string, string, int);
	Specialist(string, string, string, string, string, string, string, string, string, string, string, string);
	void viewRequests();
	void save();
	void selectRequest(int);
	void addArea(int);
	void returnUser();
	static vector<vector<ServiceRequest>> available;
	string specialistID;
	Specialist* load();

private:
	// bankAccountClass details;
	string bsb, account_num, account_name, qualification_num;
	vector<int> operationalAreas;
};
#endif
