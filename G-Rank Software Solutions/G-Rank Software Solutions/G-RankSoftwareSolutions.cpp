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

GRankSoftwareSolutions::GRankSoftwareSolutions(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
	app = Wt::WApplication::instance();
	initCSS();

	appName = "UberServices by GRankSoftwareSolutions";
	setTitle(appName);

	initContentLayout();
	title();
	loginPage();
}

void GRankSoftwareSolutions::handlePathChange()
{
	if (Wt::WApplication::instance()->internalPath() == "register")
	{
		registerPage();
	}
}

void GRankSoftwareSolutions::initCSS()
{
	app->styleSheet().addRule("#content", "display: block; margin: auto;");
	app->styleSheet().addRule("#dashboard", "width: 100%; margin-left: 0%;");
	app->styleSheet().addRule("#navbar", "background-color: #262626; color: #fff;");
	//app->styleSheet().addRule("#pageContent", "display: block; margin-left: auto; margin-right: auto;");
	app->styleSheet().addRule("body", "background-color: #abcdef;");
	app->styleSheet().addRule("#buttons", "background-color: #9abcde;");
	app->styleSheet().addRule("#header", "background-color: #262626; color: #fff; padding: 0.1em 0.5em;");
	app->styleSheet().addRule("#signUpButton", "background-color: #01d; color: #eee;"); // currently not working
	/*app->styleSheet().addRule("#sidebar", "display: inline-block; padding: 0.5em; color: #f00");
	app->styleSheet().addRule("#footer", "background-color: #262626; color: #fff; padding: 0.5em;");*/
}

void GRankSoftwareSolutions::initContentLayout()
{
	_content = root()->addWidget(make_unique<Wt::WContainerWidget>());
	_content->setId("content");
	_content->setMaximumSize(400, 1600);

	//create vertical layout
	_contentLayout = _content->setLayout(make_unique<Wt::WVBoxLayout>());
}

void GRankSoftwareSolutions::title()
{
	//create header title
	_header = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_header->setId("header");
	_headerLayout = _header->setLayout(make_unique<Wt::WVBoxLayout>());
	_headerText = _headerLayout->addWidget(make_unique<Wt::WText>("<h3>" + appName + "</h3>"), 0, Wt::AlignmentFlag::Center);
	_pageContent = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>(), 0, Wt::AlignmentFlag::Center);
}

void GRankSoftwareSolutions::contentTitle()
{
	//create header title
	_header = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_header->setId("header");
	_headerLayout = _header->setLayout(make_unique<Wt::WVBoxLayout>());
	_headerText = _headerLayout->addWidget(make_unique<Wt::WText>("<h3>" + appName + "</h3>"), 0, Wt::AlignmentFlag::Left);
	_pageContent = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>(), 0, Wt::AlignmentFlag::Left);
}

void GRankSoftwareSolutions::customerMenu()
{
	_pageContent->clear();
	Wt::WVBoxLayout *_menuLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());

	// links to for now 3 options that the customer can do
	// connect to create service request page
	Wt::WPushButton *_createRequestButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Create Servcie"));

	// connect to view manage details page
	Wt::WPushButton *_viewDetailsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("View/Manage User Details"));

	// connects to view reciepts
	Wt::WPushButton *_viewReceiptsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("View Reciepts"));

	// connect to view make review, only allow user to make a review of most recent service that happened in the last ?3 days?
	Wt::WPushButton *_viewMakeReviewButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("View/Make Reviews"));
}

