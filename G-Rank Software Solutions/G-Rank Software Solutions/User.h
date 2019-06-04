#ifndef USER_H
#define USER_H

#include<iostream>
#include<ctime>
#include<cstring>
#include<string>

using namespace std;

class User{
public:
	User();
	User(string, string, string, string, time_t, string);
	User(string, string, string, string, string, string, string);
	void setPassword(string);
	void returnUser();
	string getUserName();
	string getPassword();
	string getFullName();
	string getFirstName();
	string getLastName();
	time_t getDOB();
	string getNumber();
	string getEmail();
	string getLicenseNumber();
	void setUserName(string);
	void setFirstName(string);
	void setLastName(string);
	void setNumber(string);
	void setEmail(string);
	void setLicenseNumber(string);
protected:
	string username, password, fName, lName, licenseNumber, phNumber, email;
	time_t DOB;
};

#endif