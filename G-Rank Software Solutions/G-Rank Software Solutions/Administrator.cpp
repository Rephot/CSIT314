#include"Administrator.h"
#include <vector>

Administrator::Administrator() {

}

Administrator::Administrator(string userID, string uname, string pwd, string fname, string lname, string number) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	phNumber = number;
	adminID = userID;
}

void Administrator::saveAdministrator() {
	ofstream outFile;
	outFile.open("Administrators.csv", ios_base::app);

	outFile << adminID << "`" << username << "`" << password << "`" << fName << "`" << lName << "`" << phNumber << "\n";
	outFile.close();
}

void Administrator::returnUser() {
	cout << "adminID: " << adminID << endl;
	User::returnUser();
}

vector<Administrator> Administrator::loadAdministrators() {
	vector<Administrator> users;
	string line, username, password, fName, lName, phNumber, custID, DOB;
	string userFile = "Administrators.csv";

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
	if (inFile.is_open())
	{
		while (getline(inFile, custID, '`'))
		{
			getline(inFile, username, '`');
			getline(inFile, password, '`');
			getline(inFile, fName, '`');
			getline(inFile, lName, '`');
			getline(inFile, DOB, '`');
			getline(inFile, phNumber);

			users.push_back(Administrator(custID, username, password, fName, lName, phNumber));
		}
		inFile.close();
	}

	return users;
}

void Administrator::viewTransactions(vector<Transaction> transactions) {
	//view all
}

void Administrator::suspendUser(string custID, vector<Customer> customers) {
	//match to list and ban
}

void Administrator::suspendUser(string custID, vector<Specialist> specialists) {
	//match to list and ban
}