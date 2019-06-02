#include "ServiceRequest.h"
#include "reviews.h"
#include "receipts.h"

class Transaction {
public:
	Transaction();
	ServiceRequest getRequestData();
	Review getReviewData();
	Receipt getReceiptData();

private:
	ServiceRequest requestData;
	Review reviewData;
	Receipt receiptData;
};