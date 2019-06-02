#include <string>
#include <fstream>
#include"car.h"
using namespace std;

Car::Car(){}

Car::Car(Customer cust, string licencePlate, int modelYear, string make, string model, string shape, double engineSize, string colour) {
	this->cust_id = cust.custID;
	this->licencePlate = licencePlate;
	this->modelYear = modelYear;
	this->make = make;
	this->model = model;
	this->shape = shape;
	this->engineSize = engineSize;
	this->colour = colour;
}

Car::Car(int cust_id, string licencePlate, int modelYear, string make, string model, string shape, double engineSize, string colour)
 {
	this->cust_id = cust_id;
	this->licencePlate = licencePlate;
	this->modelYear = modelYear;
	this->make = make;
	this->model = model;
	this->shape = shape;
	this->engineSize = engineSize;
	this->colour = colour;
}

int Car::getUser() {
	return cust_id;
}

string Car::getMake() {
	return make;
}

string Car::getModel() {
	return model;
}

int Car::getYear() {
	return modelYear;
}

string Car::getLicencePlate() {
	return licencePlate;
}

string Car::getShape() {
	return shape;
}

double Car::getEngineSize() {
	return engineSize;
}

string Car::getColour() {
	return colour;
}

void Car::save() {
	ofstream outFile;
	outFile.open("Cars.csv", ios_base::app);

	outFile << to_string(cust_id) << "," << make << "," << model << "," << modelYear << "," << licencePlate << "," << shape << "," << engineSize << "," << colour << "\n";
	outFile.close();
}

Car* Car::loadCars() {
	Car* cars;
	int total_cars = 0;
	string line, cust_id, make, model, modelYear, licencePlate, shape, engineSize, colour;
	string userFile = "Cars.csv";

	// Creating input filestream
	ifstream file(userFile);
	while (getline(file, line)) total_cars++;
	cars = new Car[total_cars + 1];

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
	int i = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, cust_id, ','))
		{
			getline(inFile, make, ',');
			getline(inFile, model, ',');
			getline(inFile, modelYear, ',');
			getline(inFile, licencePlate, ',');
			getline(inFile, shape, ',');
			getline(inFile, engineSize, ',');
			getline(inFile, colour);

			cars[i] = Car(stoi(cust_id), licencePlate, stoi(modelYear), make, model, shape, stod(engineSize), colour);
			i++;
		}
		inFile.close();
	}

	return cars;
}