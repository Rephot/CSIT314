#include<iostream>
#include<ctime>
#include<cstring>

using namespace std;

class ServiceRequest {
public:
	ServiceRequest();
	ServiceRequest(string, string, string, time_t);
	void createServiceRequest();
	void broadcastServiceRequest(ServiceRequest);
	void displayProfessionalsWhoAccepted();
	void sendAffirmitiveToProfessional();
	void specialisAcceptServiceRequest();
	void professionalAcknowledgment();
	void clientChoosesProfessional();
private:
	string clientName, incidentLocation, sType;
	time_t serviceRequestedAt;
};