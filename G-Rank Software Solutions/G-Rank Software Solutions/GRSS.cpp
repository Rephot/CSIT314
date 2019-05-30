#include"GRSS.h"

regex emailPattern("(\\w+)@(\\w+)(\\.(\\w+))+");

int userRegisterType;

// registerpage tmp
Wt::WString userTmp;
Wt::WString pwTmp;
// registerpage2 tmp
Wt::WString fnameTmp;
Wt::WString lnameTmp;
Wt::WString licNumTmp;
Wt::WString phoneTmp;
Wt::WString emailTmp;
// registerpage3 tmp
// cust
Wt::WString homeAddressTmp;
Wt::WString customerTmp;
Wt::WString licPlateTmp;
Wt::WString modelYearTmp;
Wt::WString makeTmp;
Wt::WString modelTmp;
Wt::WString shapeTmp;
Wt::WString engineSizeTmp;
Wt::WString colourTmp;
// spec
Wt::WString opAreaTmp;
Wt::WString qualNumTmp;

GRSS::GRSS(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
	app = Wt::WApplication::instance();
	initCSS();

	appName = "UberServices by GRankSoftwareSolutions";
	setTitle(appName);

	initContentLayout();
	title();
	loginPage();
}

void GRSS::initCSS()
{
	app->styleSheet().addRule("#content", "display: block; margin: auto;");
	app->styleSheet().addRule("#dashboard", "width: 100%; margin-left: 0%;");
	app->styleSheet().addRule("body", "background-color: #abcdef;");
	app->styleSheet().addRule("#buttons", "background-color: #9abcde;");
	app->styleSheet().addRule("#header", "background-color: #262626; color: #fff; padding: 0.1em 0.5em;");
}

void GRSS::initContentLayout()
{
	_content = root()->addWidget(make_unique<Wt::WContainerWidget>());
	_content->setId("content");
	_content->setMaximumSize(400, 1600);

	//create vertical layout
	_contentLayout = _content->setLayout(make_unique<Wt::WVBoxLayout>());
}

void GRSS::title()
{
	//create header title
	_header = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_header->setId("header");
	_headerLayout = _header->setLayout(make_unique<Wt::WVBoxLayout>());
	_headerText = _headerLayout->addWidget(make_unique<Wt::WText>("<h3>" + appName + "</h3>"), 0, Wt::AlignmentFlag::Center);
	_pageContent = _contentLayout->addWidget(make_unique<Wt::WContainerWidget>(), 0, Wt::AlignmentFlag::Center);
}

void GRSS::loadUsers()
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


			existingSpecialists.push_back(Specialist(username, password, fName, lName, phNumber, operationalArea, stoi(specialistID)));
		}
		inFile.close();
	}
}

void GRSS::loginPage()
{
	GRSS::loadUsers();
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
	_passwordField->enterPressed().connect([=]
	{
		if (GRSS::validateLogin(_usernameField->text()))
		{
			if (GRSS::validateUsersPassword(_usernameField->text(), _passwordField->text()))
			{
				GRSS::userMenu();
			}
			// else // emit error incorrect password
		}
		else
		{
			// emit error invalid user
		}
	});

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
		GRSS::registerPage();
	});

	Wt::WPushButton *_signInButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign In"));
	//_signInButton->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/service"));
	_signInButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		if (GRSS::validateLogin(_usernameField->text()))
		{
			if (GRSS::validateUsersPassword(_usernameField->text(), _passwordField->text()))
			{
				GRSS::userMenu();
			}
			// else // emit error incorrect password
		}
		else
		{
			// emit error invalid user
		}
	});
}

bool GRSS::validateLogin(Wt::WString username)
{
	vector<Customer>::iterator cItr = existingCustomers.begin();
	vector<Specialist>::iterator sItr = existingSpecialists.begin();
	while ((cItr != existingCustomers.end()) && (sItr != existingSpecialists.end()))
	{
		Wt::WString user = cItr->getUserName();
		if (user == username)
		{
			userFlag = 1;
			return true;
		}
		else if (cItr != existingCustomers.end()) cItr++;
		user = sItr->getUserName();
		if (user == username)
		{
			userFlag = 2;
			return true;
		}
		else if (sItr != existingSpecialists.end()) sItr++;
	}
	return false;
}

