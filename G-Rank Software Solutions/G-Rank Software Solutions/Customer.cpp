//customer inherits user

#include"Customer.h"


Customer::Customer(){
	
}

Customer::Customer(string uname, string pwd, string fname, string lname, time_t dob, string number) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	DOB = dob;
	phNumber = number;
}
