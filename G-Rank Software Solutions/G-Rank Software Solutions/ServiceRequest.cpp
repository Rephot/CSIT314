#include"ServiceRequest.h"
#include<fstream>

using namespace std;

int ServiceRequest::numCurrentRequests = 0;
ServiceRequest ServiceRequest::currentRequests[50];
int ServiceRequest::numRequests = 0;

ServiceRequest::ServiceRequest()
{
	clientName = "";
	incidentLocation = "";
	sType = "";
	serviceRequestedAt = "";
	requestID = 0;
}

ServiceRequest::ServiceRequest(string nameSt, string codePost, string numSt, string descLoc, string typeService, string descInc)
{
	stName = nameSt;
	postCode = codePost;
	stNum = numSt;
	locDesc = descLoc;
	serviceType = typeService;
	incDesc = descInc;
}

ServiceRequest::ServiceRequest(string transactionID, string custID, string custCardNum, string custCardExpiry, string stName, string postCode, string stNum, string serviceType, string incDesc) {
	
	time_t timeCreated = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char timeCreatedTime[26];
	ctime_s(timeCreatedTime, 26, &timeCreated);
	string dateTimeRequested = timeCreatedTime;
	clientName = custID;
	incidentLocation = postCode;
	sType = sType;
	serviceRequestedAt = dateTimeRequested;
	requestID = ++numRequests;
}

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

string ServiceRequest::getStName()
{
	return stName;
}

string ServiceRequest::getPostCode()
{
	return postCode;
}

string ServiceRequest::getStNum()
{
	return stNum;
}

string ServiceRequest::getLocDesc()
{
	return locDesc;
}

string ServiceRequest::getServiceType()
{
	return serviceType;
}

string ServiceRequest::getIncDesc()
{
	return incDesc;
}