bool GRSS::validateUsersPassword(Wt::WString username, Wt::WString password)
{
	if (userFlag != 0)
	{
		if (userFlag == 1)
		{
			for (vector<Customer>::iterator Itr = existingCustomers.begin(); Itr != existingCustomers.end(); Itr++)
			{
				Wt::WString user = Itr->getUserName();
				Wt::WString pass = Itr->getPassword();
				if ((user == username) && (pass == password))
				{
					logged_in_customer = *Itr;
					return true;
				}
			}
		}
		else if (userFlag == 2)
		{
			for (vector<Specialist>::iterator Itr = existingSpecialists.begin(); Itr != existingSpecialists.end(); Itr++)
			{
				Wt::WString user = Itr->getUserName();
				Wt::WString pass = Itr->getPassword();
				if ((user == username) && (pass == password))
				{
					logged_in_specialist = *Itr;
					return true;
				}
			}
		}
	}// else vector<Admin>::iterator Itr = existingAdmins.begin();
	return false;
}

void GRSS::registerPage()
{
	/*
	// USER
   username, password;
	*/
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");

	// basic account login info
	Wt::WText *_usernameText = _pageLayout->addWidget(make_unique<Wt::WText>("Enter a Username"));;
	Wt::WLineEdit* _usernameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_usernameField->setPlaceholderText("usr123");
	_usernameField->changed().connect([=] {
		// check username availability
		/*(!(GRSS::userAvailable(_usernameField->text()))) ? _usernameText->setText("Enter a Username<font color=\"red\"> This User Name is unavailable</font>") : _usernameText->setText("Enter a Username");*/
	});

	// password creation and matching
	Wt::WText* _passwordText = _pageLayout->addWidget(make_unique<Wt::WText>("Enter Password"));
	Wt::WLineEdit* _passwordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_passwordField->setPlaceholderText("Password");
	_passwordField->setEchoMode(Wt::EchoMode::Password);
	Wt::WText* _confirmPasswordText = _pageLayout->addWidget(make_unique<Wt::WText>("Confirm Password"));
	Wt::WLineEdit* _confirmPasswordField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_confirmPasswordField->setPlaceholderText("Confirm Password");
	_confirmPasswordField->setEchoMode(Wt::EchoMode::Password);
	_confirmPasswordField->changed().connect([=] {
		/*(_passwordField->text() == _confirmPasswordField->text()) ? _confirmPasswordText->setText("Confirm Password") : _confirmPasswordText->setText("Confirm Password <font color=\"red\">Passwords Do NOT match</font>");*/
	});
	_passwordField->changed().connect([=] {
		/*if (_confirmPasswordField->text() != "") (_passwordField->text() == _confirmPasswordField->text()) ? _confirmPasswordText->setText("Confirm Password") : _confirmPasswordText->setText("Confirm Password <font color=\"red\">Passwords Do NOT match</font>");*/
	});

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());

	// cancel to go back to login screen, resets internal tmps to ""
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));
	_cancelButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		/*userTmp = "";
		pwTmp = "";*/
		GRSS::loginPage();
	});

	// sets tmp values for username and password, if all valid
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Next"));
	_confirmButton->setStyleClass("btn-primary");

	// missing details
	Wt::WText *_missingText = _pageLayout->addWidget(make_unique<Wt::WText>("<font color = \"red\">All fields are required</font>"));
	_missingText->setHidden(true);

	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		// if username available and passwords match, set temp values, and proceed to registerpage2
		/*if ((GRSS::userAvailable(_usernameField->text()) && (_passwordField->text() == _confirmPasswordField->text())) && (_usernameField->text() != "" && _passwordField->text() != ""  &&_confirmPasswordField->text() != "")) {
			_missingText->setHidden(true);
			userTmp = _usernameField->text();
			pwTmp = _passwordField->text();
			GRSS::registerPage2();
		}
		else _missingText->setHidden(false);*/
		GRSS::registerPage2();
	});
	// the aim with multi-page registrations is to restrict the amount of information entered on each page for UX
}

