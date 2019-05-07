#include<string>

using namespace std;

//create review for roadside assistance professional related to a request{
//	rating out of 10 ?
//	reveiw description(max char length ? )
//	customer username / name
//	pulls request identifier
//	pulls customer identifier
//	pulls specialist identifier
//}

class Reviews {
public:
	Reviews(float, string, string, int, int, int);
	Reviews();
	float getRating();
	string getDesc();
	string custName();
	int getRel_Req();
	int getRel_Cust();
	int getRel_Spec();
	void saveReview(Reviews);
	Reviews* loadReviews();
private:
	float rating;
	string description;
	string customerName;
	int relatedRequest;
	int relatedCustomer;
	int relatedSpecialist;
};