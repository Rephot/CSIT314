#include "Transaction.h"
#include "GRSS.h"

Transaction::Transaction() {}

Transaction::Transaction(string transactionID, string specID, string custID, string isComplete,
	string specBSB, string specAccNum, string specAccName, string custCardNum, string custCardExpiry,
	string stName, string postCode, string stNum, string locDesc, string serviceType, string incDesc,
	string jobRating, string reviewDesc, string callFee, string amountDue)
{
	this->transactionID = transactionID;
	relSpecID = specID;
	relCustID = custID;
	completed = isComplete;
	receiptData = Receipt(specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, callFee, amountDue);
	requestData = ServiceRequest(stName, postCode, stNum, locDesc, serviceType, incDesc);
	reviewData = Review(jobRating, reviewDesc);
}

void Transaction::GRSScreate(string transactionID, string custID, string custCardNum, string custCardExpiry, string stName, string postCode, string stNum, string locDesc, string serviceType, string incDesc, string subFlag) {
	this->transactionID = transactionID;
	relCustID = custID;
	completed = "0";
	requestData = ServiceRequest(stName, postCode, stNum, locDesc, serviceType, incDesc);
	string callout;
	(subFlag == "0") ? callout = "0" : callout = "50";
	receiptData = Receipt("", "", "", custCardNum, custCardExpiry, callout, "");
}

void Transaction::GRSSspecialistAvailable(string specID)
{
	relSpecID = specID;
}

void Transaction::GRSSaddReviewData(string rating, string description)
{
	reviewData.setJobRating(rating);
	reviewData.setJobReview(description);
}

void Transaction::GRSSaddReceiptData(string bsb, string accnum, string accname, string servicecost)
{
	receiptData.setBSB(bsb);
	receiptData.setAccNum(accnum);
	receiptData.setAccName(accname);
	receiptData.setServiceCost(servicecost);
}

string Transaction::getRelSpec() {
	return relSpecID;
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

string Transaction::getTransactionID()
{
	return transactionID;
}

string Transaction::getCustID()
{
	return relCustID;
}

string Transaction::getSpecID()
{
	return relSpecID;
}

vector<Transaction> Transaction::GRSSload(string fileString) {
	vector<Transaction> transactions;
	string transactionID, specID, custID, specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc, jobRating, reviewDesc, callOut, amount, completed, locDesc;

	// get previous transactions from file
	ifstream inFile;
	inFile.open(fileString);
	if (inFile.is_open())
	{
		while (getline(inFile, transactionID, '`'))
		{
			getline(inFile, specID, '`');
			getline(inFile, custID, '`');
			getline(inFile, completed, '`');
			getline(inFile, specBSB, '`');
			getline(inFile, specAccNum, '`');
			getline(inFile, specAccName, '`');
			getline(inFile, custCardNum, '`');
			getline(inFile, custCardExpiry, '`');
			getline(inFile, callOut, '`');
			getline(inFile, amount, '`');
			getline(inFile, stName, '`');
			getline(inFile, postCode, '`');
			getline(inFile, stNum, '`');
			getline(inFile, locDesc, '`');
			getline(inFile, serviceType, '`');
			getline(inFile, incDesc, '`');
			getline(inFile, jobRating, '`');
			getline(inFile, reviewDesc);

			transactions.push_back(Transaction(transactionID, specID, custID, completed, specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, stName, postCode, stNum, locDesc, serviceType, incDesc, jobRating, reviewDesc, callOut, amount));
		}
	}
	inFile.close();

	return transactions;
}

void Transaction::GRSSsave(string fileString)
{
	ofstream outFile;
	outFile.open(fileString, ios_base::app);

	outFile << transactionID << "`"
		<< relSpecID << "`"
		<< relCustID << "`"
		<< completed << "`"
		<< receiptData.getBSB() << "`"
		<< receiptData.getAccNum() << "`"
		<< receiptData.getAccName() << "`"
		<< receiptData.getCardNum() << "`"
		<< receiptData.getCardExpiry() << "`"
		<< receiptData.getCallOut() << "`"
		<< receiptData.getServiceCost() << "`"
		<< requestData.getStName() << "`"
		<< requestData.getPostCode() << "`"
		<< requestData.getStNum() << "`"
		<< requestData.getLocDesc() << "`"
		<< requestData.getServiceType() << "`"
		<< requestData.getIncDesc() << "`"
		<< reviewData.getJobRating() << "`"
		<< reviewData.getReviewDesc() << "\n";

	outFile.close();
}

void Transaction::GRSSsaveAll(string fileString, vector<Transaction> inPut)
{

	ofstream outFile;
	outFile.open(fileString);

	vector<Transaction>::iterator it = inPut.begin();
	if (outFile.is_open()) {
		while (it != inPut.end())
		{
			outFile << it->transactionID << "`"
				<< it->relSpecID << "`"
				<< it->relCustID << "`"
				<< it->completed << "`"
				<< it->receiptData.getBSB() << "`"
				<< it->receiptData.getAccNum() << "`"
				<< it->receiptData.getAccName() << "`"
				<< it->receiptData.getCardNum() << "`"
				<< it->receiptData.getCardExpiry() << "`"
				<< it->receiptData.getCallOut() << "`"
				<< it->receiptData.getServiceCost() << "`"
				<< it->requestData.getStName() << "`"
				<< it->requestData.getPostCode() << "`"
				<< it->requestData.getStNum() << "`"
				<< it->requestData.getLocDesc() << "`"
				<< it->requestData.getServiceType() << "`"
				<< it->requestData.getIncDesc() << "`"
				<< it->reviewData.getJobRating() << "`"
				<< it->reviewData.getReviewDesc() << "\n";
		}
	}
	outFile.close();
}