void GRSS::registerPage2()
{
	/*
	// CUSTOMER details
	string fName, lName, phNumber, licenseNumber, email;
	*/
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");

	// first and last name
	Wt::WText* _firstNameText = _pageLayout->addWidget(make_unique<Wt::WText>("First Name"));
	Wt::WLineEdit* _firstNameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_firstNameField->setPlaceholderText("Jordan");
	Wt::WText* _lastNameText = _pageLayout->addWidget(make_unique<Wt::WText>("Last Name"));
	Wt::WLineEdit* _lastNameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_lastNameField->setPlaceholderText("Smith");

	// license number can be used as age validation (at least in australia), not necessarily unique, because of stipulation by hoa of one car to one client
	Wt::WText *_licenseText = _pageLayout->addWidget(make_unique<Wt::WText>("License Number"));
	Wt::WLineEdit* _licenseField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_licenseField->setPlaceholderText("23456789");

	// phone
	Wt::WText *_contactPhoneText = _pageLayout->addWidget(make_unique<Wt::WText>("Contact Phone Number"));
	Wt::WLineEdit* _contactPhoneField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_contactPhoneField->setPlaceholderText("0412345678");
	// email
	Wt::WText *_emailText = _pageLayout->addWidget(make_unique<Wt::WText>("Email Address"));
	Wt::WLineEdit* _emailField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_emailField->setPlaceholderText("example@email.com");
	_emailField->changed().connect([=] {
		/*string email = _emailField->text().narrow();
		(regex_match(email, emailPattern)) ? _emailText->setText("Email Address") : _emailText->setText("Email Address <font color = \"red\">Not recognised as a valid email address</font>");*/
	});

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());

	// missing details
	Wt::WText *_missingText = _pageLayout->addWidget(make_unique<Wt::WText>("<font color = \"red\">All fields are required</font>"));
	_missingText->setHidden(true);

	// cancel to go back to login screen
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_cancelButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		/*
		fnameTmp = "";
		lnameTmp = "";
		licNumTmp = "";
		phoneTmp = "";
		emailTmp = "";
		*/
		GRSS::registerPage();
	});

	// confirm will add values to temp values and proceed to registerpage3
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Next"));
	_confirmButton->setStyleClass("btn-primary");
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		/*fnameTmp = _firstNameField->text();
		lnameTmp = _lastNameField->text();
		licNumTmp = _licenseField->text();
		phoneTmp = _contactPhoneField->text();
		emailTmp = _emailField->text().narrow();
		((regex_match(emailTmp, emailPattern)) && (fnameTmp != "") && (lnameTmp != "") && (licNumTmp != "") && (phoneTmp != "") && (emailTmp != "")) ? GRSS::registerPage3() : _missingText->setHidden(false);*/
		GRSS::registerPage3();
	});
}

