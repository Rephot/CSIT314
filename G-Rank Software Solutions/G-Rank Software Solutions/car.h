#ifndef CAR_H
#define CAR_H

#include <string>
#include "Customer.h"
using namespace std;

class Car{
public:
	Car();
	Car(Customer, string, int, string, string, string, double, string);
	Car(int, string, int, string, string, string, double, string);
	int getUser();
	string getMake();
	string getModel();
	int getYear();
	string getLicencePlate();
	string getShape();
	double getEngineSize();
	string getColour();
	void save();
	Car* loadCars();
private:
	int cust_id, modelYear;
	string make, model, licencePlate, colour, shape;
	double engineSize;
};

#endif