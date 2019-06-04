#include"Specialist.h"

#include <fstream>
#include <iostream>

using namespace std;

Specialist::Specialist() {}

Specialist::Specialist(string uname, string pwd, string fname, string lname, string number, string area, int specID) 
{
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	phNumber = number;
	specialistID = specID;
}

Specialist::Specialist(string specID, string uname, string pwd, string fname, string lname, string license_num, string phnumber, string email, string qualification_num, string bsb, string acc_num, string acc_name, set<string> opArea) {
	specialistID = specID;
	username = uname;
	password = pwd;
	this->fName = fname;
	this->lName = lname;
	licenseNumber = license_num;
	this->phNumber = phnumber;
	this->email = email;
	this->qualification_num = qualification_num;
	this->bsb = bsb;
	account_num = acc_num;
	account_name = acc_name;
	operationalAreas = opArea;
}

Specialist::Specialist(string specID, string uname, string pwd, string fname, string lname, string license_num, string phnumber, string email, string qualification_num, string bsb, string acc_num, string acc_name) {
	specialistID = specID;
	username = uname;
	password = pwd;
	this->fName = fname;
	this->lName = lname;
	licenseNumber = license_num;
	this->phNumber = phnumber;
	this->email = email;
	this->qualification_num = qualification_num;
	this->bsb = bsb;
	account_num = acc_num;
	account_name = acc_name;
}

void Specialist::setQualification(string qualification_num) {
	this->qualification_num = qualification_num;
}

void Specialist::setBsb(string bsb) {
	this->bsb = bsb;
}

void Specialist::setAccount_num(string account_num) {
	this->account_num = account_num;
}

void Specialist::setAccount_name(string account_name) {
	this->account_name = account_name;
}

vector<Specialist> Specialist::GRSSload() {
	vector<Specialist> specialists;
	string line,  specID,  uname,  pwd,  fname,  lname,  license_num,  phnumber,  email,  qualification_num,  bsb,  acc_num,  acc_name, areas;

	// get existing users from file
	ifstream inFile;
	inFile.open("Specialists.csv");
	int i = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, specID, '`'))
		{
			getline(inFile, uname, '`');
			getline(inFile, pwd, '`');
			getline(inFile, fname, '`');
			getline(inFile, lname, '`');
			getline(inFile, license_num, '`');
			getline(inFile, phnumber, '`');
			getline(inFile, email, '`');
			getline(inFile, qualification_num, '`');
			getline(inFile, areas, '`');
			getline(inFile, bsb, '`');
			getline(inFile, acc_num, '`');
			getline(inFile, acc_name);

			specialists.push_back(Specialist(specID, uname, pwd, fname, lname, license_num, phnumber, email, qualification_num, bsb, acc_num, acc_name));
			std::stringstream ss(areas);
			std::string token;
			while (std::getline(ss, token, '|')) {
				specialists.back().operationalAreas.insert(token);
			}
		}
		inFile.close();
	}

	return specialists;
}

void Specialist::save() {
	ofstream outFile;
	outFile.open("Specialists.csv", ios_base::app);

	outFile << specialistID << "`"
		<< username << "`"
		<< password << "`"
		<< fName << "`"
		<< lName << "`"
		<< licenseNumber << "`"
		<< phNumber << "`"
		<< email << "`"
		<< qualification_num << "`";

	for (std::set<string>::iterator it = operationalAreas.begin(); it != operationalAreas.end(); ++it) {
		if (it != operationalAreas.begin()) outFile << "|";
		outFile << *it;
	}

	outFile << "`"
		<< bsb << "`"
		<< account_num << "`"
		<< account_name << "\n";
	outFile.close();
}

void Specialist::saveAll(vector<Specialist> inSpec) {
	ofstream outFile;
	outFile.open("Specialists.csv");

	vector<Specialist>::iterator it = inSpec.begin();
	if (outFile.is_open()) {
		while (it != inSpec.end())
		{
			outFile << it->specialistID << "`"
				<< it->username << "`"
				<< it->password << "`"
				<< it->fName << "`"
				<< it->lName << "`"
				<< it->licenseNumber << "`"
				<< it->phNumber << "`"
				<< it->email << "`"
				<< it->qualification_num << "`";

			for (std::set<string>::iterator itr = it->operationalAreas.begin(); itr != it->operationalAreas.end(); ++itr) {
				if (itr != it->operationalAreas.begin()) outFile << "|";
				outFile << *itr;
			}

			outFile << "`"
				<< it->bsb << "`"
				<< it->account_num << "`"
				<< it->account_name << "\n";
			it++;
		}
	}
	outFile.close();
}

string Specialist::getQualNum()
{
	return qualification_num;
}

string Specialist::getBSB()
{
	return bsb;
}

string Specialist::getAccNum()
{
	return account_num;
}

string Specialist::getAccName()
{
	return account_name;
}