void GRSS::registerPage3()
{
	/*
	// customers car
	int cust_id, modelYear;
	string make, model, licencePlate, colour, shape;
	double engineSize;

	// specialists
	string to int operationalArea
	*/
	// 3rd page registration: home address, car details, bankCard details
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	_pageContent->setId("pageContent");

	// radio boxes for choice between specialist and client, all information previously is common
	Wt::WContainerWidget *_buttonContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	Wt::WHBoxLayout *_buttonLayout = _buttonContainer->setLayout(make_unique<Wt::WHBoxLayout>());
	auto _buttonGroup = make_shared<Wt::WButtonGroup>();
	Wt::WRadioButton *_specRadio = _buttonLayout->addWidget(make_unique<Wt::WRadioButton>("Specialist"));
	_buttonGroup->addButton(_specRadio, 1);
	Wt::WRadioButton *_custRadio = _buttonLayout->addWidget(make_unique<Wt::WRadioButton>("Customer"));
	_buttonGroup->addButton(_custRadio, 2);
	// changes the content of a stacked widget

	// 3rd page form customer
	Wt::WContainerWidget *_thirdPageForm = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());

	// change content based on which radio selected
	auto rawButtonGroup = _buttonGroup.get();
	_buttonGroup->checkedChanged().connect([=](Wt::WRadioButton *selection)
	{
		// usertype flag for user creation
		if (rawButtonGroup->id(selection) == 1) {
			// 3rd page form specialist

			_thirdPageForm->clear();
			userFlag = 2;
			Wt::WVBoxLayout *_thirdPageLayout = _thirdPageForm->setLayout(make_unique<Wt::WVBoxLayout>());
			Wt::WText *_qualNumberText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("License/Qualification Number"));
			Wt::WLineEdit *_qualNumberField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_qualNumberField->setPlaceholderText("MVTC165396");

			// may move to registerPage4 for payment details
			Wt::WText *_BSBText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("BSB"));
			Wt::WLineEdit *_BSBField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_BSBField->setPlaceholderText("9801-1080");
		}
		else if (rawButtonGroup->id(selection) == 2) {
			// 3rd page registration(Customer): home address, car details, bankCard details
			/*
			Wt::WString hmTmp;
			// car details, only needed for customer
			Wt::WString cstTmp; // generated custId when register complete
			Wt::WString lcnsPltTmp;
			Wt::WString mdlYrTmp;
			Wt::WString mkTmp;
			Wt::WString mdlTmp;
			Wt::WString shpTmp;
			Wt::WString ngnSzTmp;
			Wt::WString clrTmp;
			*/
			_thirdPageForm->clear();
			userFlag = 1;
			Wt::WVBoxLayout *_thirdPageLayout = _thirdPageForm->setLayout(make_unique<Wt::WVBoxLayout>());

			Wt::WText* _homeAddressText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Home Address"));
			Wt::WLineEdit* _homeAddressField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_homeAddressField->setPlaceholderText("221b Baker Street");

			Wt::WText* _lcncPltText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Licence Plate"));
			Wt::WLineEdit* _lcncPltField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_lcncPltField->setPlaceholderText("BJB-007");

			Wt::WText* _modelYearText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Year Made"));
			Wt::WLineEdit* _modelYearField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_modelYearField->setPlaceholderText("2007");

			Wt::WText* _carMakeText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Make"));
			Wt::WLineEdit* _carMakeField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_carMakeField->setPlaceholderText("Toyboata");

			Wt::WText *_carModelText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Model"));
			Wt::WLineEdit* _carModelField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_carModelField->setPlaceholderText("Hilux");

			Wt::WText *_shapeText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Shape"));
			// replace with combo box
			Wt::WLineEdit* _shapeField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_shapeField->setPlaceholderText("Ute");

			Wt::WText *_engineSizeText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Colour"));
			Wt::WLineEdit* _engineSizeField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_engineSizeField->setPlaceholderText("3.4L");

			Wt::WText *_carColourText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Colour"));
			Wt::WLineEdit* _carColourField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_carColourField->setPlaceholderText("Blue");
		}
	});

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());
	// cancel to go back to login screen
	Wt::WPushButton *_retraceButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_retraceButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRSS::registerPage2();
	});
	// confirm will create user profile and log them in (this assumes they've confirmed their account via email...)
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		// this should point to loginPage() such that the user can log in with the newly created user
		GRSS::loginPage();
	});
}

// register page 4 payment details

bool GRSS::userAvailable(Wt::WString username) {
	Wt::WString user;
	vector<Customer>::iterator cItr = existingCustomers.begin();
	while (cItr != existingCustomers.end())
	{
		user = cItr->getUserName();
		if (user == username) return false;
		else if (cItr != existingCustomers.end()) cItr++;
	}
	vector<Specialist>::iterator sItr = existingSpecialists.begin();
	while (sItr != existingSpecialists.end())
	{
		user = sItr->getUserName();
		if (user == username) return false;
		else if (sItr != existingSpecialists.end()) sItr++;
	}
	return true;
}

void GRSS::userMenu()
{
	// want to put current request somewhere in this menu, probably after the buttons, ONLY IF they have a current request
	_pageContent->clear();
	Wt::WVBoxLayout *_menuLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());

	// links to for now 3 options that the customer can do
	// connect to create service request page
	if (userFlag == 1)
	{
		Wt::WPushButton *_requestButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Create Service Request"));
		// connect to service creation page
		_requestButton->clicked().connect([=]
		{
			// STRETCH: if has current request ? goes to request : goes to create request;
			GRSS::createRequestPage();
		});
	}
	else if (userFlag == 2)
	{
		// view current requests in area
		Wt::WPushButton *_currentRequestsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Current Requests"));
		// connect to view requests page
		_currentRequestsButton->clicked().connect([=](const Wt::WMouseEvent &e)
		{
			GRSS::viewRequests();
		});
	}

	// connect to view manage details page
	Wt::WPushButton *_viewDetailsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("User Details"));
	_viewDetailsButton->clicked().connect([=]
	{
		GRSS::viewUserDetails();
	});

	// connects to view reciepts
	Wt::WPushButton *_viewTransactionsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Reciepts"));
	_viewTransactionsButton->clicked().connect([=]
	{
		GRSS::viewTransactions();
	});

	// connect to view make review, only allow user to make a review of most recent service that happened in the last ?3 days?
	Wt::WPushButton *_viewMakeReviewButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Reviews"));
	_viewMakeReviewButton->clicked().connect([=]
	{
		GRSS::viewReviews();
	});

	// logout ??
}

