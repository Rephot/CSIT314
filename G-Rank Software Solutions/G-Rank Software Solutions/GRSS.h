#ifndef G_SOFTWARESOLUTIONS_H
#define G_SOFTWARESOLUTIONS_H

#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WComboBox.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WContainerwidget.h>
#include <Wt/WEvent.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLength.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLink.h>
#include <Wt/WPushButton.h>
#include <Wt/WRadioButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WVBoxLayout.h>

#include <fstream>
#include <vector>
#include <regex>

#include "Specialist.h"
#include "Customer.h"

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
	vector<Customer> existingCustomers = {};
	vector<Specialist> existingSpecialists = {};
	int userFlag;
	// may replace with logged_in_user???
	Customer logged_in_customer;
	Specialist logged_in_specialist;
	void initCSS();
	void initContentLayout();
	void title();
	void loadUsers();
	void loginPage();
	void registerPage();
	void registerPage2();
	void registerPage3();
	bool userAvailable(Wt::WString);

	void userMenu();
	void viewRequests();
	void createRequestPage();
	void viewUserDetails();

public:
	GRSS(const Wt::WEnvironment &env);
};

#endif