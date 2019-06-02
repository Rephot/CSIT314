#include"Administrator.h"

Administrator::Administrator() {

}

Administrator::Administrator(int userID, string uname, string pwd, string fname, string lname, time_t dob, string number) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	DOB = dob;
	phNumber = number;
	adminID = userID;
}

void Administrator::saveAdministrator() {
	ofstream outFile;
	outFile.open("Customers.csv", ios_base::app);

	outFile << to_string(adminID) << "," << username << "," << password << "," << fName << "," << lName << "," << DOB << "," << phNumber << "\n";
	outFile.close();
}

void Administrator::returnUser() {
	cout << "adminID: " << adminID << endl;
	User::returnUser();
}

Administrator* loadAdministrators() {
	Administrator* users;
	int total_administrators = 0;
	string line, username, password, fName, lName, phNumber, custID, DOB;
	string userFile = "Specialists.csv";

	// Creating input filestream
	ifstream file(userFile);
	while (getline(file, line)) total_administrators++;
	users = new Administrator[total_administrators + 1];

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
	int i = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, custID, ','))
		{
			getline(inFile, username, ',');
			getline(inFile, password, ',');
			getline(inFile, fName, ',');
			getline(inFile, lName, ',');
			getline(inFile, DOB, ',');
			getline(inFile, phNumber);

			users[i] = Administrator(stoi(custID), username, password, fName, lName, stoi(DOB), phNumber);
			i++;
		}
		inFile.close();
	}

	return users;
}