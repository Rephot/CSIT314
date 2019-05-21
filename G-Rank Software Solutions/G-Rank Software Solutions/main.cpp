#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <vector>


#include "ServiceRequest.h"
#include "Specialist.h"
#include "Customer.h"
#include "User.h"
#include "G-RankSoftwareSolutions.h"
#include "Reviews.h"
#include "car.h"

using namespace std;

/*
J: For future testing have changed menu items from char selection to int selection, easier to manage
J: also changed the menus to be do whiles, as they happen at least once, and before, the menu wasn't showing sometimes

COMPLETED(for purpose of functionality check up) -- login and user creation is one funcitonality should focus on customer creation{ 
	username
	password
	email
	DoB
	real name
}
C: for below, basics is working but the following needs to be added
COMPLETED(for purpose of functionality check up) create a roadside assistance professional account -- still need bank details{
	average rating out of 10
	bank account details - not yet implemented
	preferred area of operation
	generated identifier
	based on user creation for login account
}
COMPLETED(for purpose of functionality check up, work is to continue on the rest of the class functions) -- service request creation relates to managing roadside assistance service requests{
	description of incident
	location of incident
	time created
	customer who created
	?
}
C: For below I see some of the class is done. I will work on loading them in and out of a file
J: COMPLETE(for the purpose of functionality progress review) create review for roadside assistance professional related to a request{
	rating out of 10?
	reveiw description (max char length?)
	customer username/name
	pulls request identifier
	pulls customer identifier
	pulls specialist identifier
}
J: MOSTLY COMPLETED(receipt generation mostly complete, still needs to access the customer, specialist and request identifiers)create a way to pay professionals on service completion, this could also be considered receipt generation considering the information that we generate{
	access bank details of specialist for payment
	receipt has:
		transaction ID (should be generated from a static variable that increases after each transaction is processed)
		amount (the amount charged for the particular service type)
		subscribed or not - include callout fee in this transaction (this will only appear on PoD user receipts)
		time (consider whether it should include both time request, time of payment or both)
		customer identifier (auto filled from ServiceRequest info, ie ServiceRequest should have Customer that is related to it)
		specialist identifier (auto filled from ServiceRequest info, ie ServiceRequest should have Specialist that is related to it, but only after the Specialist has confirmed to take on the job)
		?vehicle identification? if specialists are fleet - this is more required from the company's point of view, as a mini insurance thing, so they know which vehicle was where, and with who
			shall ask whether this information is required, if so there will be a fleet truck class, wtih:
			- truck rego
			- truck ID
			- truck status: {available, assigned, maintainanceRequired)
}
*/

int total_customers;
int total_specialists;
Specialist* specialists;
Customer* customers;
void firstMenu(int);
vector <vector<Specialist>> specialistsAvailable;
vector <Specialist> selectedSpecialist;
Car* cars;

void showAvailable(int requestID) {
	for (int i = 0; i < specialistsAvailable[requestID].size(); i++) {
		cout << i << " " << specialistsAvailable[requestID][i].getFullName() << " " << specialistsAvailable[requestID][i].getNumber() << endl;;
	}
}

void selectRequest(int requestID, Specialist logged_in_user) {
	specialistsAvailable.resize(50);
	specialistsAvailable[requestID].push_back(logged_in_user);
}

void acceptSpecialist(int requestID, int specialistIndex) {
	selectedSpecialist.resize(50);
	selectedSpecialist[requestID] = specialistsAvailable[requestID][specialistIndex];
}




/*C: Returns array of specialist users from file Specialists.csv*/
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

/*C: Returns array of customer users from file Customers.csv*/
Customer* loadCustomers() {
	Customer* users;
	total_customers = 0;
	string line, username, password, fName, lName, phNumber, custID, DOB;
	string userFile = "Customers.csv";

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
		while (getline(inFile, custID, ','))
		{
			getline(inFile, username, ',');
			getline(inFile, password, ',');
			getline(inFile, fName, ',');
			getline(inFile, lName, ',');
			getline(inFile, DOB, ',');
			getline(inFile, phNumber);

			users[i] = Customer(stoi(custID), username, password, fName, lName, stoi(DOB), phNumber);
			i++;
		}
		inFile.close();
	}

	return users;
}

void receiptsMenu(int choice) {
	// view payment history
	// view request history
	// view ?
}

// should be a menu item in customer menu
void reviewMenu(int choice, Customer logged_in_user) {
	// create review after job completion (stretch, servicerequests will have flag for completion to check against, also extended time to write one up)
	Review averageRev;
	averageRev.createReview(logged_in_user);
}

/*C: Currently only displays specialist account details but will extend to edit*/
void specialist_manageDetailsMenu(int choice, Specialist logged_in_user) {
	// view user details
	// edit user details
	logged_in_user.returnUser();
}

/*C: Currently only displays customer account details but will extend to edit*/
void manageDetailsMenu(int choice, Customer logged_in_user) {
	// view user details
	// edit user details
	logged_in_user.returnUser();
}

void createRequestMenu(int choice, Customer logged_in_user) {
	// run createServiceRequest();
	ServiceRequest create;
	create.createServiceRequest(logged_in_user);
}

void viewRequestMenu(int choice, Specialist logged_in_user) {
	// run createServiceRequest();
	logged_in_user.viewRequests();
}


