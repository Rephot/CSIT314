#include<iostream>
#include<ctime>
#include<cstring>
#include "User.h"

User::User(string uname, string pwd) {
	username = uname;
	password = pwd;
}

bool User::checkPassword(string pwd) {
	if (this->password == pwd) {
		return true;
	}
	else {
		return false;
	}
}

void User::userDetails(string name, string location, string number, Car car) {
	this->name = name;
	this->location = location;
	phNumber = number;
	this->car = car;
}


void User::returnUser() {
	cout << "Username: " << username << endl;
	cout << "Password: " << password << endl;
	cout << "Full Name: " << name << endl;
	cout << "location: " << location << endl;
	cout << "Phone Number: " << phNumber << endl;

}