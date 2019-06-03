#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ServiceRequest.h"
#include "reviews.h"
#include "receipts.h"

class Transaction {
public:
	Transaction();
	Transaction(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string);
	void create(string, string, string, string, string, string, string, string, string);
	ServiceRequest getRequestData();
	//void saveTransaction();
	Review getReviewData();
	Receipt getReceiptData();
	static vector<Transaction> GRSSload(vector<Customer>);
	static void GRSSsave(vector<Transaction>);

private:
	string transactionID, relSpecID, relCustID, amount, callOut, completed;
	ServiceRequest requestData;
	Review reviewData;
	Receipt receiptData;
};

#endif