/*C: Specialist menu deisplayed when logged in*/
void specialist_profileMenu(int choice, Specialist logged_in_user) {
	/* user can choose between
	looking at receipt
	managing their details
	creating request
	?viewing their current request progress?
	or quitting */
	do {
		cout << "1. Receipts ETC\n";
		cout << "2. Manage User Details\n";
		cout << "3. View Requests\n";
		cout << "0. Logout and Quit\n";
		cout << "What would you like to do? ";
		cin >> choice;
		if (choice < 0 && choice > 3)
			cout << "Please enter a letter corresponding to a menu item.";
	} while (choice < 0 && choice > 3);
	cin.ignore();
	system("CLS");//clears console
	if (choice == 1) receiptsMenu(99);
	else if (choice == 2) specialist_manageDetailsMenu(99, logged_in_user);
	else if (choice == 3) viewRequestMenu(99, logged_in_user);
	else return;
}

/*C: Customer menu displayed when logged in*/
void customer_profileMenu(int choice, Customer logged_in_user) {
	/* user can choose between
		looking at receipt
		managing their details
		creating request
		create review
		?viewing their current request progress?
		or quitting */
	do {
			cout << "1. View Receipts ETC\n";
			cout << "2. Manage User Details\n";
			cout << "3. Create Request\n";
			cout << "4. Create Review\n";
			cout << "0. Logout and Quit\n";
			cout << "What would you like to do ? ";
			cin >> choice;
			if (choice < 0 && choice > 4)
				cout << "Please enter a number corresponding to a menu item. ";
	} while (choice < 0 && choice > 4);
	cin.ignore();
	system("CLS");//clears console
	if (choice == 1) receiptsMenu(99);
	else if (choice == 2) manageDetailsMenu(99, logged_in_user);
	else if (choice == 3) createRequestMenu(99, logged_in_user);
	else if (choice == 4) reviewMenu(99, logged_in_user);
	else return;
}

/*C: Login menu for specialists*/
void specialist_loginMenu(int choice) {
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
	specialist_profileMenu(99, logged_in_user);
}

/*C: Login menu for customers*/
void customer_loginMenu(int choice) {
	Customer* users;
	string userName, passWord;
	bool valid = false;
	Customer logged_in_user;
	// enter login details, then validate, then show options once logged in.

	users = loadCustomers();

	while (!valid) {
		cout << "Enter your username: ";
		cin >> userName;
		cout << "Enter your password: ";
		cin >> passWord;
		// this will be authentication
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
	customer_profileMenu(99, logged_in_user);
}

/*C: Signup menu for specialists*/
void specialist_signUpMenu(int choice) {
	string username, password, fName, lName, phNumber, input, opArea, id;
	Specialist created_user;

	// enter new user details as necessary, then proceed to profile options
	ofstream outFile;
	outFile.open("Specialists.csv", ios_base::app);

	//create test User
	//later on i will handle inputing and outputing all user accounts to a csv
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
	outFile << username << "," << password << "," << fName << "," << lName << "," << phNumber << "," << opArea << "," << to_string(total_specialists+1) << "\n";
	outFile.close();
	system("CLS");//clears console
	//cin.ignore();
	cout << "Specialist Account Created Succesfully" << endl;
	firstMenu(99);
}

/*C: Signup menu for Customers*/
void signUpMenu(int choice) {
	string username, password, fName, lName, phNumber, input;
	Customer created_user;

	// enter new user details as necessary, then proceed to profile options
	//ofstream outFile;
	//outFile.open("Users.csv", ios_base::app);

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
	created_user = Customer(total_customers+1, username, password, fName, lName, 0, phNumber);
	created_user.saveCustomer();

	system("CLS");//clears console
	
	cout << "Customer Account Created Succesfully" << endl;
	firstMenu(99);
}

/*Opening console menu for program*/
void firstMenu(int choice) {
	do {
		cout << "1. Customer Login\n";
		cout << "2. Customer Sign Up\n";
		cout << "3. Specialist Login\n";
		cout << "4. Specialist Sign up\n";
		cout << "0. quit\n";
		cout << "What would you like to do ? ";
		cin >> choice;
		cin.ignore();
		if (choice < 0 && choice > 4) cout << "Please enter a number corresponding to a menu item.\n";
	} while (choice < 0 && choice > 4);
	//cin.ignore();
	system("CLS");//clears console
	if (choice == 1) customer_loginMenu(99);
	else if (choice == 2) signUpMenu(99);
	else if (choice == 3) specialist_loginMenu(99);
	else if (choice == 4) specialist_signUpMenu(99);
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
	
	/*initiation
	User* users;
	int count = 0;
	string line, username, password, fName, lName, phNumber;
	string userFile = "Users.csv";

	// Creating input filestream
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
	}*/

	// test user file contents
	//User user1(username, password, fName, lName, 0, phNumber);// creates user
	//system("CLS");//clears console

	/*print all user details
	for (int i = 0; i < count + 1; i++) {
		users[i].returnUser();
		cout << endl;
	}*/

	//user1.returnUser();//displays user credentials
	//Sleep(2500);//pauses for 2.5 seconds
	//system("CLS");//clears console

	// main menu
	int choice = 99;
	int respondTo;

	specialists = loadSpecialists();
	customers = loadCustomers();

	ServiceRequest req;
	req.loadRequests();

	Car car = Car(customers[0], "abc012", 2017, "Toyota", "Corolla", "Hatchback", 1.8, "White");
	car.save();


	cars = Car::loadCars();

	selectRequest(1, specialists[0]);
	selectRequest(1, specialists[1]);
	selectRequest(1, specialists[0]);

	showAvailable(1);

	

	//first menu
	firstMenu(choice);
	//cout << exitCode;
	Sleep(10000);//pauses for 5 seconds

	return 0;
	/*return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return make_unique<GRankSoftwareSolutions>(env);
	});*/
}