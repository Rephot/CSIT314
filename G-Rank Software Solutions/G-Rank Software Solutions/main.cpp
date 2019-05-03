#include <algorithm>
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

/*
login and user creation is one funcitonality should focus on customer creation
service request creation relates to managing roadside assistance service requests
create review for roadside assistance professional related to a request
create a roadside assistance professional account
create a way to pay professionals for a service completion
*/

//int main(int argc, char **argv){
//	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
//		return make_unique<GRankSoftwareSolutions>(env);
//	});
//}

void receiptsMenu(char choice) {
	// view payment history
	// view request history
	// view ?
}

void manageDetailsMenu(char choice) {
	// view user details
	// edit user details
}

void createRequestMenu(char choice) {
	// run createServiceRequest();
	ServiceRequest create;
	create.createServiceRequest();
}

void profileMenu(char choice) {
	/* user can choose between
	looking at receipt
	managing their details
	creating request
	?viewing their current request progress?
	or quitting */
	while (choice != 'r' && choice != 'R'
		&& choice != 'm' && choice != 'M'
		&& choice != 'c' && choice != 'C'
		&& choice != 'q' && choice != 'Q') {
			cout << "R for Receipts ETC\n";
			cout << "M for Manage User Details\n";
			cout << "C for Create Request\n";
			cout << "Q for Logout and Quit\n";
			cout << "What would you like to do ? ";
			cin >> choice;
			if (choice != 'r' && choice != 'R'
			 && choice != 'm' && choice != 'M'
			 && choice != 'c' && choice != 'C'
			 && choice != 'q' && choice != 'Q')
				cout << "Please enter a letter corresponding to a menu item. ";
	}
	cin.ignore();
	if (choice == 'r' || choice == 'R') receiptsMenu(choice);
	else if (choice == 'm' || choice == 'M') manageDetailsMenu(choice);
	else if (choice == 'c' || choice == 'C') createRequestMenu(choice);
	else return;
}

void signUpMenu(char choice) {
	string username, password, fName, lName, phNumber, input;

	// enter new user details as necessary, then proceed to profile options
	ofstream outFile;
	outFile.open("Users.csv", ios_base::app);

	//create test User
	//later on i will handle inputing and outputing all user accounts to a csv
	// JOSH: "this can be managed in the Wt::Auth module"
	cout << "To Create an account please enter a username: ";
	getline(cin, username);
	cout << "Please enter a password: ";
	getline(cin, password);
	//use a space between fname, lname and phone number then enter
	cout << "Now please enter your first name, last name and phone number: ";
	getline(cin, input);

	/*istring stream allows for multiple variables to be input on one line of console
	(if needed elsewhere but was just testing here)*/
	std::istringstream iss(input);
	iss >> fName;
	iss >> lName;
	iss >> phNumber;

	//write variables for new user to file
	outFile << username << "," << password << "," << fName << "," << lName << "," << phNumber << "\n";
	outFile.close();
	cin.ignore();
	profileMenu(choice);
}

void loginMenu(char choice) {
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
	cin.ignore();
	profileMenu(choice);
}

void firstMenu(char choice) {
	bool isChoice = false;
	char choices[6] = {'l', 'L', 's', 'S', 'p', 'P'};
	while (!isChoice) {
		cout << "L for Login\nS for Sign Up\nQ for quit\nWhat would you like to do? ";
		cin >> choice;
		if (std::find(std::begin(choices), std::end(choices), choice) != std::end(choices))
			cout << "Please enter a letter corresponding to a menu item.\n";
		else
			isChoice = true;
	}
	cin.ignore();
	if (choice == 'l' || choice == 'L') loginMenu(choice);
	else if (choice == 's' || choice == 'S') signUpMenu(choice);
	else if (choice == 'p' || choice == 'P') profileMenu(choice);
	else return;
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
	string line, username, password, fName, lName, phNumber;
	string userFile = "Users.csv";

	/* Creating input filestream */
	ifstream file("Users.csv");
	while (getline(file, line)) count++;
	users = new User[count + 1];

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
	firstMenu(choice);
	
	cin.ignore();
	
	// test creation of serviceRequest
	ServiceRequest testrequest;
	// description of what aim to do with wt widgets
	cout << "this is as user\n";
	cout << "user calls createservicerequest by pressing a button in the ui\n";
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