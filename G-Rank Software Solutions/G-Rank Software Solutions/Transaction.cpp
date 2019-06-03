#include "Transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(string transactionID, string specID, string custID, string specBSB, string specAccNum, string specAccName, string custCardNum, string custCardExpiry, string stName, string postCode, string stNum, string serviceType, string incDesc, string jobRating, string reviewDesc, bool isComplete)
{
	this->transactionID = transactionID;
	relSpecID = specID;
	relCustID = custID;
	completed = isComplete;
	requestData = ServiceRequest();
	reviewData = Review();
	receiptData = Receipt();
}

void Transaction::create(string transactionID, string custID, string custCardNum, string custCardExpiry, string stName, string postCode, string stNum, string serviceType, string incDesc) {
	this->transactionID = transactionID;
	relCustID = custID;
	completed = false;
	requestData = ServiceRequest(transactionID, custID, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc);
	reviewData = Review();
	receiptData = Receipt();
}

ServiceRequest Transaction::getRequestData() {
	return requestData;
}

Review Transaction::getReviewData() {
	return reviewData;
}

Receipt Transaction::getReceiptData() {
	return receiptData;
}

vector<Transaction> Transaction::GRSSload() {
	vector<Transaction> transactions;
	string transactionID, specID, custID, specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc, jobRating, reviewDesc;

	// get previous transactions from file
	ifstream inFile;
	inFile.open("Transactions.csv");
	if (inFile.is_open())
	{
		while (getline(inFile, transactionID, '`'))
		{
			getline(inFile, specID, '`');
			getline(inFile, custID, '`');
			getline(inFile, specBSB, '`');
			getline(inFile, specAccNum, '`');
			getline(inFile, specAccName, '`');
			getline(inFile, custCardNum, '`');
			getline(inFile, custCardExpiry, '`');
			getline(inFile, stName, '`');
			getline(inFile, postCode, '`');
			getline(inFile, stNum, '`');
			getline(inFile, serviceType, '`');
			getline(inFile, incDesc, '`');
			getline(inFile, jobRating, '`');
			getline(inFile, reviewDesc);

			transactions.push_back(Transaction(transactionID, specID, custID, specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc, jobRating, reviewDesc, true));
		}
	}

	return transactions;
}

/*void Transaction::saveTransaction() {
	ofstream outFile;
	outFile.open("Transactions.csv", ios_base::app);

	outFile << transactionID << "`"
		<< specID << "`"
		<< custID << "`"
		<< specBSB << "`"
		<< specAccNum << "`"
		<< specAccName << "`"
		<< custCardNum << "`"
		<< custCardExpiry << "`"
		<< stName << "`"
		<< postCode << "`"
		<< serviceType << "`"
		<< jobRating << "`"
		<< reviewDesc << "\n";
	outFile.close();
}*/
