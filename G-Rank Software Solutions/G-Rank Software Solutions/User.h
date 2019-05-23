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
	bool setPassword(string);
	void returnUser();
	string getUserName();
	string getPassword();
	string getFullName();
	string getFirstName();
	string getLastName();
	time_t getDOB();
	string getNumber();
protected:
	string username, password, fName, lName, phNumber;
	time_t DOB;
};

#endif