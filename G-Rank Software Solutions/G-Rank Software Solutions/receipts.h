#ifndef RECEIPTS_H
#define RECEIPTS_H

#include<ctime>
#include<chrono>
#include<string>
#include<cstring>

using namespace std;

class Receipt {
public:
	Receipt();
	Receipt(string, string, string, string, string, string, string);
	string getBSB();
	string getAccNum();
	string getAccName();
	string getCardNum();
	string getCardExpiry();
	string getCallOut();
	string getServiceCost();
	void setBSB(string);
	void setAccNum(string);
	void setAccName(string);
	void setServiceCost(string);

private:
	string BSB, accNum, accName, cardNum, cardExpiry, callOut, serviceCost;
};

#endif