#ifndef G_SOFTWARESOLUTIONS_H
#define G_SOFTWARESOLUTIONS_H

#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WContainerwidget.h>
#include <Wt/WEvent.h>
#include <Wt/WLength.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLink.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <fstream>
#include <vector>

#include "Customer.h"
#include "Specialist.h"

using namespace std;

class GRankSoftwareSolutions : public Wt::WApplication {
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
	void handlePathChange(); // J: will be trying to add URL path management, STRETCH goal
	bool validateLogin(Wt::WString); // passed entered username to check if user exists
	// ↑this is used to confirm, ↓this is then used to validate
	bool validateUsersPassword(Wt::WString, Wt::WString); // passed enterd username and password to check if the password is correct for that user
	vector<Customer> existingCustomers;
	vector<Specialist> existingSpecialists;
	int userFlag;

public:
	GRankSoftwareSolutions(const Wt::WEnvironment &env);
	void initCSS();
	void initContentLayout();
	void loginPage();
	void servicePage();
	void registerPage();
	void registerPage2();
	void registerPage3();
	void customerMenu();
	void title();
	void contentTitle();
	void loadUsers();
};

#endif