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

void GRankSoftwareSolutions::handlePathChange() {
	if (Wt::WApplication::instance()->internalPath() == "/?_=/register") {
		registerPage();
	}
}

void GRankSoftwareSolutions::initCSS() {
	app->styleSheet().addRule("#content", "display: block; margin: auto;");
	//app->styleSheet().addRule("#pageContent", "display: block; margin-left: auto; margin-right: auto;");
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
	Wt::WText* _usernameText = _pageLayout->addWidget(make_unique<Wt::WText>("Username:"));
	Wt::WLineEdit* _usernameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());

	//create password text and input
	Wt::WText* _passwordText = _pageLayout->addWidget(make_unique<Wt::WText>("Password:"));
	Wt::WLineEdit* _passwordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());

	//create pushButtons for sign in and sign up
	Wt::WContainerWidget* _buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout* _buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());
	Wt::WPushButton* _signUpButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign Up"));
	/*_signUpButton->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/register"));
	Wt::WApplication::instance()->internalPathChanged().connect([=] {
		handlePathChange();
	});*/
	_signUpButton->clicked().connect([=](const Wt::WMouseEvent &e) {
		GRankSoftwareSolutions::registerPage();
	});
	
	Wt::WPushButton* _signInButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign In"));
	//_signInButton->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/service"));
	_signInButton->clicked().connect([=](const Wt::WMouseEvent &e) {
		//GRankSoftwareSolutions::validate();
	});
}

void GRankSoftwareSolutions::registerPage() { // J: does not currently create user, will link into program tomorrow wednesday 15th probably
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");

	// J: will add specialist/customer choice here, which will add/remove fields that are unique to each option

	// basic account login info
	Wt::WText* _usernameText = _pageLayout->addWidget(make_unique<Wt::WText>("Enter your Username"));
	Wt::WLineEdit* _usernameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_usernameField->setPlaceholderText("Username:");
	Wt::WText* _passwordText = _pageLayout->addWidget(make_unique<Wt::WText>("Enter Password"));
	Wt::WLineEdit* _passwordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_passwordField->setPlaceholderText("Password:");
	Wt::WText* _confirmPasswordText = _pageLayout->addWidget(make_unique<Wt::WText>("Confirm Password"));
	Wt::WLineEdit* _confirmPasswordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_confirmPasswordField->setPlaceholderText("Confirm Password:");

	Wt::WBreak *_registerBreak = _pageLayout->addWidget(make_unique<Wt::WBreak>());

	// personal details, names, license number and contact details(phone number and email, phone as way of communicating with specialists, and email for other service related commicae)
	Wt::WText* _firstNameText = _pageLayout->addWidget(make_unique<Wt::WText>("First Name"));
	Wt::WLineEdit* _firstNameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_firstNameField->setPlaceholderText("First Name:");
	Wt::WText* _lastNameText = _pageLayout->addWidget(make_unique<Wt::WText>("Last Name"));
	Wt::WLineEdit* _lastNameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_lastNameField->setPlaceholderText("Last Name:");
	Wt::WText *_licenseText = _pageLayout->addWidget(make_unique<Wt::WText>("License Number"));
	Wt::WLineEdit* _licenseField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_licenseField->setPlaceholderText("License Number:");
	Wt::WText *_contactPhoneText = _pageLayout->addWidget(make_unique<Wt::WText>("Contact Phone Number"));
	Wt::WLineEdit* _contactPhoneField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_contactPhoneField->setPlaceholderText("Phone Number:");

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());

	// cancel to go back to login screen
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));

	// confirm will create user profile and log them in (assuming they've confirmed their account via email...)
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
	_confirmButton->setStyleClass("btn-primary");
}

void GRankSoftwareSolutions::servicePage() {
	// map, combobox, description (textEdit), confirm and cancel
}