void GRSS::createRequestPage()
{
	// STRETCH add map widget, and only if you can pass data to and get data from
	// really want this to either create new request or if they've created a request, shows them that request and the specialists that have responded
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	/*
	ServiceRequest newRequest;
	// identifying number
	client = user.getFullName();
	time_t timeCreated = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char timeCreatedTime[26];
	ctime_s(timeCreatedTime, 26, &timeCreated);
	string dateTimeRequested = timeCreatedTime;
	newRequest.clientName = client;
	newRequest.incidentLocation = location;
	newRequest.sType = sType;
	newRequest.serviceRequestedAt = dateTimeRequested;
	newRequest.requestID = ++numRequests;
	broadcastServiceRequest(newRequest);
	*/

	// location information
	_pageLayout->addWidget(make_unique<Wt::WText>("Location:"));
	Wt::WLineEdit *_streetField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_streetField->setPlaceholderText("Street Name");
	Wt::WLineEdit *_streetNumberField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_streetNumberField->setPlaceholderText("Street Number(optional)");
	Wt::WLineEdit *_postField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_postField->setPlaceholderText("PostCode");
	Wt::WTextArea *_locationDescriptionArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>());
	_locationDescriptionArea->setPlaceholderText("Add additional location descriptors");

	_pageLayout->addWidget(make_unique<Wt::WBreak>());

	// incident information
	_pageLayout->addWidget(make_unique<Wt::WText>("Incident:"));
	Wt::WComboBox *_serviceType = _pageLayout->addWidget(make_unique<Wt::WComboBox>());
	_serviceType->addItem("Please Select...");
	_serviceType->addItem("Flat Tyre");
	_serviceType->addItem("Break Down");
	_serviceType->addItem("Flat Battery");
	_serviceType->addItem("Car Won't Start");
	_serviceType->addItem("Other, please describe");
	Wt::WTextArea *_descriptionArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>());
	_descriptionArea->setPlaceholderText("Add a Description");

	Wt::WHBoxLayout *_buttonsLayout = _pageLayout->addLayout(make_unique<Wt::WHBoxLayout>());
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));
	// connect to customer menu
	_cancelButton->clicked().connect([=]
	{
		// enum serviceStatus {requested, respondedTo, accepted, inProgress, complete, cancelled, investigation}
		GRSS::userMenu();
	});

	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
	// present with dialog/page for information confirmation, then connect to saveRequest such that specialist can respond

}

void GRSS::viewRequests()
{
	// generates a list of current requests that match the current specialists operational area
	// only if the specialist hasn't been accepted for a job
	// if they've been selected for a job, shows that job, and button to mark the job as complete
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=] { GRSS::userMenu(); });
	//while there are requests matching area
	for (int i = 0; i < 8; i++) {
		Wt::WContainerWidget *_requestContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WHBoxLayout *_requestHLayout = _requestContainer->setLayout(make_unique<Wt::WHBoxLayout>());
		Wt::WContainerWidget *_requestInfoContainer = _requestHLayout->addWidget(make_unique<Wt::WContainerWidget>(), 1);
		Wt::WVBoxLayout *_requestInfoLayout = _requestInfoContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		_requestInfoLayout->addWidget(make_unique<Wt::WText>("Address Information: St No.(if non-zero), St Name, PostCode"));
		_requestInfoLayout->addWidget(make_unique<Wt::WText>("Incident Info: type"));
		Wt::WTextArea *_requestDescription = _requestInfoLayout->addWidget(make_unique<Wt::WTextArea>("Incident Description"));
		_requestDescription->setReadOnly(true);
		Wt::WPushButton *_acceptRequestButton = _requestHLayout->addWidget(make_unique<Wt::WPushButton>("Accept"), 0, Wt::AlignmentFlag::Middle);
		_acceptRequestButton->setHeight(75);
	}
}

