//specialist inherits user


#include"Specialist.h"

using namespace std;

vector <vector<ServiceRequest>> Specialist::available;

Specialist::Specialist() {

}

Specialist::Specialist(string uname, string pwd, string fname, string lname, time_t dob, string number, string area, int specialistID) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	DOB = dob;
	phNumber = number;
	operationalArea = area;
	this->specialistID = specialistID;
}

void Specialist::viewRequests() {
	for (int i = 0; i < ServiceRequest::numCurrentRequests; i++) {
		if (ServiceRequest::currentRequests[i].incidentLocation == operationalArea) {
			cout << ServiceRequest::toString(ServiceRequest::currentRequests[i]) << endl;
		}
	}
}

void Specialist::selectRequest(int requestID) {
}

void Specialist::returnUser() {
	User::returnUser();//C: User::returnUser() just calls the parent function on the same object that calls this function (inheritance)
	cout << "Operation Area: " << operationalArea << endl;
}