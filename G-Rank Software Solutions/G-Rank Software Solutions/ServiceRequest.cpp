#include"ServiceRequest.h"
#include"Specialist.h"

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

int ServiceRequest::numCurrentRequests = 0;
ServiceRequest ServiceRequest::currentRequests[50];
int ServiceRequest::numRequests = 0;

ServiceRequest::ServiceRequest() {
	clientName = "";
	incidentLocation = "";
	sType = "";
	serviceRequestedAt = "";
	requestNumber = ++numRequests;
}

void ServiceRequest::broadcastServiceRequest(ServiceRequest newRequest) {
	// place into an array for the specialists to view
	// will be called from the constructor
	// add service request to static member of specialist class
	cout << "This is where the request would be broadcast from!\n" << endl;
	currentRequests[numCurrentRequests++] = newRequest;
	cout << toString(currentRequests[0]);
}

void ServiceRequest::createServiceRequest(/*needs customer who called*/) {//(Customer currentCustomer)
	/*
	some way of acquiring location info
	*/
	/* Test

	*/
	ServiceRequest newRequest;
	// identifying number
	string sType, location, client;
	// shall be replaced by WT form code
	cout << "This is a Test:\nPlease Enter the details of the incident.\nIs it a breakdown or something like a flat tyre? ";
	getline(cin, sType);
	cout << "Where did the incident happen? ";
	getline(cin, location);
	client = "Joshua Groucutt";
	time_t timeCreated = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char timeCreatedTime[26];
	ctime_s(timeCreatedTime, 26, &timeCreated);
	string dateTimeRequested = timeCreatedTime;
	newRequest.clientName = client;
	newRequest.incidentLocation = location;
	newRequest.sType = sType;
	newRequest.serviceRequestedAt = dateTimeRequested;
	broadcastServiceRequest(newRequest);
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

string ServiceRequest::toString() {
	stringstream request;
	request << clientName << " has requested assistance for a " << sType << " service, at " << incidentLocation << ", at the time, " << serviceRequestedAt;
	string requested = request.str();
	return requested;
}

string ServiceRequest::toString(ServiceRequest requestString) {
	stringstream request;
	request << requestString.clientName << " has requested assistance for a " << requestString.sType << " service, at " << requestString.incidentLocation << ", at the time, " << requestString.serviceRequestedAt;
	string requested = request.str();
	return requested;
}