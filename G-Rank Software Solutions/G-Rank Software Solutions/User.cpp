#include"User.h"

User::User() {}

User::User(string uname, string pwd, string fname, string lname, string lNum, string number, string mail) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	licenseNumber = lNum;
	phNumber = number;
	email = mail;
}

string User::getUserName() {
	return username;
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

string User::getNumber() {
	return phNumber;
}

string User::getEmail() {
	return email;
}

string User::getLicenseNumber() {
	return licenseNumber;
}

void User::setUserName(string username) {
	this->username = username;
}

void User::setFirstName(string fName) {
	this->fName = fName;
}

void User::setLastName(string lName) {
	this->lName = lName;
}

void User::setNumber(string phNumber) {
	this->phNumber = phNumber;
}

void User::setEmail(string email) {
	this->email = email;
}

void User::setLicenseNumber(string licenseNumber) {
	this->licenseNumber = licenseNumber;
}

void User::setPassword(string pwd) {
	this->password = pwd;
}