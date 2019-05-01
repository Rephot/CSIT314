#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "ServiceRequest.h"
#include "Specialist.h"
#include "User.h"
#include "G-RankSoftwareSolutions.h"

using namespace std;

//int main(int argc, char **argv){
//	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
//		return make_unique<GRankSoftwareSolutions>(env);
//	});
//}

char firstMenu(char choice) {
	while (choice != 'l' && choice != 'L' && choice != 'q' && choice != 'Q' && choice != 's' && choice != 'S') {
		cout << "L for Login\nS for Sign Up\nQ for quit\nWhat would you like to do? ";
		cin >> choice;
		if (choice != 'l' && choice != 'L' && choice != 'q' && choice != 'Q' && choice != 's' && choice != 'S') cout << "Please enter a letter corresponding to a menu item.\n";
	}
	return choice;
}

char loginMenu(char choice) {
	string userName, passWord;
	bool valid = false;
	// enter login details, then validate, then show options once logged in.
	cout << valid << endl;
	while (!valid) {
		cout << "Enter your username: ";
		cin >> userName;
		cout << "Enter your password: ";
		cin >> passWord;
		cout << "TEST!\n";
		valid = true;
	}
	return 'p';
}

char signUpMenu(char choice) {
	// enter new user details as necessary, then proceed to profile options

	return 'q';
}

char profileMenu(char choice) {
	// enter new user details as necessary, then proceed to profile options
	while (choice != 'r' && choice != 'R' && choice != 'm' && choice != 'M' && choice != 'c' && choice != 'C') {
		cout << "R for Receipts ETC\nM for Manage User Details\nC for Create Request\nWhat would you like to do? ";
		cin >> choice;
		if (choice != 'r' && choice != 'R' && choice != 'm' && choice != 'M' && choice != 'c' && choice != 'C') cout << "Please enter a letter corresponding to a menu item. ";
	}
	return choice;
}

int main(int argc, char **argv){
	/*
	1. loads in necessary info from file when we have
	1b. runs UI render loop
	2. performs functions as requested by user
	3. save info to file
	3b. closes interface

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
	
	//initiation
	User* users;
	int count = 0;
	string line, username, password, fName, lName, phNumber, input;
	string userFile = "Users.csv";

	/* Creating input filestream */
	ifstream file("Users.csv");
	while (getline(file, line)) count++;
	users = new User[count + 1];
	
	ofstream outFile;
	outFile.open("Users.csv", ios_base::app);

	//create test Userdfasdf
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

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
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

	// test user file contents
	//User user1(username, password, fName, lName, 0, phNumber);// creates user
	system("CLS");//clears console

	//print all user details
	for (int i = 0; i < count + 1; i++) {
		users[i].returnUser();
		cout << endl;
	}

	//user1.returnUser();//displays user credentials
	Sleep(5000);//pauses for 5 seconds
	system("CLS");//clears console

	// main menu
	char choice = '\0', exitCode;
	int respondTo;

	//first menu
	choice = firstMenu(choice);

	while (choice != 'q' && choice != 'Q') {
		if (choice == 'l' || choice == 'L') choice = loginMenu(choice);
		if (choice == 's' || choice == 'S') choice = signUpMenu(choice);
		if (choice == 'p' || choice == 'P') choice = profileMenu(choice);
		else choice = 'q';
	}
	
	cin.ignore();
	
	// test creation of serviceRequest
	ServiceRequest testrequest;
	cout << "this is as user\nuser calls createservicerequest by pressing a button in the ui\n"; // description of what aim to do with wt widgets
	testrequest.createServiceRequest();
	cout << "now as specialist\n";
	Specialist andrew;
	andrew.viewRequests();
	cout << "which request would you like to respond to? ";
	cin >> respondTo;
	cout << "q to quit: ";
	cin >> exitCode;
	cout << exitCode;
	return 0;
}

// choices from menu