//specialist inherits user

#include"Specialist.h"
#include"ServiceRequest.h"

using namespace std;

Specialist::Specialist() {

}

void Specialist::viewRequests() {
	for (int i = 0; i < ServiceRequest::numCurrentRequests; i++) {
		cout << ServiceRequest::toString(ServiceRequest::currentRequests[i]) << endl;
	}
}

void Specialist::sendAvailable() {

}