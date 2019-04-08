#include<iostream>
#include<cstring>
#include"ServiceRequest.h"

using namespace std;

/*
created
broadcast
accept request
display accepted
client chooses
sends affirmative to professional
// do we need a second level of confirmation?
*/

ServiceRequest recentRequests[]; // dynamically allocated as learnt in CSCI203
static int activeRequests;
string displayAcceptedSpecialists[];

struct location{
	int streetNo;
	string streetName;
	string suburb;
	string description;
	
};

struct customerInfo{
	string car; // will be a car object when that is made
	string name; // will be a first and last if necessary
	// will add more if necessary, if you happen to think of any, please add them
};

ServiceRequest::ServiceRequest(){
	//customer who created and all associated data(name, user type, car information), location details provided, 
	customerInfo raisedBy;
	location incidentOccuredAt;
	broadcastServiceRequest();
}

ServiceRequest::createServiceRequest(/*needs customer who called*/){//(Customer currentCustomer)
	ServiceRequest newRequest;
	/*
	some way of acquiring location info
	*/
	// test
	customerInfo client;
	client.car = "Beepy McBeepFace";
	client.name = "Shouty McShoutFace";
	location incidentLocation;
	incidentLocation.streetNo = 13;
	incidentLocation.streetName = "University Lane";
	incidentLocation.suburb = "Keiraville";
	incidentLocation.description = "Someone slashed my tyres whilst I was in class!!";
	newRequest = new ServiceRequest(client, incidentLocation);
}

ServiceRequest::broadcastServiceRequest{
	// place into an array for the specialists to view
	// will be called from the constructor
	recentRequests[activeRequests++] = newRequest;
}

// a get function that returns the array of professionals that accepted
ServiceRequest::displayProfessionalsWhoAccepted{
	// lets client see who is available to help
	// displays formatted data from an array
	return displayAcceptedSpecialists;
}

ServiceRequest::sendAffirmitiveToProfessional{
	// when client accepts a professional, they get alerted that they were picked
	
}

// these may be better placed in Specialist 

ServiceRequest::specialisAcceptServiceRequest{
	// I think this should be called by the specialist and it adds their info to the array of accepted specialists
}

ServiceRequest::professionalAcknowledgment{
	// professional acknowledges
	// and this should be called by the specialist which calls the 
}

// this may be better placed in Customer

ServiceRequest::clientChoosesProfessional{
	// client chooses from the array of accepted specialists
}


