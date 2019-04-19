#include<iostream>
#include<ctime>
#include<cstring>
#include "car.h"

using namespace std;

class User {
public:
	User(string, string);
	string username;
	bool checkPassword(string);
	void userDetails(string, string, string, Car);
	void returnUser();

private:
	string password, name, phNumber, location;
	Car car;
};