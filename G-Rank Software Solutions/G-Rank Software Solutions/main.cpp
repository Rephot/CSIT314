#include<iostream>
#include<sstream>
#include<fstream>
#include<cstring>
#include<ctime>
#include"windows.h."
#include"ServiceRequest.h"
#include "User.h"

using namespace std;

int main(){
	/*
	1. loads in necessary info from file when we have
	1b. runs UI render loop
	2. performs functions as requested by user
	3. save info to file
	3b. closes webGL interface
	*/
	/*
	Service Request Test
	1. input details from client
	 a. Location
	 b. Type
	 c. generate date and time
	 d. ?anything else?
	2. create a service request from user input
	3. broadcast the request to specialists
	4. collate specialists who accepted the request
	5. show client specialists who accepted
	6. client chooses a specialist
	7. specialist receives a go ahead notification
	*/
	int exitCode;

	User* users;

	int count = 0;
	string line;

	/* Creating input filestream */
	ifstream file("Users.csv");
	while (getline(file, line))
		count++;

	users = new User[count + 1];

	ofstream outFile;
	outFile.open("Users.csv", ios_base::app);


	//create test User
	string username, password, fName, lName, phNumber, input;

	cout << "To Create an account please enter a username: ";//later on i will handle inputing and outputing all user accounts to a csv // JOSH: "this can be managed in the Wt::Auth module"
	getline(cin, username);
	cout << "Please enter a password: ";
	getline(cin, password);
	cout << "Now please enter your first name, last name and phone number: ";//use a space between fname, lname and phone number then enter
	getline(cin, input);

	//istring stream allows for multiple variables to be input on one line of console (if needed elsewhere but was just testing here)
	std::istringstream iss(input);
	iss >> fName;
	iss >> lName;
	iss >> phNumber;

	//write variables for new user to file
	outFile << username << "," << password << "," << fName << "," << lName << "," << phNumber << "\n";

	outFile.close();

	//open file to create array of users
	ifstream inFile;
	inFile.open("Users.csv");

	int i = 0;

	if (inFile.is_open())
	{
		while (getline(inFile, username, ','))
		{
			getline(inFile, password, ',');
			getline(inFile, fName, ',');
			getline(inFile, lName, ',');
			getline(inFile, phNumber);

			users[i] = User(username, password, fName, lName, 0, phNumber);

			i++;
		}
		inFile.close();
	}


	//User user1(username, password, fName, lName, 0, phNumber);// creates user

	system("CLS");//clears console

	//print all user details
	for (int i = 0; i < count + 1; i++) {
		users[i].returnUser();
		cout << endl;
	}

	//user1.returnUser();//displays user credentials

	Sleep(10000);//pauses for 10 seconds

	system("CLS");//clears console


	delete users;
	//run test request
	ServiceRequest testRequest;
	testRequest.createServiceRequest();
	cin >> exitCode;
	return 0;
}
