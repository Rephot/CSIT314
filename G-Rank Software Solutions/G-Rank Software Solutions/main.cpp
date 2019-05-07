#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "ServiceRequest.h"
#include "Specialist.h"
#include"Customer.h"
#include "User.h"
#include "G-RankSoftwareSolutions.h"

using namespace std;

/*
COMPLETED(for purpose of functionality check up) -- login and user creation is one funcitonality should focus on customer creation{ 
	username
	password
	email
	DoB
	real name
}
COMPLETED(for purpose of functionality check up, work is to continue on the rest of the class functions) -- service request creation relates to managing roadside assistance service requests{
	description of incident
	location of incident
	time created
	customer who created
	?
}
create review for roadside assistance professional related to a request{
	review description max characters ??
	customer who created
	specialist review is about
	review specific rating
	?? average rating for the specialist ??
}
create a roadside assistance professional account{
	rating out of 10
	reveiw description (max char length?)
	customer username/name
	pulls request identifier
	pulls customer identifier
	pulls specialist identifier
}
create a way to pay professionals for a service completion{
	access bank details of specialist for payment
	receipt has:
		transaction ID
		amount
		subscribed or not - include callout fee in this transaction
		time
		customer identifier
		specialist identifier
		?vehicle identification? if specialists are fleet
}
create review for roadside assistance professional related to a request{
	rating out of 10?
	reveiw description (max char length?)
	customer username/name
	pulls request identifier
	pulls customer identifier
	pulls specialist identifier
}
create a roadside assistance professional account(Will update user account handling to allow for both customer and professional account types){
	bank account details
	preferred area of operation
	generated identifier
	based on user creation for login account
}
create a way to pay professionals for a service completion
(can we just use a flag ifPaid or something for now and say its handled by paypal or something?
J: maybe, do you want to ask one of the tutors or Hoa? and also just so we can easily see questions from the other within comments, seperate the line and tag it "C:" or "J:", 
TEST see if this push goes through){
	transaction ID
	amount
	subscribed or not - include callout fee in this transaction
	time
	customer identifier
	specialist identifier
	?vehicle identification? if specialists are fleet
}
*/
int total_customers;
int total_specialists;

Specialist* loadSpecialists() {
	Specialist* users;
	total_specialists = 0;
	string line, username, password, fName, lName, phNumber, operationalArea, specialistID;
	string userFile = "Specialists.csv";

	// Creating input filestream
	ifstream file(userFile);
	while (getline(file, line)) total_specialists++;
	users = new Specialist[total_specialists + 1];

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
			getline(inFile, phNumber, ',');
			getline(inFile, operationalArea, ',');
			getline(inFile, specialistID);

			users[i] = Specialist(username, password, fName, lName, 0, phNumber, operationalArea, stoi(specialistID));
			i++;
		}
		inFile.close();
	}

	return users;
}

Customer* loadCustomers() {
	Customer* users;
	total_customers = 0;
	string line, username, password, fName, lName, phNumber, operationalArea, specialistID;
	string userFile = "Users.csv";

	/* Creating input filestream */
	ifstream file(userFile);
	while (getline(file, line)) total_customers++;
	users = new Customer[total_customers + 1];

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

			users[i] = Customer(username, password, fName, lName, 0, phNumber);
			i++;
		}
		inFile.close();
	}

	return users;
}

void receiptsMenu(char choice) {
	// view payment history
	// view request history
	// view ?
}

void specialist_manageDetailsMenu(char choice, Specialist logged_in_user) {
	// view user details
	// edit user details
	logged_in_user.returnUser();
}

void manageDetailsMenu(char choice, Customer logged_in_user) {
	// view user details
	// edit user details
	logged_in_user.returnUser();
}

void createRequestMenu(char choice, Customer logged_in_user) {
	// run createServiceRequest();
	ServiceRequest create;
	create.createServiceRequest(logged_in_user);
}

void specialist_profileMenu(char choice, Specialist logged_in_user) {
	/* user can choose between
	looking at receipt
	managing their details
	creating request
	?viewing their current request progress?
	or quitting */
	while (choice != 'r' && choice != 'R'
		&& choice != 'm' && choice != 'M'
		&& choice != 'q' && choice != 'Q') {
		cout << "R for Receipts ETC\n";
		cout << "M for Manage User Details\n";
		cout << "Q for Logout and Quit\n";
		cout << "What would you like to do ? ";
		cin >> choice;
		if (choice != 'r' && choice != 'R'
			&& choice != 'm' && choice != 'M'
			&& choice != 'q' && choice != 'Q')
			cout << "Please enter a letter corresponding to a menu item. ";
	}
	cin.ignore();
	system("CLS");//clears console
	if (choice == 'r' || choice == 'R') receiptsMenu(choice);
	else if (choice == 'm' || choice == 'M') specialist_manageDetailsMenu(choice, logged_in_user);
	else return;
}

void profileMenu(char choice, Customer logged_in_user) {
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
	system("CLS");//clears console
	if (choice == 'r' || choice == 'R') receiptsMenu(choice);
	else if (choice == 'm' || choice == 'M') manageDetailsMenu(choice, logged_in_user);
	else if (choice == 'c' || choice == 'C') createRequestMenu(choice, logged_in_user);
	else return;
}

