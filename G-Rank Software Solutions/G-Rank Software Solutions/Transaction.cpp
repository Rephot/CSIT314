#include "Transaction.h"
#include "GRSS.h"

Transaction::Transaction() {}

Transaction::Transaction(string transactionID, string specID, string custID, string isComplete,
	string specBSB, string specAccNum, string specAccName, string custCardNum, string custCardExpiry,
	string stName, string postCode, string stNum, string serviceType, string incDesc,
	string jobRating, string reviewDesc, string callFee, string amountDue)
{
	this->transactionID = transactionID;
	relSpecID = specID;
	relCustID = custID;
	completed = isComplete;
	receiptData = Receipt(specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, callFee, amountDue);
	requestData = ServiceRequest(stName, postCode, stNum, serviceType, incDesc);
	reviewData = Review(jobRating, reviewDesc);
}

void Transaction::create(string transactionID, string custID, string custCardNum, string custCardExpiry, string stName, string postCode, string stNum, string serviceType, string incDesc) {
	this->transactionID = transactionID;
	relCustID = custID;
	completed = "0";
	requestData = ServiceRequest(transactionID, custID, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc);
	reviewData = Review();
	receiptData = Receipt();
}

string Transaction::getArea() {
	return requestData.getPostCode();
}

void Transaction::setSpecialist(Specialist spec) {
	relSpecID = spec.specialistID;
}

void Transaction::addAvailableSpecialist(Specialist spec) {
	availableSpecialists.push_back(spec);
}

void Transaction::loadAvailableSpecialists(vector<Specialist> spec) {
	string transID, specialists;
	string userFile = "availableSpecialists.csv";


	ifstream inFile;
	inFile.open(userFile);
	if (inFile.is_open())
	{
		while (getline(inFile, transID, '`'))
		{
			getline(inFile, specialists);
			if (transID == this->transactionID) {
				std::stringstream ss(specialists);
				std::string token;
				while (std::getline(ss, token, '|')) {
					for (std::vector<Specialist>::iterator it = spec.begin(); it != spec.end(); ++it) {
						if (it->specialistID == token) availableSpecialists.push_back(*it);
					}
				}
			}
			
		}
		inFile.close();
	}
}

void Transaction::saveAvailableSpecialists()
{
	ofstream outFile;
	outFile.open("availableSpecialists.csv");

	outFile << transactionID << "`";

	vector<Specialist>::iterator it = availableSpecialists.begin();
	while (it != availableSpecialists.end())
	{
		outFile << it->specialistID << "|";
		it++;
	}

	outFile << "\n";

	outFile.close();
}

vector<Specialist> Transaction::getAvailableSpecialists() {
	return availableSpecialists;
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

vector<Transaction> Transaction::GRSSload(vector<Customer> existingCustomers) {
	vector<Transaction> transactions;
	string transactionID, specID, custID, specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc, jobRating, reviewDesc, callOut, amount, completed;

	// get previous transactions from file
	ifstream inFile;
	inFile.open("Transactions.csv");
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
			getline(inFile, serviceType, '`');
			getline(inFile, incDesc, '`');
			getline(inFile, jobRating, '`');
			getline(inFile, reviewDesc);

			transactions.push_back(Transaction(transactionID, specID, custID, completed, specBSB, specAccNum, specAccName, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc, jobRating, reviewDesc, callOut, amount));
		}
	}
	inFile.close();

	return transactions;
}

void Transaction::GRSSsave(vector<Transaction> previousTransactions)
{
	ofstream outFile;
	outFile.open("Transactions.csv");

	vector<Transaction>::iterator it = previousTransactions.begin();
	while (it != previousTransactions.end())
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
			<< it->requestData.getServiceType() << "`"
			<< it->requestData.getIncDesc() << "`"
			<< it->reviewData.getJobRating() << "`"
			<< it->reviewData.getReviewDesc() << "\n";
		it++;
	}
	outFile.close();
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