void GRankSoftwareSolutions::loginPage()
{
	GRankSoftwareSolutions::loadUsers();
	_pageContent->clear();
	//create username text and input
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");
	_pageContent->setWidth(400);
	Wt::WText *_usernameText = _pageLayout->addWidget(make_unique<Wt::WText>("Username:"));
	Wt::WLineEdit *_usernameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_usernameField->setPlaceholderText("user1234");

	//create password text and input
	Wt::WText *_passwordText = _pageLayout->addWidget(make_unique<Wt::WText>("Password:"));
	Wt::WLineEdit *_passwordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_passwordField->setPlaceholderText("Password");
	_passwordField->setEchoMode(Wt::EchoMode::Password);

	//create pushButtons for sign in and sign up
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());
	Wt::WPushButton *_signUpButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign Up"));
	//_signUpButton->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/register"));
	//Wt::WApplication::instance()->internalPathChanged().connect([=] {
	//	//handlePathChange();
	//});
	_signUpButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRankSoftwareSolutions::registerPage();
	});
	
	Wt::WPushButton *_signInButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign In"));
	//_signInButton->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/service"));
	_signInButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		if (GRankSoftwareSolutions::validateLogin(_usernameField->text()))
		{
			if (GRankSoftwareSolutions::validateUsersPassword(_usernameField->text(), _passwordField->text())) GRankSoftwareSolutions::customerMenu();
		}
		else
		{

		}
		/*(GRankSoftwareSolutions::validate()) ? { }:{ };*/
	});
}

void GRankSoftwareSolutions::registerPage()
{ // J: does not currently create user, will link into program tomorrow wednesday 15th probably
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");

	// J: will add specialist/customer choice here, which will add/remove fields that are unique to each option

	// basic account login info
	Wt::WText* _usernameText = _pageLayout->addWidget(make_unique<Wt::WText>("Enter a Username"));
	Wt::WLineEdit* _usernameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_usernameField->setPlaceholderText("user123");
	Wt::WText* _passwordText = _pageLayout->addWidget(make_unique<Wt::WText>("Enter Password"));
	Wt::WLineEdit* _passwordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_passwordField->setPlaceholderText("Password");
	_passwordField->setEchoMode(Wt::EchoMode::Password);
	Wt::WText* _confirmPasswordText = _pageLayout->addWidget(make_unique<Wt::WText>("Confirm Password"));
	Wt::WLineEdit* _confirmPasswordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_confirmPasswordField->setPlaceholderText("Confirm Password");
	_confirmPasswordField->setEchoMode(Wt::EchoMode::Password);

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());

	// cancel to go back to login screen
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));
	_cancelButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRankSoftwareSolutions::loginPage();
	});

	// confirm will create user profile and log them in (this assumes they've confirmed their account via email...)
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Next"));
	_confirmButton->setStyleClass("btn-primary");
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRankSoftwareSolutions::registerPage2();
	});
	// will check if userName is available
	// will check if passwords match
	// STRETCH: will check if email is of correct format
	// 3rd page registration: home address, car details, bankCard details
	// the aim with multi-page registrations is to restrict the amount of information entered on each page for UX
}

void GRankSoftwareSolutions::registerPage2()
{
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");

	// 2nd page registration?
	// personal details, names, license number and contact details(phone number and email, phone as way of communicating with specialists, and email for other service related commicae)
	Wt::WText* _firstNameText = _pageLayout->addWidget(make_unique<Wt::WText>("First Name"));
	Wt::WLineEdit* _firstNameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_firstNameField->setPlaceholderText("Jordan");
	Wt::WText* _lastNameText = _pageLayout->addWidget(make_unique<Wt::WText>("Last Name"));
	Wt::WLineEdit* _lastNameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_lastNameField->setPlaceholderText("Smith");
	Wt::WText *_licenseText = _pageLayout->addWidget(make_unique<Wt::WText>("License Number"));
	Wt::WLineEdit* _licenseField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_licenseField->setPlaceholderText("23456789");
	Wt::WText *_contactPhoneText = _pageLayout->addWidget(make_unique<Wt::WText>("Contact Phone Number"));
	Wt::WLineEdit* _contactPhoneField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_contactPhoneField->setPlaceholderText("0412345678");

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());

	// cancel to go back to login screen
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_cancelButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRankSoftwareSolutions::registerPage();
	});

	// confirm will create user profile and log them in (this assumes they've confirmed their account via email...)
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Next"));
	_confirmButton->setStyleClass("btn-primary");
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRankSoftwareSolutions::registerPage3();
	});
}

