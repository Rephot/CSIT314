#include"reviews.h"
#include <fstream>
#include <iostream>

int total_reviews;

Reviews::Reviews(){
}

Reviews::Reviews(float rating, string description, string customerName, int relatedRequest, int relatedCustomer, int relatedSpecialist) {
	this->rating = rating;
	this->description = description;
	this->customerName = customerName;
	this->relatedRequest = relatedRequest;
	this->relatedCustomer = relatedCustomer;
	this->relatedSpecialist = relatedSpecialist;
}

float Reviews::getRating() {
	return rating;
}

string Reviews::getDesc() {
	return description;
}

string Reviews::custName() {
	return customerName;
}

int Reviews::getRel_Req() {
	return relatedRequest;
}

int Reviews::getRel_Cust() {
	return relatedCustomer;
}

int Reviews::getRel_Spec() {
	return relatedSpecialist;
}


void Reviews::saveReview(Reviews reviews) {
	ofstream outFile;
	outFile.open("Reviews.csv", ios_base::app);

	outFile << reviews.getRating() << "," << reviews.getDesc() << "," << reviews.custName() << "," << reviews.getRel_Req() << "," << reviews.getRel_Cust() << "," << reviews.getRel_Spec() << "\n";
	outFile.close();
}

Reviews* Reviews::loadReviews() {
	Reviews* reviews;
	total_reviews = 0;
	string rating, line, description, customerName, relatedRequest, relatedCustomer, relatedSpecialist;
	string userFile = "Reviews.csv";

	// Creating input filestream
	ifstream file(userFile);
	while (getline(file, line)) total_reviews++;
	reviews = new Reviews[total_reviews + 1];

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

			reviews[i] = Reviews(stof(rating), description, customerName, stoi(relatedRequest), stoi(relatedCustomer), stoi(relatedSpecialist));
			i++;
		}
		inFile.close();
	}

	return reviews;
}