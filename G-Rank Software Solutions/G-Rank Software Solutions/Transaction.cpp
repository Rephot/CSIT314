#include "Transaction.h"

Transaction::Transaction() {}

ServiceRequest Transaction::getRequestData() {
	return requestData;
}

Review Transaction::getReviewData() {
	return reviewData;
}

Receipt Transaction::getReceiptData() {
	return receiptData;
}