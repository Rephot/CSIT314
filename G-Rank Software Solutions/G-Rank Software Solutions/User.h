#include<iostream>
#include<ctime>
#include<cstring>
#include "car.h"

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


private:
	string password, fName, lName, phNumber;
	time_t DOB;
};