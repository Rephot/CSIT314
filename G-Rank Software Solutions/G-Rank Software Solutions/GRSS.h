#ifndef G_SOFTWARESOLUTIONS_H
#define G_SOFTWARESOLUTIONS_H

#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WComboBox.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerwidget.h>
#include <Wt/WDoubleSpinBox.h>
#include <Wt/WEvent.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLength.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLink.h>
#include <Wt/WPushButton.h>
#include <Wt/WRadioButton.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WVBoxLayout.h>

#include <fstream>
#include <vector>
#include <regex>
#include <set>

#include "Specialist.h"
#include "Customer.h"
#include "Transaction.h"
#include "Administrator.h"

using namespace std;

class GRSS : public Wt::WApplication {
private:
	std::string appName;
	Wt::WApplication* app;
	Wt::WContainerWidget* _content;
	Wt::WVBoxLayout* _contentLayout;
	Wt::WContainerWidget* _header;
	Wt::WVBoxLayout* _headerLayout;
	Wt::WText* _headerText;
	Wt::WContainerWidget* _pageContent;
	Wt::WVBoxLayout* _pageLayout;
	bool validateLogin(Wt::WString); // passed entered username to check if user exists
	// ↑this is used to confirm, ↓this is then used to validate
	bool validateUsersPassword(Wt::WString, Wt::WString); // passed enterd username and password to check if the password is correct for that user
	int userFlag;
	// may replace with logged_in_user???
	Customer logged_in_customer;
	Specialist logged_in_specialist;
	void initCSS();
	void initContentLayout();
	void title();
	void loadInfo();
	void unLoadData(Transaction);
	void loginPage();
	void registerPage();
	void registerPage2();
	void registerPage3();
	void registerPage4();
	bool userAvailable(Wt::WString);

	void userMenu();
	void createRequestPage();
	void customerRequest();
	void requestInProgress();
	void viewRequests();
	void specialistRequest();
	void requestComplete();
	void viewUserDetails();
	void editUserDetails();
	void viewTransactions();

public:
	vector<Customer> existingCustomers;
	vector<Specialist> existingSpecialists;
	vector<Administrator> existingAdmins;
	vector<Transaction> previousTransactions;
	vector<Transaction> inProgress; // customer created requests
	vector<Transaction> specAvailable; // specialists responding
	vector<Transaction> specAccepted; // customer has accepted a specialist
	vector<Transaction> completed;
	GRSS(const Wt::WEnvironment &env);
};

#endif