#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WContainerwidget>
#include <Wt/WLength>
#include <Wt/WLineEdit>
#include <Wt/WLink>
#include <Wt/WEvent.h>
#include <Wt/WPushButton>
#include <Wt/WText>

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
	void title();
};