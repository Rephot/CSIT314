//specialist inherits user
//#include"User.h"
#include"Specialist.h"
#include"ServiceRequest.h"

using namespace std;

Specialist::Specialist() {

}

Specialist::Specialist(string uname, string pwd, string fname, string lname, time_t dob, string number, string area, int id) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	DOB = dob;
	phNumber = number;
	operationalArea = area;
	specialistID = id;
}

void Specialist::viewRequests() {
	for (int i = 0; i < ServiceRequest::numCurrentRequests; i++) {
		cout << ServiceRequest::toString(ServiceRequest::currentRequests[i]) << endl;
	}
}

void Specialist::selectRequest() {

}

void Specialist::returnUser() {
	User::returnUser();
	cout << "Operation Area: " << operationalArea << endl;

}