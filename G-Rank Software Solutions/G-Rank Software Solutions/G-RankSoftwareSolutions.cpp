/*
nav page placeholder
serviceRequest creation
	links to ???
	map
	type
	description
*/

#include"G-RankSoftwareSolutions.h"

//namespace {
//
//	void handlePathChange()
//	{
//		Wt::WApplication *app = Wt::WApplication::instance();
//
//		if (app->internalPath() == "/login")
//			loginPage();
//		else if (app->internalPath() == "/service")
//			servicePage();
//		else
//			howDidYouGetHere();
//	}
//
//}

GRankSoftwareSolutions::GRankSoftwareSolutions(const Wt::WEnvironment &env) : Wt::WApplication(env) {
	app = Wt::WApplication::instance();
	initCSS();

	appName = "UberServices by GRankSoftwareSolutions";
	setTitle(appName);

	initContentLayout();
	title();
	loginPage();
}

void GRankSoftwareSolutions::initCSS() {
	app->styleSheet().addRule("#content", "display: block; margin-left: auto; margin-right: auto; margin-top: 15%;");
	app->styleSheet().addRule("#pageContent", "display: block; margin-left: auto; margin-right: auto;");
	app->styleSheet().addRule("body", "background-color: #abcdef;");
	app->styleSheet().addRule("#buttons", "background-color: #fedcba;");
	app->styleSheet().addRule("#header", "background-color: #262626; color: #fff; padding: 0.1em 0.5em;");
	app->styleSheet().addRule("#signUpButton", "background-color: #01d; color: #eee;"); // currently not working
	/*app->styleSheet().addRule("#sidebar", "display: inline-block; padding: 0.5em; color: #f00");
	app->styleSheet().addRule("#footer", "background-color: #262626; color: #fff; padding: 0.5em;");*/
}

void GRankSoftwareSolutions::initContentLayout() {
	_content = root()->addWidget(make_unique<Wt::WContainerWidget>());
	_content->setId("content");
	_content->setWidth(400);

	//create vertical layout
	_contentLayout = _content->setLayout(make_unique<Wt::WVBoxLayout>());
}

void GRankSoftwareSolutions::title() {
	//create header title
	_header = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_header->setId("header");
	_headerLayout = _header->setLayout(make_unique<Wt::WVBoxLayout>());
	_headerText = _headerLayout->addWidget(make_unique<Wt::WText>("<h3>" + appName + "</h3>"), 0, Wt::AlignmentFlag::Center);
}

void GRankSoftwareSolutions::loginPage() {
	//create username text and input
	_pageContent = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>(), 0, Wt::AlignmentFlag::Center);
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");
	_pageContent->setWidth(400);
	_username = _pageLayout->addWidget(make_unique<Wt::WText>("Username:"));
	_usernameInput = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());

	//create password text and input
	_password = _pageLayout->addWidget(make_unique<Wt::WText>("Password:"));
	_passwordInput = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());

	//create pushButtons for sign in and sign up
	_buttons = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttons->setId("buttons");
	_buttonsLayout = _buttons->setLayout(make_unique<Wt::WHBoxLayout>());
	_signUp = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign Up"));
	_signUp->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/register"));
	
	_signIn = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign In"));
	_signIn->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/service"));
}

void GRankSoftwareSolutions::servicePage() {
	// map, combobox, description (textEdit), confirm and cancel
}