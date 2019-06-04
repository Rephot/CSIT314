#ifndef SPECIALIST_H
#define SPECIALIST_H

#include <vector>
#include <set>

#include "User.h"
#include "ServiceRequest.h"

using namespace std;

class Specialist : public User{
public:
	Specialist();
	Specialist(string, string, string, string, string, string, int);
	Specialist(string, string, string, string, string, string, string, string, string, string, string, string, set<string>);
	Specialist(string, string, string, string, string, string, string, string, string, string, string, string);
	void viewRequests();
	void save();
	void selectRequest(int);
	void addArea(string);
	void returnUser();
	static vector<vector<ServiceRequest>> available;
	static Specialist* load();
	static vector<Specialist> GRSSload();
	set<string> operationalAreas;
	string specialistID;
	string getQualNum();
	string getBSB();
	string getAccNum();
	string getAccName();

private:
	string bsb, account_num, account_name, qualification_num, licenseNumber;
};
#endif
