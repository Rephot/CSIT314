#include<iostream>
#include<ctime>
#include<string>
#include "User.h"

User::User(string uname, string pwd, string fname, string lname, time_t dob, string number) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	DOB = dob;
	phNumber = number;
}

string User::getPassword() {
	return password;
}

string User::getFullName() {
	return fName + " " + lName;
}

string User::getFirstName() {
	return fName;
}

string User::getLastName() {
	return lName;
}

time_t User::getDOB() {
	return DOB;
}

string User::getNumber() {
	return phNumber;
}

bool User::setPassword(string pwd) {
	this->password == pwd;
	return true;
}

User::User() {
	username = "";
	password = "";
	fName = "";
	lName = "";
	DOB = 0;
	phNumber = "";
}

void User::returnUser() {
	cout << "Username: " << username << endl;
	cout << "Password: " << password << endl;
	cout << "Full Name: " << fName << " " << lName << endl;
	cout << "Date of Birth: " << DOB << endl;
	cout << "Phone Number: " << phNumber << endl;

}