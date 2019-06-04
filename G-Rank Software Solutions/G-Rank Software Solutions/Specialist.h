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
	void save();
	void selectRequest(int);
	void addArea(string);
	void returnUser();
	string getQualification();
	string getBsb();
	string getAccount_num();
	string getAccount_name();
	void setQualification(string);
	void setBsb(string);
	void setAccount_num(string);
	void setAccount_name(string);
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
	string bsb, account_num, account_name, qualification_num;
};
#endif
