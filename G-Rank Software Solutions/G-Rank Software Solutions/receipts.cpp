/*

job gets done
create invoice
create and send receipt
create and update system with reviews and info about customer if needed

*//*
create a way to pay professionals on service completion, this could also be considered receipt generation considering the information that we generate{
	access bank details of specialist for payment - not necessary for receipt?
	receipt has:
		time (consider whether it should include both time request, time of payment or both)
		transaction ID (should be generated from a static variable that increases after each transaction is processed)
		amount (the amount charged for the particular service type)
		subscribed or not - include callout fee in this transaction (this will only appear on PoD user receipts)
		customer identifier (auto filled from ServiceRequest info, ie ServiceRequest should have Customer that is related to it)
		specialist identifier (auto filled from ServiceRequest info, ie ServiceRequest should have Specialist that is related to it, but only after the Specialist has confirmed to take on the job)
		?vehicle identification? if specialists are fleet - this is more required from the company's point of view, as a mini insurance thing, so they know which vehicle was where, and with who
			shall ask whether this information is required, if so there will be a fleet truck class, wtih:
			- truck rego
			- truck ID
			- truck status: {available, assigned, maintainanceRequired)
}*/

#include"Receipts.h"

int Receipt::numReceipts = 0;

Receipt::Receipt() {

}

Receipt::Receipt(int recID, float amt, bool subbed, time_t generated, int customerID, int specID, int reqID) {
	receiptID = recID;
	amount = amt;
	subscribed = subbed;
	timeOf = generated;
	custID = customerID;
	specialistID = specID;
	requestID = reqID;
}

Receipt::Receipt(string specBSB, string specAccNum, string specAccName, string custCardNum, string custCardExpiry, string callFee, string amountDue)
{
	BSB = specBSB;
	accNum = specAccNum;
	accName = specAccName;
	cardNum = custCardNum;
	cardExpiry = custCardExpiry;
	callOut = callFee;
	serviceCost = amountDue;
}

void Receipt::generateReceipt(/*passed specialist, serviceRequest, and customer related to transaction*/) {
	/*
	format
		dateTime
		receiptID
		if(subscribed) amount += callOutFee(const double)
		paid to relSpecialist
		your bankCard details **** **** **** 1234 ?? maybe
		amount
	*/
	Receipt rec;
	char createdTime[26];
	time_t timeCreated = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	ctime_s(createdTime, 26, &timeCreated);
	string dateTime = createdTime;
	int recNum = ++numReceipts;
	float amountToPay = 234.50; // switch on job type?
	// if(customer.subscribed) amountToPay += callOutFee;
	int specID = 20; // access specialist.specialistID;
	int reqID = 34; // access serviceRequest.requestID;

}

string Receipt::getBSB()
{
	return BSB;
}

string Receipt::getAccNum()
{
	return accNum;
}

string Receipt::getAccName()
{
	return accName;
}

string Receipt::getCardNum()
{
	return cardNum;
}

string Receipt::getCardExpiry()
{
	return cardExpiry;
}

string Receipt::getCallOut()
{
	return callOut;
}

string Receipt::getServiceCost()
{
	return serviceCost;
}

void Receipt::setBSB(string specbsb)
{
	BSB = specbsb;
}

void Receipt::setAccNum(string specAccNum)
{
	accNum = specAccNum;
}

void Receipt::setAccName(string specAccName)
{
	accName = specAccName;
}

void Receipt::setServiceCost(string serviceCost)
{
	this->serviceCost = serviceCost;
}