void GRankSoftwareSolutions::registerPage3()
{
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");

	// 3rd page registration: home address, car details, bankCard details
	Wt::WText* _homeAddressText = _pageLayout->addWidget(make_unique<Wt::WText>("Home Address"));
	Wt::WLineEdit* _homeAddressField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_homeAddressField->setPlaceholderText("221b Baker Street");
	Wt::WText* _carMakeText = _pageLayout->addWidget(make_unique<Wt::WText>("Car Make"));
	Wt::WLineEdit* _carMakeField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_carMakeField->setPlaceholderText("Toyboata");
	Wt::WText *_carModelText = _pageLayout->addWidget(make_unique<Wt::WText>("Car Model"));
	Wt::WLineEdit* _carModelField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_carModelField->setPlaceholderText("Hidux");
	Wt::WText *_carColourText = _pageLayout->addWidget(make_unique<Wt::WText>("Car Colour"));
	Wt::WLineEdit* _carColourField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_carColourField->setPlaceholderText("White");

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());

	// cancel to go back to login screen
	Wt::WPushButton *_retraceButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_retraceButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRankSoftwareSolutions::registerPage2();
	});

	// confirm will create user profile and log them in (this assumes they've confirmed their account via email...)
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRankSoftwareSolutions::customerMenu();
	});
}

void GRankSoftwareSolutions::servicePage()
{
	// map?STRETCH, combobox, description (textEdit), confirm and cancel
}

void GRankSoftwareSolutions::loadUsers()
{
	string line, username, password, fName, lName, phNumber, custID, DOB;
	string userFile = "Customers.csv";

	// get existing users from file
	ifstream inFile;
	inFile.open(userFile);
	if (inFile.is_open())
	{
		while (getline(inFile, custID, ','))
		{
			getline(inFile, username, ',');
			getline(inFile, password, ',');
			getline(inFile, fName, ',');
			getline(inFile, lName, ',');
			getline(inFile, DOB, ',');
			getline(inFile, phNumber);

			existingCustomers.push_back(Customer(stoi(custID), username, password, fName, lName, stoi(DOB), phNumber));
		}
		inFile.close();
	}
	string operationalArea, specialistID;
	userFile = "Specialists.csv";

	// get existing users from file
	inFile.open(userFile);
	if (inFile.is_open())
	{
		while (getline(inFile, username, ','))
		{
			getline(inFile, password, ',');
			getline(inFile, fName, ',');
			getline(inFile, lName, ',');
			getline(inFile, phNumber, ',');
			getline(inFile, operationalArea, ',');
			getline(inFile, specialistID);

			existingSpecialists.push_back(Specialist(username, password, fName, lName, 0, phNumber, operationalArea, stoi(specialistID)));
		}
		inFile.close();
	}
}

bool GRankSoftwareSolutions::validateLogin(Wt::WString username)
{
	vector<Customer>::iterator cItr = existingCustomers.begin();
	vector<Specialist>::iterator sItr = existingSpecialists.begin();
	while ( ( cItr != existingCustomers.end() ) && ( sItr != existingSpecialists.end() ) )
	{
		Wt::WString user = cItr->getUserName();
		if (user == username)
		{
			userFlag = 1;
			return true;
		} else if(cItr != existingCustomers.end()) cItr++;
		user = sItr->getUserName();
		if (user == username)
		{
			userFlag = 2;
			return true;
		} else if(sItr != existingSpecialists.end()) sItr++;
	}
	return false;
}

bool GRankSoftwareSolutions::validateUsersPassword(Wt::WString username, Wt::WString password)
{
	if(userFlag != 0)
	{
		if (userFlag == 1)
		{
			for (vector<Customer>::iterator Itr = existingCustomers.begin(); Itr != existingCustomers.end(); Itr++) {
				Wt::WString user = Itr->getUserName();
				Wt::WString pass = Itr->getPassword();
				if((user == username) && (pass == password)) return true;
			}
		}
		else
		{
			for (vector<Specialist>::iterator Itr = existingSpecialists.begin(); Itr != existingSpecialists.end(); Itr++)
			{
				Wt::WString user = Itr->getUserName();
				Wt::WString pass = Itr->getPassword();
				if ((user == username) && (pass == password)) return true;
			}
		}
	}// else vector<Admin>::iterator Itr = existingAdmins.begin();
	return false;
}