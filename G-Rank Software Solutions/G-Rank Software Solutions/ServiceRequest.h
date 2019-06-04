#ifndef SERVICEREQUEST_H
#define SERVICEREQUEST_H

#include<iostream>
#include<ctime>
#include<cstring>
#include<sstream>
#include<string>
#include<chrono>
#include"Customer.h"
//#include"Specialist.h"

using namespace std;

class ServiceRequest {
public:
	ServiceRequest();
	ServiceRequest(string, string, string, string, string, string);
	ServiceRequest(string, string, string, string, string, string, string, string, string);
	void saveRequests();
	void createServiceRequest(Customer);
	void broadcastServiceRequest(ServiceRequest);
	void loadRequests();
	string toString(), incidentLocation;
	static string toString(ServiceRequest);
	// this array will be replaced by either a vector/map or by a WT construct
	static ServiceRequest currentRequests[50];
	static int numCurrentRequests, numRequests;
	int requestID;
	string getStName();
	string getPostCode();
	string getStNum();
	string getLocDesc();
	string getServiceType();
	string getIncDesc();
private:
	string clientName, sType, serviceRequestedAt;
	string stName, postCode, stNum, locDesc, serviceType, incDesc;
	
};
#endif