void specialist_loginMenu(char choice) {
	Specialist* users;
	string userName, passWord;
	bool valid = false;
	Specialist logged_in_user;
	// enter login details, then validate, then show options once logged in.

	users = loadSpecialists();

	while (!valid) {
		cout << "Enter your username: ";
		cin >> userName;
		cout << "Enter your password: ";
		cin >> passWord;
		// this will be authentication
		
		for (int i = 0; i < total_specialists; i++) {
			if (users[i].username == userName && users[i].getPassword() == passWord) {
				cout << users[i].username << users[i].getPassword();
				logged_in_user = users[i];
				system("CLS");//clears console
				cout << "Logging in as specialist: " << logged_in_user.username << endl;
				valid = true;
				break;
			}
		}
	}
	cin.ignore();
	specialist_profileMenu(choice, logged_in_user);
}

void customer_loginMenu(char choice) {
	Customer* users;
	string userName, passWord;
	bool valid = false;
	Customer logged_in_user;
	// enter login details, then validate, then show options once logged in.

	users = loadCustomers();

	while (valid) {
		cout << "Enter your username: ";
		cin >> userName;
		cout << "Enter your password: ";
		cin >> passWord;
		// this will be authentication
		userName = users[1].username;
		passWord = users[1].getPassword();
		for (int i = 0; i < total_customers; i++) {
			if (users[i].username == userName && users[i].getPassword() == passWord) {
				cout << users[i].username << users[i].getPassword();
				logged_in_user = users[i];
				system("CLS");//clears console
				cout << "Logging in as customer: " << logged_in_user.username << endl;
				valid = true;
				break;
			}
		}		
	}
	cin.ignore();
	profileMenu(choice, logged_in_user);
}

void specialist_signUpMenu(char choice) {
	string username, password, fName, lName, phNumber, input, opArea, id;
	Specialist created_user;

	// enter new user details as necessary, then proceed to profile options
	ofstream outFile;
	outFile.open("Specialists.csv", ios_base::app);

	//create test User
	//later on i will handle inputing and outputing all user accounts to a csv
	// JOSH: "this can be managed in the Wt::Auth module"
	cout << "To Create an account please enter a username: ";
	getline(cin, username);
	cout << "Please enter a password: ";
	getline(cin, password);
	cout << "Please enter your operation postcode: ";
	getline(cin, opArea);
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
	outFile << username << "," << password << "," << fName << "," << lName << "," << phNumber << "," << opArea << "," << "0" << "\n";
	outFile.close();
	system("CLS");//clears console
	//cin.ignore();
	cout << "Specialist Account Created Succesfully";
	specialist_loginMenu('L');
}

void signUpMenu(char choice) {
	string username, password, fName, lName, phNumber, input;
	User created_user;

	// enter new user details as necessary, then proceed to profile options
	ofstream outFile;
	outFile.open("Users.csv", ios_base::app);

	//create test User
	//later on i will handle inputing and outputing all user accounts to a csv
	cout << "To Create an account please enter a username: ";
	getline(cin, username);
	cout << "Please enter a password: ";
	getline(cin, password);
	//use a space between fname, lname and phone number then enter
	cout << "Now please enter your first name, last name and phone number: ";
	getline(cin, input);

	/*istringstream allows for multiple variables to be input on one line of console
	it also allows you to build a string much more easily
	e.g stringstream hello << "This is an example: " << string value << " says hello!";
	(if needed elsewhere but was just testing here)*/
	std::istringstream iss(input);
	iss >> fName;
	iss >> lName;
	iss >> phNumber;

	//write variables for new user to file
	outFile << username << "," << password << "," << fName << "," << lName << "," << phNumber << "\n";
	outFile.close();
	system("CLS");//clears console
	cin.ignore();
	cout << "Customer Account Created Succesfully";
	customer_loginMenu('L');
}

void firstMenu(char choice) {
	bool isChoice = false;
	char choices[8] = {'l', 'L', 's', 'S', 'p', 'P', 'C', 'c'};
	while (!isChoice) {
		cout << "L for Customer Login\nS for Customer Sign Up\nP for Specialist Login\nC for Specialist Sign up\nQ for quit\nWhat would you like to do? ";
		cin >> choice;
		if (std::find(std::begin(choices), std::end(choices), choice) != std::end(choices))
			isChoice = true;
		else
			cout << "Please enter a letter corresponding to a menu item.\n";
	}
	//cin.ignore();
	system("CLS");//clears console
	if (choice == 'l' || choice == 'L') customer_loginMenu(choice);
	else if (choice == 's' || choice == 'S') signUpMenu(choice);
	else if (choice == 'c' || choice == 'C') specialist_signUpMenu(choice);
	else if (choice == 'p' || choice == 'P') specialist_loginMenu(choice);
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
	Sleep(2500);//pauses for 2.5 seconds
	system("CLS");//clears console

	// main menu
	char choice = '\0', exitCode;
	int respondTo;

	//first menu
	firstMenu(choice);

	cout << "q to quit: ";
	cin >> exitCode;
	//cout << exitCode;

	return exitCode;
	//	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
	//		return make_unique<GRankSoftwareSolutions>(env);
	//	});
}