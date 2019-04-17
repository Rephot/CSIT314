#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include"ServiceRequest.h"
#include"Specialist.h"

using namespace std;

int main(){
	/*
	1. loads in necessary info from file when we have
	1b. runs UI render loop
	2. performs functions as requested by user
	3. save info to file
	3b. closes interface
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
	ServiceRequest testRequest;
	/*while (exitCode != 'q') {

	}*/
	cout << "THIS IS AS USER\nuser calls createServiceRequest by pressing a button in the ui\n"; // description of what aim to do with WT widgets
	testRequest.createServiceRequest();
	cout << "NOW AS SPECIALIST\n";
	Specialist andrew;
	andrew.viewRequests();
	cout << "q to quit: ";
	cin >> exitCode;
	return 0;
}
