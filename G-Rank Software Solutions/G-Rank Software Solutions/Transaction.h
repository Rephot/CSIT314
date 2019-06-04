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
	static vector<Transaction> GRSSload(string);
	void GRSScreate(string, string, string, string, string, string, string, string, string, string, string);
	void GRSSsave(string);
	static void GRSSsaveAll(string, vector<Transaction>);
	void GRSSspecialistAvailable(string);
	void GRSSaddReceiptData(string, string, string, string);
	void GRSSaddReviewData(string, string);
	ServiceRequest getRequestData();
	Review getReviewData();
	Receipt getReceiptData();
	string getRelSpec();
	string getTransactionID();
	string getCustID();
	string getSpecID();

private:
	string transactionID, relSpecID, relCustID, completed;
	ServiceRequest requestData;
	Review reviewData;
	Receipt receiptData;
};

#endif