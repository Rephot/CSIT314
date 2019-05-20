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
#include <Wt/WMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPopupMenuItem.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>

#include <fstream>

using namespace std;

class GRankSoftwareSolutions : public Wt::WApplication {
private:
	std::string appName;
	Wt::WApplication* app;
	Wt::WContainerWidget* _content;
	Wt::WVBoxLayout* _contentLayout;
	Wt::WContainerWidget* _header;
	Wt::WText* _headerText;
	Wt::WContainerWidget* _pageContent;
	Wt::WVBoxLayout* _pageLayout;
	void handlePathChange(); // J: will be trying to add URL path management, STRETCH goal
	bool validateUser();

public:
	GRankSoftwareSolutions(const Wt::WEnvironment &env);
	void initCSS();
	void initContentLayout();
	void loginPage();
	void servicePage();
	void registerPage();
	void registerPage2();
	void registerPage3();
	void customerDashboard();
	void title();
};

#endif