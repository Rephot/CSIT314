#include"reviews.h"

Review::Review(){

}

void Review::createReview()
{
}

void Review::createReview() {
	stringstream reviewOut;
	Review rev;
	float rating;
	int specialistID, requestID;
	string reviewDescription;
	time_t timeCreated;
	cout << "Please enter the request identification that this review is for: ";
	cin >> requestID;
	cout << "Please enter the identification number of the specialist that assisted you: ";
	cin >> specialistID;
	cout << "Out of 10, what would you rate your interaction with this specialist: ";
	// check if float
	cin >> rating;
	cout << "Would you like to add a review description (optional): ";
	getline(cin, reviewDescription);
	rev.rating = rating;
	rev.description = reviewDescription;
	rev.relatedRequest = requestID;
	rev.relatedSpecialist = specialistID;
	rev.relatedCustomer = ""; // customer.name or ID number;
}