#include<string>
#include<sstream>
#include<iostream>
#include<ctime>

using namespace std;

//create review for roadside assistance professional related to a request{
//	rating out of 10 ?
//	reveiw description(max char length ? )
//	customer username / name
//	pulls request identifier
//	pulls customer identifier
//	pulls specialist identifier
//}

class Review {
public:
	Review();
	Review(float, string, string, int, int, int);
	float getRating();
	string getDesc();
	string custName();
	int getRel_Req();
	int getRel_Cust();
	int getRel_Spec();
	void saveReview(Reviews);
	Reviews* loadReviews();
	void createReview(); // types are temporary will replace with more suitable
private:
	float rating;
	string description, customerName, relatedCustomer;
	int relatedRequest, relatedSpecialist;
};