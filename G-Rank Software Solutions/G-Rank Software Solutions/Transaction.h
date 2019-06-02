#include "ServiceRequest.h"
#include "reviews.h"
#include "receipts.h"

class Transaction {
public:
	Transaction();
	Transaction(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, bool);
	ServiceRequest getRequestData();
	Review getReviewData();
	Receipt getReceiptData();
	static vector<Transaction> GRSSload();

private:
	string transactionID, relSpecID, relCustID;
	bool completed;
	ServiceRequest requestData;
	Review reviewData;
	Receipt receiptData;
};