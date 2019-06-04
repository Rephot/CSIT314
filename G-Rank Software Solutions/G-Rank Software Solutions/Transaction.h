#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ServiceRequest.h"
#include "reviews.h"
#include "receipts.h"
#include "Specialist.h"

class Transaction {
public:
	Transaction();
	Transaction(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string);
	void create(string, string, string, string, string, string, string, string, string);
	ServiceRequest getRequestData();
	// void saveTransaction();
	string getArea();
	Review getReviewData();
	Receipt getReceiptData();
	static vector<Transaction> GRSSload(vector<Customer>);
	static void GRSSsave(vector<Transaction>);
	void setSpecialist(Specialist);
	void addAvailableSpecialist(Specialist, string);
	vector<Specialist> getAvailableSpecialists();
	void loadAvailableSpecialists();
	void saveAvailableSpecialists();
	void leaveReview(string, string);
	void generateReceipt(string, string, string, string, string, string, string);

private:
	string transactionID, relSpecID, relCustID, amount, callOut, completed;
	ServiceRequest requestData;
	Review reviewData;
	Receipt receiptData;
	vector<Specialist> availableSpecialists;
};

#endif