#include<iostream>
#include<ctime>
#include<cstring>

using namespace std;

class ServiceRequest {
public:
	ServiceRequest();
	ServiceRequest(string, string, string, string);
	void createServiceRequest();
	void broadcastServiceRequest(ServiceRequest);
	void displayProfessionalsWhoAccepted();
	void sendAffirmitiveToProfessional();
	void specialisAcceptServiceRequest();
	void professionalAcknowledgment();
	void clientChoosesProfessional();
	string toString();
	static ServiceRequest currentRequests[50];
	static int numRequests;
private:
	string clientName, incidentLocation, sType, serviceRequestedAt;
};