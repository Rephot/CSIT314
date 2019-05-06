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
	Reviews();
private:
	float rating;
	string description;
	string customerName;
	int relatedRequest;
	int relatedCustomer;
	int relatedSpecialist;
};