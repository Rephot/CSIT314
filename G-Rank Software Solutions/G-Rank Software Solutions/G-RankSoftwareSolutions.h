#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WContainerwidget>
#include <Wt/WLength>
#include <Wt/WLineEdit>
#include <Wt/WLink>
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
	Wt::WText* _username;
	Wt::WLineEdit* _usernameInput;
	Wt::WText* _password;
	Wt::WLineEdit* _passwordInput;
	Wt::WContainerWidget* _buttons;
	Wt::WHBoxLayout* _buttonsLayout;
	Wt::WPushButton* _signUp;
	Wt::WPushButton* _signIn;
	Wt::WContainerWidget* _pageContent;
	Wt::WVBoxLayout* _pageLayout;

public:
	GRankSoftwareSolutions(const Wt::WEnvironment &env);
	void initCSS();
	void initContentLayout();
	void loginPage();
	void servicePage();
	void title();
};