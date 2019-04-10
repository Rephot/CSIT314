#include<iostream>
#include<string>
#include"ServiceRequest.h"

using namespace std;

/*
created
broadcast
accept request
display accepted
client chooses
sends affirmative to professional
// do we need a second level of confirmation?
*/

//struct location{
//	int streetNo;
//	string streetName;
//	string suburb;
//	string description;
//	
//};

//struct customerInfo{
//	string car; // will be a car object when that is made
//	string name; // will be a first and last if necessary
//	// will add more if necessary, if you happen to think of any, please add them
//};

ServiceRequest::ServiceRequest() {
	clientName = "";
	incidentLocation = "";
	sType = "";
	serviceRequestedAt = NULL;
}

ServiceRequest::ServiceRequest(string client, string location, string serviceType, time_t dateTimeRequested){
	//customer who created and all associated data(name, user type, car information), location details provided, 
	clientName = client;
	incidentLocation = location;
	sType = serviceType;
	serviceRequestedAt = dateTimeRequested;
}

void ServiceRequest::createServiceRequest(/*needs customer who called*/){//(Customer currentCustomer)
	/*
	some way of acquiring location info
	*/
	/* Test 
	
	*/
	ServiceRequest newRequest;
	// identifying number
	string sType, location, client;
	time_t dateTimeRequested, timer;
	cout << "This is a Test:\nPlease Enter the details of the incident.\nIs it a breakdown or something like a flat tyre? ";
	getline(cin, sType);
	cout << "Where did the incident happen? ";
	getline(cin, location);
	dateTimeRequested = time(&timer);
	client = "Joshua Groucutt";
	newRequest = { client, location, sType, dateTimeRequested };
	broadcastServiceRequest(newRequest);
}

void ServiceRequest::broadcastServiceRequest(ServiceRequest newRequest){
	// place into an array for the specialists to view
	// will be called from the constructor
	// add service request to static member of specialist class
	cout << "This is where the request would be broadcast from!\n" << endl;
}

// a get function that returns the array of professionals that accepted
void ServiceRequest::displayProfessionalsWhoAccepted(){
	// lets client see who is available to help
	// displays formatted data from an array
}

void ServiceRequest::sendAffirmitiveToProfessional(){
	// when client accepts a professional, they get alerted that they were picked
	
}

// these may be better placed in Specialist 

void ServiceRequest::specialisAcceptServiceRequest(){
	// I think this should be called by the specialist and it adds their info to the array of accepted specialists
}

void ServiceRequest::professionalAcknowledgment(){
	// professional acknowledges
	// and this should be called by the specialist which calls the 
}

// this may be better placed in Customer

void ServiceRequest::clientChoosesProfessional(){
	// client chooses from the array of accepted specialists
}


