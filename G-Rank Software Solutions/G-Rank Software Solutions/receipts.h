/*

job gets done
create invoice
create and send receipt
create and update system with reviews and info about customer if needed

*/

//create a way to pay professionals for a service completion{
//	transaction ID
//	amount
//	subscribed or not - include callout fee in this transaction
//	time
//	customer identifier
//	specialist identifier
//	?vehicle identification? if specialists are fleet
//}

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
	Receipt(int, float, bool, time_t, int, int, int);
	Receipt(string, string, string, string, string, string, string);
	void generateReceipt();
	static int numReceipts;
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
	int receiptID;
	float amount;
	bool subscribed;
	time_t timeOf;
	int custID; // acquired from the customer involved in the transaction
	int specialistID; // acquired from the specialist involved in the transaction
	int requestID; // acquired from the request that has been fulfilled
};

#endif