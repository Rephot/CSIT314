#include"Receipts.h"

Receipt::Receipt() {}

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
