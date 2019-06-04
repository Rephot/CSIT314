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
//#include "Transaction.h"
//#include"common.h"

using namespace std;

//class User;
//class Transaction;

class Specialist : public User{
public:
	Specialist();
	Specialist(string, string, string, string, string, string, int);
	Specialist(string, string, string, string, string, string, string, string, string, string, string, string, vector<string>);
	Specialist(string, string, string, string, string, string, string, string, string, string, string, string);
	//vector<Transaction> viewRequests(vector<Transaction>);
	void save();
	void selectRequest(int);
	void addArea(string);
	void returnUser();
	string getQualification();
	string getBsb();
	string getAccount_num();
	string getAccount_name();
	static vector<vector<ServiceRequest>> available;
	static Specialist* load();
	static vector<Specialist> GRSSload();
	vector<string> operationalAreas;
	string specialistID, callOutFee;

private:
	string bsb, account_num, account_name, qualification_num;
};
#endif
