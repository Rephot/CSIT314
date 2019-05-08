//customer inherits user

#include"Customer.h"
#include <fstream>
#include <iostream>
#include <string>


Customer::Customer(){
	
}

Customer::Customer(int userID, string uname, string pwd, string fname, string lname, time_t dob, string number) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	DOB = dob;
	phNumber = number;
	custID = userID;
}

void Customer::saveCustomer() {
	ofstream outFile;
	outFile.open("Customers.csv", ios_base::app);

	outFile << to_string(custID) << "," << username << "," << password << "," << fName << "," << lName << "," << DOB << "," << phNumber << "\n";
	outFile.close();
}

void Customer::returnUser() {
	cout << "custID: " << custID << endl;
	User::returnUser();
}