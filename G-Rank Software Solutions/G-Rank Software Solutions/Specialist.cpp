#include"Specialist.h"

#include <fstream>
#include <iostream>

using namespace std;

vector <vector<ServiceRequest>> Specialist::available;
int total_specialists1;

Specialist::Specialist() {

}

Specialist::Specialist(string uname, string pwd, string fname, string lname, string number, string area, int specID) 
{
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	phNumber = number;
	//operationalArea = area;
	specialistID = specID;
}

Specialist::Specialist(string specID, string uname, string pwd, string fname, string lname, string license_num, string phnumber, string email, string qualification_num, string bsb, string acc_num, string acc_name) {
	specialistID = specID;
	username = uname;
	password = pwd;
	this->fName = fname;
	this->lName = lname;
	licenseNumber = license_num;
	this->phNumber = phnumber;
	emailAddress = email;
	this->qualification_num = qualification_num;
	this->bsb = bsb;
	account_num = acc_num;
	account_name = acc_name;
}

void Specialist::viewRequests() {
	for (int i = 0; i < ServiceRequest::numCurrentRequests; i++) {
		for (std::vector<string>::iterator it = operationalAreas.begin(); it != operationalAreas.end(); ++it) {
			if (ServiceRequest::currentRequests[i].incidentLocation == *it) {
				cout << ServiceRequest::toString(ServiceRequest::currentRequests[i]) << endl;
			}
		}
	}
}

Specialist* Specialist::load() {
	Specialist* specialists;
	total_specialists1 = 0;
	string line,  specID,  uname,  pwd,  fname,  lname,  license_num,  phnumber,  email,  qualification_num,  bsb,  acc_num,  acc_name, areas;
	string userFile = "Specialists.csv";

	// Creating input filestream
	ifstream file(userFile);
	while (getline(file, line)) total_specialists1++;
	specialists = new Specialist[total_specialists1 + 1];

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
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

			specialists[i] = Specialist(specID, uname, pwd, fname, lname, license_num, phnumber, email, qualification_num, bsb, acc_num, acc_name);
			std::stringstream ss(areas);
			std::string token;
			while (std::getline(ss, token, '|')) {
				specialists[i].operationalAreas.push_back(token);
			}
			i++;
		}
		inFile.close();
	}

	return specialists;
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
				specialists.back().operationalAreas.push_back(token);
			}
		}
		inFile.close();
	}

	return specialists;
}

void Specialist::save() {
	ofstream outFile;
	outFile.open("Specialists.csv", ios_base::app);

	outFile << specialistID << "`" << username << "`" << password << "`" << fName << "`" << lName << "`" << licenseNumber << "`" << phNumber << "`" << email << "`" << qualification_num << "`";

	for (std::vector<string>::iterator it = operationalAreas.begin(); it != operationalAreas.end(); ++it) {
		if (it != operationalAreas.begin()) outFile << "|";
		outFile << *it;
	}

	outFile << "`" << bsb << "`" << account_num << "`" << account_name << "\n";
	outFile.close();
}

void Specialist::selectRequest(int requestID) {
}

void Specialist::addArea(string postcode) {
	operationalAreas.push_back(postcode);
}

void Specialist::returnUser() {
	User::returnUser();//C: User::returnUser() just calls the parent function on the same object that calls this function (inheritance)
	//cout << "Operation Area: " << operationalArea << endl;
}