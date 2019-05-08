#include"reviews.h"
#include <fstream>
#include <iostream>

int total_reviews;

Review::Review(){

}

Review::Review(float rating, string description, string customerName, int relatedRequest, int relatedCustomer, int relatedSpecialist) {
	this->rating = rating;
	this->description = description;
	this->customerName = customerName;
	this->relatedRequest = relatedRequest;
	this->relatedCustomer = relatedCustomer;
	this->relatedSpecialist = relatedSpecialist;
}

float Review::getRating() {
	return rating;
}

string Review::getDesc() {
	return description;
}

string Review::custName() {
	return customerName;
}

int Review::getRel_Req() {
	return relatedRequest;
}

int Review::getRel_Cust() {
	return relatedCustomer;
}

int Review::getRel_Spec() {
	return relatedSpecialist;
}


void Review::saveReview(Review reviews) {
	ofstream outFile;
	outFile.open("Reviews.csv", ios_base::app);

	outFile << reviews.getRating() << "," << reviews.getDesc() << "," << reviews.custName() << "," << reviews.getRel_Req() << "," << reviews.getRel_Cust() << "," << reviews.getRel_Spec() << "\n";
	outFile.close();
}

Review* Review::loadReviews() {
	Review* reviews;
	total_reviews = 0;
	string rating, line, description, customerName, relatedRequest, relatedCustomer, relatedSpecialist;
	string userFile = "Reviews.csv";

	// Creating input filestream
	ifstream file(userFile);
	while (getline(file, line)) total_reviews++;
	reviews = new Review[total_reviews + 1];

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
	int i = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, rating, ','))
		{
			getline(inFile, description, ',');
			getline(inFile, customerName, ',');
			getline(inFile, relatedRequest, ',');
			getline(inFile, relatedCustomer, ',');
			getline(inFile, relatedSpecialist);

			reviews[i] = Review(stof(rating), description, customerName, stoi(relatedRequest), stoi(relatedCustomer), stoi(relatedSpecialist));
			i++;
		}
		inFile.close();
	}

	return reviews;
}

void Review::createReview(Customer logged_in_user) {
	stringstream reviewIn;
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
	cin.ignore();
	getline(cin, reviewDescription, '\n');
	cout << reviewDescription;
	Sleep(5000);
	rev = Review(rating, reviewDescription, logged_in_user.getFullName(), requestID, logged_in_user.custID, specialistID);
	saveReview(rev);
}