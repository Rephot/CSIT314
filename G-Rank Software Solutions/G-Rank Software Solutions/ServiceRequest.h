#include<iostream>
#include<ctime>
#include<cstring>
#include<sstream>
#include<string>
#include<chrono>
class User;

using namespace std;

class ServiceRequest {
public:
	ServiceRequest();
	void createServiceRequest(User);
	void broadcastServiceRequest(ServiceRequest);
	void displayProfessionalsWhoAccepted();
	void sendAffirmitiveToProfessional();
	void specialisAcceptServiceRequest();
	void professionalAcknowledgment();
	void clientChoosesProfessional();
	string toString();
	static string toString(ServiceRequest);
	// this array will be replaced by either a vector/map or by a WT construct
	static ServiceRequest currentRequests[50];
	static int numCurrentRequests, numRequests;
private:
	string clientName, incidentLocation, sType, serviceRequestedAt;
	int requestNumber;
};