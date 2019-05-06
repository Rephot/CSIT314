// inherits user

//create a roadside assistance professional account{
//	bank account details
//	preferred area of operation
//	generated identifier
//	based on user creation for login account
//}

#include<string>

using namespace std;

class Specialist{
public:
	Specialist();
	void viewRequests();
	void selectRequest();
private:
	// bankAccountClass details;
	string operationalArea;
	int specialistID;
	// User loginAccount;
};