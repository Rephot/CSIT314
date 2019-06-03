//customer inherits user

#include"Customer.h"

int total_customers1;

Customer::Customer(){
	
}

Customer::Customer(int userID, string uname, string pwd, string fname, string lname, time_t dob, string number) {
	username = uname;
	password = pwd;
	fName = fname;
	lName = lname;
	DOB = dob;
	phNumber = number;
	custID = userID;
}

Customer::Customer(string custID, string uname, string pwd, string fname, string lname, string license_num, string phnumber, string email, string car_year, string car_make, string car_model, string car_shape, string car_colour, string car_engine_size, string sub_flag, string card_num, string security_code, string expiry) {
	this->custID = custID;
	this->username = uname;
	this->password = pwd;
	this->fName = fname;
	this->lName = lname;
	this->phNumber = phnumber;
	this->sub_flag = sub_flag;
	this->card_num = card_num;
	this->security_code = security_code;
	this->expiry = expiry;
	this->licenseNumber = license_num;
	this->email = email;
	this->car_year = car_year;
	this->car_make = car_make;
	this->car_model = car_model;
	this->car_shape = car_shape;
	this->car_colour = car_colour;
	this->car_engine_size = car_engine_size;
}

Customer* Customer::load() {
	Customer* customers;
	total_customers1 = 0;
	string line, custID, uname, pwd, fname, lname, license_num, phnumber, email, car_year, car_make, car_model, car_shape, car_colour, car_engine_size, sub_flag, card_num, security_code, expiry;
	string userFile = "Customers.csv";

	// Creating input filestream
	ifstream file(userFile);
	while (getline(file, line)) total_customers1++;
	customers = new Customer[total_customers1 + 1];

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
	int i = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, custID, '`'))
		{
			getline(inFile, uname, '`');
			getline(inFile, pwd, '`');
			getline(inFile, fname, '`');
			getline(inFile, lname, '`');
			getline(inFile, license_num, '`');
			getline(inFile, phnumber, '`');
			getline(inFile, email, '`');
			getline(inFile, car_year, '`');
			getline(inFile, car_make, '`');
			getline(inFile, car_model, '`');
			getline(inFile, car_shape, '`');
			getline(inFile, car_colour, '`');
			getline(inFile, car_engine_size, '`');
			getline(inFile, sub_flag, '`');
			getline(inFile, card_num, '`');
			getline(inFile, security_code, '`');
			getline(inFile, expiry);

			customers[i] = Customer(custID, uname, pwd, fname, lname, license_num, phnumber, email, car_year, car_make, car_model, car_shape, car_colour, car_engine_size, sub_flag, card_num, security_code, expiry);
			i++;
		}
		inFile.close();
	}

	return customers;
}

vector<Customer> Customer::GRSSload() {
	vector<Customer> customers;
	string line, custID, uname, pwd, fname, lname, license_num, phnumber, email, car_year, car_make, car_model, car_shape, car_colour, car_engine_size, sub_flag, card_num, security_code, expiry;

	// get existing users from file
	ifstream inFile;
	inFile.open("Customers.csv");
	if (inFile.is_open())
	{
		while (getline(inFile, custID, '`'))
		{
			getline(inFile, uname, '`');
			getline(inFile, pwd, '`');
			getline(inFile, fname, '`');
			getline(inFile, lname, '`');
			getline(inFile, license_num, '`');
			getline(inFile, phnumber, '`');
			getline(inFile, email, '`');
			getline(inFile, car_year, '`');
			getline(inFile, car_make, '`');
			getline(inFile, car_model, '`');
			getline(inFile, car_shape, '`');
			getline(inFile, car_colour, '`');
			getline(inFile, car_engine_size, '`');
			getline(inFile, sub_flag, '`');
			getline(inFile, card_num, '`');
			getline(inFile, security_code, '`');
			getline(inFile, expiry);

			customers.push_back(Customer(custID, uname, pwd, fname, lname, license_num, phnumber, email, car_year, car_make, car_model, car_shape, car_colour, car_engine_size, sub_flag, card_num, security_code, expiry));
		}
		inFile.close();
	}

	return customers;
}

void Customer::saveCustomer() {
	ofstream outFile;
	outFile.open("Customers.csv", ios_base::app);

	outFile << custID << "`"
		<< username << "`"
		<< password << "`"
		<< fName << "`"
		<< lName << "`"
		<< licenseNumber << "`"
		<< phNumber << "`"
		<< email << "`"
		<< car_year << "`"
		<< car_make << "`"
		<< car_model << "`"
		<< car_shape << "`"
		<< car_colour << "`"
		<< car_engine_size << "`"
		<< sub_flag << "`"
		<< card_num << "`"
		<< security_code << "`"
		<< expiry << "\n";
	outFile.close();
}

void Customer::returnUser() {
	cout << "custID: " << custID << endl;
	User::returnUser();
}

string Customer::returnSubFlag() {
	return sub_flag;
}

string Customer::getUserName() {
	return username;
}