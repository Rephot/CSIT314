
#include"ServiceRequest.h"
#include<fstream>


using namespace std;


int ServiceRequest::numCurrentRequests = 0;
ServiceRequest ServiceRequest::currentRequests[50];
int ServiceRequest::numRequests = 0;

void ServiceRequest::saveRequests()
{
	ofstream outFile;
	outFile.open("Requests.csv");

	for (int i = 0; i < numCurrentRequests; i++) {
		outFile << currentRequests[i].clientName << "," << to_string(currentRequests[i].requestID) << "," << currentRequests[i].incidentLocation << "," << currentRequests[i].sType << "," << "0" << "\n";
	}
	//C: serviceRequestedAt has a /n at the end of it for some reason and that causes saving it to use 2 lines so ive substitued 0 in its place for now
	outFile.close();
}

ServiceRequest::ServiceRequest()
{
	clientName = "";
	incidentLocation = "";
	sType = "";
	serviceRequestedAt = "";
	requestID = 0;
}

void ServiceRequest::loadRequests() {
	ServiceRequest serviceReq;
	string line, clientName, requestID, incidentLocation, sType, serviceRequestedAt;
	string userFile = "Requests.csv";

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
	int i = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, clientName, ','))
		{
			getline(inFile, requestID, ',');
			getline(inFile, incidentLocation, ',');
			getline(inFile, sType, ',');
			getline(inFile, serviceRequestedAt);

			serviceReq.clientName = clientName;
			serviceReq.incidentLocation = incidentLocation;
			serviceReq.sType = sType;
			serviceReq.serviceRequestedAt = serviceRequestedAt;
			serviceReq.requestID = stoi(requestID);

			++numRequests;

			broadcastServiceRequest(serviceReq);

			i++;
		}
		inFile.close();
	}
}

void ServiceRequest::broadcastServiceRequest(ServiceRequest newRequest) {
	// place into an array for the specialists to view
	// will be called from the constructor
	// add service request to static member of specialist class
	currentRequests[numCurrentRequests++] = newRequest;
	newRequest.saveRequests();
}

void ServiceRequest::createServiceRequest(Customer user) {
	ServiceRequest newRequest;
	// identifying number
	string sType, location, client;
	// shall be replaced by WT form code
	cout << "Please Enter the details of the incident.\nIs it a breakdown or something like a flat tyre ? ";
	getline(cin, sType);
	cout << "Where is the incident? ";
	getline(cin, location);
	client = user.getFullName();
	time_t timeCreated = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char timeCreatedTime[26];
	ctime_s(timeCreatedTime, 26, &timeCreated);
	string dateTimeRequested = timeCreatedTime;
	newRequest.clientName = client;
	newRequest.incidentLocation = location;
	newRequest.sType = sType;
	newRequest.serviceRequestedAt = dateTimeRequested;
	newRequest.requestID = ++numRequests;
	broadcastServiceRequest(newRequest);
}

// a get function that returns the array of professionals that accepted
int ServiceRequest::displayProfessionalsWhoAccepted(int requestID) {
	// lets client see who is available to help
	// displays formatted data from an array
	
	return 0;
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
	request << requestString.requestID << " " << requestString.clientName << " has requested assistance for a " << requestString.sType << " service, at " << requestString.incidentLocation << ", at the time, " << requestString.serviceRequestedAt;
	string requested = request.str();
	return requested;
}