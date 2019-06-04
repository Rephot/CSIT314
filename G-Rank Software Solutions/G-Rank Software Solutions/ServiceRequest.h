#ifndef SERVICEREQUEST_H
#define SERVICEREQUEST_H

#include<iostream>
#include<ctime>
#include<cstring>
#include<sstream>
#include<string>
#include<chrono>

#include"Customer.h"

using namespace std;

class ServiceRequest {
public:
	ServiceRequest();
	ServiceRequest(string, string, string, string, string, string);
	string getStName();
	string getPostCode();
	string getStNum();
	string getLocDesc();
	string getServiceType();
	string getIncDesc();

private:
	string stName, postCode, stNum, locDesc, serviceType, incDesc;
};

#endif