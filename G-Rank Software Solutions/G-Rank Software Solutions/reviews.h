#ifndef REVIEWS_H
#define REVIEWS_H

#include<string>
#include<sstream>
#include<iostream>
#include<ctime>
#include<Windows.h>

#include "Customer.h"

using namespace std;

class Review {
public:
	Review();
	Review(string, string);
	string getJobRating();
	string getReviewDesc();
	void setJobRating(string);
	void setJobReview(string);

private:
	string jobRating, reviewDesc;
};

#endif