void GRSS::viewUserDetails()
{
	// shows all user details, has button to edit, editable fields
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=]
	{
		GRSS::userMenu();
	});

	// userFlag
	// username
	Wt::WText *_usernameText = _pageLayout->addWidget(make_unique<Wt::WText>("Username"));
	// first name
	Wt::WText *_fnameText = _pageLayout->addWidget(make_unique<Wt::WText>("First Name")); 
	// last name
	Wt::WText *_lnameText = _pageLayout->addWidget(make_unique<Wt::WText>("Last Name")); 
	// licence number
	Wt::WText *_licenceNumberText = _pageLayout->addWidget(make_unique<Wt::WText>("Licence Number")); 
	// phone number
	Wt::WText *_phoneNumberText = _pageLayout->addWidget(make_unique<Wt::WText>("Phone Number")); 
	// email
	Wt::WText *_emailText = _pageLayout->addWidget(make_unique<Wt::WText>("eMail")); 
}

void GRSS::editUserDetails()
{
	// shows all user details, has button to edit, editable fields
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_cancelButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));
	_cancelButton->clicked().connect([=]
	{
		GRSS::viewUserDetails();
	});

	// userFlag
	// first name
	Wt::WText *_fnameText = _pageLayout->addWidget(make_unique<Wt::WText>("Current First Name" /* + current fname*/));
	Wt::WLineEdit *_newFnameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_newFnameField->setPlaceholderText("Enter your new first name");
	// last name
	Wt::WText *_lnameText = _pageLayout->addWidget(make_unique<Wt::WText>("Current Last Name" /* + current lname*/));
	Wt::WLineEdit *_newLnameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_newLnameField->setPlaceholderText("Enter your new last name");
	// licence number
	Wt::WText *_licenceNumberText = _pageLayout->addWidget(make_unique<Wt::WText>("Current Licence Number" /* + current licnum*/));
	Wt::WLineEdit *_newLicenceNumberField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_newLicenceNumberField->setPlaceholderText("Enter your new licence number");
	// phone number
	Wt::WText *_phoneNumberText = _pageLayout->addWidget(make_unique<Wt::WText>("Current Phone Number" /* + Current number*/));
	Wt::WLineEdit *_newPhoneNumberField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_newPhoneNumberField->setPlaceholderText("Enter your new phone number");
	// email
	Wt::WText *_emailText = _pageLayout->addWidget(make_unique<Wt::WText>("Current eMail" /* + Current email*/));
	Wt::WLineEdit *_newEmailField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
	_newEmailField->setPlaceholderText("Enter your new phone number");

	Wt::WPushButton *_confirmButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Confirmm"));
	_confirmButton->clicked().connect([=]
	{
		// update details that were changed and go back to view user details
	});
}

// view transactions
void GRSS::viewTransactions()
{
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=]
	{
		GRSS::userMenu();
	});

	// related to current user
	// service request info
	Wt::WText *_serReqInfText = _pageLayout->addWidget(make_unique<Wt::WText>("Service Request Info"));
	// reciept info
	Wt::WText *_recInfoText = _pageLayout->addWidget(make_unique<Wt::WText>("Reciept Info"));
	// review info
	Wt::WText *_reviewInfoText = _pageLayout->addWidget(make_unique<Wt::WText>("Review Info"));
}

// view / make reviews
// pulls review data out of transactions and displays to user
// customer provides specialist identifier, whilst specialist user can only see reviews related to them
void GRSS::viewReviews()
{
	// shows most recent request if less than 2-3 days old, allows review to be made
	// shows all reviews customer has made, allows user to select specialist to view all their reviews
	// by clicking on the specialist

	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=]
	{
		GRSS::userMenu();
	});

	for (int i = 0; i < 5; i++)
	{
		// if transaction custid matches current customer id print review details
		// put all info in  a container
		Wt::WText *_requestText = _pageLayout->addWidget(make_unique<Wt::WText>("Request ID"));
		Wt::WText *_specialistText = _pageLayout->addWidget(make_unique<Wt::WText>("Specialist who completed this request"));
		Wt::WText *_reviewText = _pageLayout->addWidget(make_unique<Wt::WText>("Review Details"));
		Wt::WText *_ratingText = _pageLayout->addWidget(make_unique<Wt::WText>("Rating out of 10"));
	}
}