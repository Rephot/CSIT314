#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ServiceRequest.h"
#include "reviews.h"
#include "receipts.h"
#include "Specialist.h"

class Transaction {
public:
	Transaction();
	Transaction(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string);
	void create(string, string, string, string, string, string, string, string, string);
	ServiceRequest getRequestData();
	// void saveTransaction();
	string getArea();
	Review getReviewData();
	Receipt getReceiptData();
	static vector<Transaction> GRSSload(string);
	void setSpecialist(Specialist);
	void addAvailableSpecialist(Specialist);
	vector<Specialist> getAvailableSpecialists();
	void loadAvailableSpecialists(vector<Specialist>);
	void saveAvailableSpecialists();
	string getTransactionID();
	string getCustID();
	string getSpecID();
	void GRSScreate(string, string, string, string, string, string, string, string, string, string, string);
	void GRSSsave(string);
	static void GRSSsaveAll(string, vector<Transaction>);
	void GRSSspecialistAvailable(string);
	void GRSSaddReceiptData(string, string, string, string);
	void GRSSaddReviewData(string, string);

private:
	string transactionID, relSpecID, relCustID, amount, callOut, completed;
	ServiceRequest requestData;
	Review reviewData;
	Receipt receiptData;
	vector<Specialist> availableSpecialists;
};

#endif