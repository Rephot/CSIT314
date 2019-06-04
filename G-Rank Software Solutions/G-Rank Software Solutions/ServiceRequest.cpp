#include"ServiceRequest.h"
#include<fstream>

using namespace std;

ServiceRequest::ServiceRequest() {}

ServiceRequest::ServiceRequest(string nameSt, string codePost, string numSt, string descLoc, string typeService, string descInc)
{
	stName = nameSt;
	postCode = codePost;
	stNum = numSt;
	locDesc = descLoc;
	serviceType = typeService;
	incDesc = descInc;
}

string ServiceRequest::getStName()
{
	return stName;
}

string ServiceRequest::getPostCode()
{
	return postCode;
}

string ServiceRequest::getStNum()
{
	return stNum;
}

string ServiceRequest::getLocDesc()
{
	return locDesc;
}

string ServiceRequest::getServiceType()
{
	return serviceType;
}

string ServiceRequest::getIncDesc()
{
	return incDesc;
}