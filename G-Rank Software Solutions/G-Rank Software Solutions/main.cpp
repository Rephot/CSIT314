#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include"ServiceRequest.h"
#include"Specialist.h"

#include"G-RankSoftwareSolutions.h"

//int main(int argc, char **argv){
//	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
//		return make_unique<GRankSoftwareSolutions>(env);
//	});
//}

char firstMenu(char choice) {
	while (choice != 'l' && choice != 'L' && choice != 'q' && choice != 'Q' && choice != 'r' && choice != 'R') {
		cout << "L for Login\nR for Register\nQ for quit\nWhat would you like to do? ";
		cin >> choice;
		if (choice != 'l' && choice != 'L' && choice != 'q' && choice != 'Q' && choice != 'r' && choice != 'R') cout << "Please enter a letter corresponding to a menu item. ";
	}
	return choice;
}

char loginMenu(char choice) {
	// enter login details, then validate, then show options once logged in.
	return 'p';
}

char registerMenu(char choice) {
	// enter new user details as necessary, then proceed to profile options
	return 'p';
}

char profileMenu(char choice) {
	// enter new user details as necessary, then proceed to profile options
	return 'p';
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
	char choice = 'a';

	//first menu
	firstMenu(choice);

	while (choice != 'q' && choice != 'Q') {
		if (choice == 'l' || choice == 'L') choice = loginMenu(choice);
		if (choice == 'r' || choice == 'R') choice = registerMenu(choice);
		if (choice == 'p' || choice == 'P') choice = profileMenu(choice);
		cout << endl << choice << endl;
	}
	

	ServiceRequest testrequest;
	cout << "this is as user\nuser calls createservicerequest by pressing a button in the ui\n"; // description of what aim to do with wt widgets
	testrequest.createServiceRequest();
	cout << "now as specialist\n";
	Specialist andrew;
	andrew.viewRequests();
	cout << "which request would you like to respond to? ";
}

// choices from menu