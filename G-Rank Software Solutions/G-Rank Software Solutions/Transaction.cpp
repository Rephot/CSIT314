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

void Transaction::create(string transactionID, string custID, string custCardNum, string custCardExpiry, string stName, string postCode, string stNum, string serviceType, string incDesc) {
	this->transactionID = transactionID;
	relCustID = custID;
	completed = "0";
	requestData = ServiceRequest(transactionID, custID, custCardNum, custCardExpiry, stName, postCode, stNum, serviceType, incDesc);
	reviewData = Review();
	receiptData = Receipt();
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

void Transaction::leaveReview(string jobRating, string reviewDesc) {
	if (completed == "1") {
		reviewData = Review(jobRating, reviewDesc);
	}
	else {
		cout << "Transaction is not complete, you cannot leave a review" << endl;
	}
}

void Transaction::generateReceipt(string specBSB, string specAccNum, string specAccName, string custCardNum, string custCardExpiry, string callFee, string amountDue) {

}

string Transaction::getArea() {
	return requestData.getPostCode();
}

void Transaction::setSpecialist(Specialist spec) {
	relSpecID = spec.specialistID;
}

void Transaction::complete(Customer cust) {
	completed = "1";
	Specialist spec;
	for (std::vector<Specialist>::iterator it = availableSpecialists.begin(); it != availableSpecialists.end(); ++it) {
		if (it->specialistID == relSpecID) {
			spec = *it;
		}
	}
	receiptData = Receipt(spec.getBsb(), spec.getAccount_num(), spec.getAccount_name(), cust.getCardNumber(), cust.getCardExpiry(), spec.callOutFee, spec.callOutFee);
}

void Transaction::addAvailableSpecialist(Specialist spec, string price) {
	availableSpecialists.push_back(spec);
	availableSpecialists.back().callOutFee = price;
}

string Transaction::getRelSpec() {
	return relSpecID;
}

void Transaction::loadAvailableSpecialists() {
	string transID, specialists, specID, uname, pwd, fname, lname, license_num, phnumber, email, qualification_num, bsb, acc_num, acc_name, areas, callOut;
	string userFile = "availableSpecialists.csv";


	ifstream inFile;
	inFile.open(userFile);
	if (inFile.is_open())
	{
		while (getline(inFile, transID, ','))
		{
			getline(inFile, specialists);
			if (transID == this->transactionID) {
				
				
				std::stringstream ss(specialists);

				getline(ss, specID, '`');
				getline(ss, uname, '`');
				getline(ss, pwd, '`');
				getline(ss, fname, '`');
				getline(ss, lname, '`');
				getline(ss, license_num, '`');
				getline(ss, phnumber, '`');
				getline(ss, email, '`');
				getline(ss, qualification_num, '`');
				getline(ss, areas, '`');
				getline(ss, bsb, '`');
				getline(ss, acc_num, '`');
				getline(ss, acc_name, '`');
				getline(ss, callOut);

				Specialist s = Specialist(specID, uname, pwd, fname, lname, license_num, phnumber, email, qualification_num, bsb, acc_num, acc_name);
				std::stringstream sss(areas);
				std::string token;
				while (std::getline(sss, token, '|')) {
					s.operationalAreas.push_back(token);
				}

				this->addAvailableSpecialist(s, callOut);
			}
			
		}
		inFile.close();
	}
}

void Transaction::saveAvailableSpecialists()
{
	ofstream outFile;
	outFile.open("availableSpecialists.csv");

	outFile << transactionID << ",";

	vector<Specialist>::iterator it = availableSpecialists.begin();
	while (it != availableSpecialists.end())
	{
		outFile << it->specialistID << "`"
			<< it->getUserName() << "`"
			<< it->getPassword() << "`"
			<< it->getFirstName() << "`"
			<< it->getLastName() << "`"
			<< it->getLicenseNumber() << "`"
			<< it->getNumber() << "`"
			<< it->getEmail() << "`"
			<< it->getQualification() << "`";

		for (std::vector<string>::iterator t = it->operationalAreas.begin(); t != it->operationalAreas.end(); ++t) {
			if (t != it->operationalAreas.begin()) outFile << "|";
			outFile << *t;
		}

		outFile << "`"
			<< it->getBsb() << "`"
			<< it->getAccount_num() << "`"
			<< it->getAccount_name() << "`"
			<< it->callOutFee << "\n";
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
