#include"ServiceRequest.h"
// inherits user

class Specialist {
public:
	Specialist();
	void addToCurrentRequests();
private:
	static ServiceRequest currentRequests[];
};
