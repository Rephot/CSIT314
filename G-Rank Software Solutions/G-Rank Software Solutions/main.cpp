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
#include "GRSS.h"
#include "Reviews.h"
#include "car.h"

using namespace std;

int total_customers;
int total_specialists;
Specialist* specialists;
Customer* customers;
void firstMenu(int);
vector <vector<Specialist>> specialistsAvailable;
vector <Specialist> selectedSpecialist;
vector <vector<ServiceRequest>> completedRequests;
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

void isSelected(int requestID, Specialist logged_in_user) {
	if (selectedSpecialist[requestID].specialistID == logged_in_user.specialistID) {
		cout << "Selected for Request: " << ServiceRequest::currentRequests[requestID].toString() << endl;
	}
}

void completeRequest(int requestID, Specialist logged_in_user) {
	completedRequests.resize(total_specialists);
	for (int i = 0; i < ServiceRequest::numRequests; i++) {
		if (ServiceRequest::currentRequests[i].requestID == requestID) {
			//completedRequests[logged_in_user.specialistID].push_back(ServiceRequest::currentRequests[i]);
		}
	}
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

	users = Specialist::load();

	while (!valid) {
		cout << "Enter your username: ";
		cin >> userName;
		cout << "Enter your password: ";
		cin >> passWord;
		// this will be authentication
		
		for (int i = 0; i < total_specialists; i++) {
			if (users[i].getUserName() == userName && users[i].getPassword() == passWord) {
				cout << users[i].getUserName() << users[i].getPassword();
				logged_in_user = users[i];
				system("CLS");//clears console
				cout << "Logging in as specialist: " << logged_in_user.getUserName() << endl;
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

	users = Customer::load();

	for (int i = 0; i < 10; i++){
		cout << users[i].custID << " " << users[i].getUserName() << " " << users[i].getPassword() << endl;
	}

	while (!valid) {
		cout << "Enter your username: ";
		cin >> userName;
		cout << "Enter your password: ";
		cin >> passWord;
		// this will be authentication
		for (int i = 0; i < 10; i++) {
			if (users[i].getUserName() == userName && users[i].getPassword() == passWord) {
				cout << users[i].getUserName() << users[i].getPassword();
				logged_in_user = users[i];
				system("CLS");//clears console
				cout << "Logging in as customer: " << logged_in_user.getUserName() << endl;
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

int main(int argc, char **argv) {
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
	//int respondTo;

	//ServiceRequest req;
	//req.loadRequests();
	//Sleep(10000);//pauses for 5 seconds

	//Car car = Car(customers[0], "abc012", 2017, "Toyota", "Corolla", "Hatchback", 1.8, "White");
	//car.save();

	//cars = Car::loadCars();

	//selectRequest(1, specialists[0]);
	//selectRequest(1, specialists[1]);
	//selectRequest(1, specialists[0]);

	//showAvailable(1);
	
	//specialists = Specialist::load();
	//customers = Customer::load();

	////first menu
	//int choice = 99;
	//firstMenu(choice);
	//Sleep(100000);//pauses for 5 seconds

	//return 0;
	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return make_unique<GRSS>(env);
	});
}