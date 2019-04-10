#include"ServiceRequest.h"
// inherits user

class Specialist {
public:
	Specialist();
	void addToCurrentRequests();
	static ServiceRequest currentRequests[];
private:
};
