#ifndef USER_H
#define USER_H

#include<iostream>
#include<ctime>
#include<cstring>
#include"Car.h"

using namespace std;

class User {
public:
	User(string, string, string, string, time_t, string);
	string username;
	bool setPassword(string);
	void returnUser();
	string getPassword();
	string getFullName();
	string getFirstName();
	string getLastName();
	time_t getDOB();
	string getNumber();
	User();


protected:
	string password, fName, lName, phNumber;
	time_t DOB;
};
#endif
