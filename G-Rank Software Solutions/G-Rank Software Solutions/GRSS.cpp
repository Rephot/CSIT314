#include"GRSS.h"

regex emailPattern("(\\w+)@(\\w+)(\\.(\\w+))+");

// registerpage tmp
string userTmp;
string pwTmp;
// registerpage2 tmp
string fnameTmp;
string lnameTmp;
string licNumTmp;
string phoneTmp;
string emailTmp;
// registerpage3 tmp
// cust
string homeAddressTmp;
string customerTmp;
string licPlateTmp;
string modelYearTmp;
string makeTmp;
string modelTmp;
string shapeTmp;
string engineSizeTmp;
string colourTmp;
// spec
set<string> opAreaTmp;
int check[15] = {};
string postCodes[15] = { "2515", "2516", "2517", "2518", "2519", "2500", "2525", "2526", "2527", "2528", "2529", "2530", "2502", "2505", "2506" };
string qualNumTmp;
// registerPage4 tmp
// cust
string cardNumTmp;
string cardExpTmp;
string cardSecTmp;
string subFlagTmp;
// spec
string BSBTmp;
string accNumTmp;
string accNameTmp;

// create request tmp
// location
string stNameTmp;
string stNumTmp;
string postCodeTmp;
string locationDescTmp;
// incident
string incidentTypeTmp;
string incidentDescTmp;

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
	_content->setMaximumSize(400, 1000000);

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

void GRSS::loadInfo()
{
	existingCustomers.clear();
	existingCustomers = Customer::GRSSload();
	existingSpecialists.clear();
	existingSpecialists = Specialist::GRSSload();
	existingAdmins.clear();
	existingAdmins = Administrator::loadAdministrators();
	inProgress = Transaction::GRSSload("GRSScreated.csv"); // customer creates
	specAvailable = Transaction::GRSSload("GRSSspecAvailable.csv"); // specialists says they're available
	specAccepted = Transaction::GRSSload("GRSSspecialistAccepted.csv"); // customer chooses specialist
	completed = Transaction::GRSSload("GRSSjobCompleted.csv"); // specialist marks job as completed, customer will add review and rating and confirm payment
	previousTransactions = Transaction::GRSSload("Transactions.csv"); // load all completed jobs
}

void GRSS::unLoadData(Transaction finished)
{
	inProgress = Transaction::GRSSload("GRSScreated.csv"); // customer creates
	specAvailable = Transaction::GRSSload("GRSSspecAvailable.csv"); // specialists says they're available
	specAccepted = Transaction::GRSSload("GRSSspecialistAccepted.csv"); // customer chooses specialist
	completed = Transaction::GRSSload("GRSSjobCompleted.csv"); // specialist marks job as completed, customer will add review and rating and confirm payment
	vector<Transaction>::iterator it;
	if (!(inProgress.empty()))
	{
		it = inProgress.begin();
		while (it != inProgress.end())
		{
			if (finished.getTransactionID() == (*it).getTransactionID()) inProgress.erase(it);
			if (!(inProgress.empty()))
			{
				if (it != inProgress.end()) it++;
			}
			else break;
		}
	}
	if (!(specAvailable.empty()))
	{
		it = specAvailable.begin();
		while (it != specAvailable.end())
		{
			if (finished.getTransactionID() == (*it).getTransactionID()) specAvailable.erase(it);
			if (!(specAvailable.empty()))
			{
				if (it != specAvailable.end()) it++;
			}
			else break;
		}
	}
	if (!(specAccepted.empty()))
	{
		it = specAccepted.begin();
		while (it != specAccepted.end())
		{
			if (finished.getTransactionID() == (*it).getTransactionID()) specAccepted.erase(it);
			if (!(specAccepted.empty()))
			{
				if (it != specAccepted.end()) it++;
			}
			else break;
		}
	}
	if(!(completed.empty()))
	{
		it = completed.begin();
		while (it != completed.end())
		{
			if (finished.getTransactionID() == (*it).getTransactionID()) completed.erase(it);
			if (!(completed.empty()))
			{
				if (it != completed.end()) it++;
			}
			else break;
		}
	}
	Transaction::GRSSsaveAll("GRSScreated.csv", inProgress);
	Transaction::GRSSsaveAll("GRSSspecAvailable.csv", specAvailable);
	Transaction::GRSSsaveAll("GRSSspecialistAccepted.csv", specAccepted);
	Transaction::GRSSsaveAll("GRSSjobCompleted.csv", completed);
}

void GRSS::loginPage()
{
	GRSS::loadInfo();
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
	_signUpButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		GRSS::registerPage();
	});

	Wt::WPushButton *_signInButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Sign In"));
	_signInButton->clicked().connect([=]
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
	vector<Administrator>::iterator aItr = existingAdmins.begin();
	do
	{
		Wt::WString user = cItr->getUserName();;
		if (user == username)
		{
			userFlag = 1;
			return true;
		}
		else if (cItr != existingCustomers.end()) cItr++;
	} while (cItr != existingCustomers.end());
	do
	{
		Wt::WString user = sItr->getUserName();
		user = sItr->getUserName();
		if (user == username)
		{
			userFlag = 2;
			return true;
		}
		else if (sItr != existingSpecialists.end()) sItr++;
	} while (sItr != existingSpecialists.end());
	do
	{
		Wt::WString user = aItr->getUserName();
		user = aItr->getUserName();
		if (user == username)
		{
			userFlag = 3;
			return true;
		}
		else if (aItr != existingAdmins.end()) aItr++;
	} while (aItr != existingAdmins.end());
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
		else if (userFlag == 3)
		{
			for (vector<Administrator>::iterator Itr = existingAdmins.begin(); Itr != existingAdmins.end(); Itr++)
			{
				Wt::WString user = Itr->getUserName();
				Wt::WString pass = Itr->getPassword();
				if ((user == username) && (pass == password))
				{
					logged_in_admin = *Itr;
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
		(!(GRSS::userAvailable(_usernameField->text()))) ? _usernameText->setText("Enter a Username<font color=\"red\"> This User Name is unavailable</font>") : _usernameText->setText("Enter a Username");
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
		(_passwordField->text() == _confirmPasswordField->text()) ? _confirmPasswordText->setText("Confirm Password") : _confirmPasswordText->setText("Confirm Password <font color=\"red\">Passwords Do NOT match</font>");
	});
	_passwordField->changed().connect([=] {
		if (_confirmPasswordField->text() != "") (_passwordField->text() == _confirmPasswordField->text()) ? _confirmPasswordText->setText("Confirm Password") : _confirmPasswordText->setText("Confirm Password <font color=\"red\">Passwords Do NOT match</font>");
	});

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());

	// cancel to go back to login screen, resets internal tmps to ""
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));
	_cancelButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		userTmp = "";
		pwTmp = "";
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
		if ((GRSS::userAvailable(_usernameField->text()) && (_passwordField->text() == _confirmPasswordField->text())) && (_usernameField->text() != "" && _passwordField->text() != ""  &&_confirmPasswordField->text() != "")) {
			_missingText->setHidden(true);
			userTmp = _usernameField->text().narrow();
			pwTmp = _passwordField->text().narrow();
			GRSS::registerPage2();
		}
		else _missingText->setHidden(false);
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
		fnameTmp = "";
		lnameTmp = "";
		licNumTmp = "";
		phoneTmp = "";
		emailTmp = "";
		GRSS::registerPage();
	});

	// confirm will add values to temp values and proceed to registerpage3
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Next"));
	_confirmButton->setStyleClass("btn-primary");
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		fnameTmp = _firstNameField->text().narrow();
		lnameTmp = _lastNameField->text().narrow();
		licNumTmp = _licenseField->text().narrow();
		phoneTmp = _contactPhoneField->text().narrow();
		emailTmp = _emailField->text().narrow();
		((regex_match(_emailField->text().narrow(), emailPattern)) && (fnameTmp != "") && (lnameTmp != "") && (licNumTmp != "") && (phoneTmp != "") && (emailTmp != "")) ? GRSS::registerPage3() : _missingText->setHidden(false);
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
			_qualNumberField->changed().connect([=]
			{
				qualNumTmp = _qualNumberField->text().narrow();
			});

			Wt::WText *_postCodeArea = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Choose your operating areas"));

			Wt::WSelectionBox *_postCodeSelection = _thirdPageLayout->addWidget(make_unique<Wt::WSelectionBox>());
			_postCodeSelection->addItem("2515");
			_postCodeSelection->addItem("2516");
			_postCodeSelection->addItem("2517");
			_postCodeSelection->addItem("2518");
			_postCodeSelection->addItem("2519");
			_postCodeSelection->addItem("2500");
			_postCodeSelection->addItem("2525");
			_postCodeSelection->addItem("2526");
			_postCodeSelection->addItem("2527");
			_postCodeSelection->addItem("2528");
			_postCodeSelection->addItem("2529");
			_postCodeSelection->addItem("2530");
			_postCodeSelection->addItem("2502");
			_postCodeSelection->addItem("2505");
			_postCodeSelection->addItem("2506");
			_postCodeSelection->setSelectionMode(Wt::SelectionMode::Extended);
			_postCodeSelection->activated().connect([=]
			{
				std::set<int> selection = _postCodeSelection->selectedIndexes();
				for (std::set<int>::iterator it = selection.begin(); it != selection.end(); ++it)
				{
					opAreaTmp.insert(_postCodeSelection->itemText(*it).narrow());
				}
			});
		}
		else if (rawButtonGroup->id(selection) == 2) {
			// 3rd page registration(Customer): home address, car details, bankCard details
			_thirdPageForm->clear();
			userFlag = 1;
			Wt::WVBoxLayout *_thirdPageLayout = _thirdPageForm->setLayout(make_unique<Wt::WVBoxLayout>());

			Wt::WText* _homeAddressText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Home Address"));
			Wt::WLineEdit* _homeAddressField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_homeAddressField->setPlaceholderText("221b Baker Street");
			_homeAddressField->changed().connect([=]
			{
				homeAddressTmp = _homeAddressField->text().narrow();
			});

			Wt::WText* _lcncPltText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Licence Plate"));
			Wt::WLineEdit* _lcncPltField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_lcncPltField->setPlaceholderText("BJB-007");
			_lcncPltField->changed().connect([=]
			{
				licPlateTmp = _lcncPltField->text().narrow();
			});

			Wt::WText* _modelYearText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Year Made"));
			Wt::WLineEdit* _modelYearField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_modelYearField->setPlaceholderText("2007");
			_modelYearField->changed().connect([=]
			{
				modelYearTmp = _modelYearField->text().narrow();
			});

			Wt::WText* _carMakeText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Make"));
			Wt::WLineEdit* _carMakeField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_carMakeField->setPlaceholderText("Toyboata");
			_carMakeField->changed().connect([=]
			{
				makeTmp = _carMakeField->text().narrow();
			});

			Wt::WText *_carModelText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Model"));
			Wt::WLineEdit* _carModelField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_carModelField->setPlaceholderText("Hilux");
			_carModelField->changed().connect([=]
			{
				modelTmp = _carModelField->text().narrow();
			});

			Wt::WText *_shapeText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Shape"));
			// replace with combo box MAYBE
			Wt::WLineEdit* _shapeField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_shapeField->setPlaceholderText("Ute");
			_shapeField->changed().connect([=]
			{
				shapeTmp = _shapeField->text().narrow();
			});

			Wt::WText *_engineSizeText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Engine Size"));
			Wt::WLineEdit* _engineSizeField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_engineSizeField->setPlaceholderText("3.4L");
			_engineSizeField->changed().connect([=]
			{
				engineSizeTmp = _engineSizeField->text().narrow();
			});

			Wt::WText *_carColourText = _thirdPageLayout->addWidget(make_unique<Wt::WText>("Car Colour"));
			Wt::WLineEdit* _carColourField = _thirdPageLayout->addWidget(make_unique<Wt::WLineEdit>());
			_carColourField->setPlaceholderText("Blue");
			_carColourField->changed().connect([=]
			{
				colourTmp = _carColourField->text().narrow();
			});
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
		for(int i = 0; i < 15; i++) check[i] = 0;
		qualNumTmp = "";
		homeAddressTmp = "";
		customerTmp = "";
		licPlateTmp = "";
		modelYearTmp = "";
		makeTmp = "";
		modelTmp = "";
		shapeTmp = "";
		engineSizeTmp = "";
		colourTmp = "";
		GRSS::registerPage2();
	});
	// confirm will create user profile and log them in (this assumes they've confirmed their account via email...)
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Next"));
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		if (userFlag == 1) {
			for (int i = 0; i < 15; i++)
			{
				if (check[i] != 0)
				{
					opAreaTmp.insert(postCodes[i]);
				}
			}
		}
		GRSS::registerPage4();
	});
}

void GRSS::registerPage4()
{
	if (userFlag == 1) {
		// customers
		_pageContent->clear();
		_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
		_pageContent->setId("pageContent");

		Wt::WText *_subscribeText = _pageLayout->addWidget(make_unique<Wt::WText>("Do you want to subscribe?"));
		Wt::WCheckBox *_subscribeCheck = _pageLayout->addWidget(make_unique<Wt::WCheckBox>("Subscribe?"));
		_subscribeCheck->changed().connect([=]
		{
			(_subscribeCheck->isChecked()) ? subFlagTmp = "0" : subFlagTmp = "1";
		});

		Wt::WText* _cadrNumText = _pageLayout->addWidget(make_unique<Wt::WText>("Credit Card Number"));
		Wt::WLineEdit* _cardNumField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
		_cardNumField->setPlaceholderText("5353091234567890");
		_cardNumField->changed().connect([=]
		{
			cardNumTmp = _cardNumField->text().narrow();
		});

		Wt::WText* _cardExpiryText = _pageLayout->addWidget(make_unique<Wt::WText>("Credit Card Expiry"));
		Wt::WLineEdit* _cardExpiryField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
		_cardExpiryField->setPlaceholderText("12/23");
		_cardExpiryField->changed().connect([=]
		{
			cardExpTmp = _cardExpiryField->text().narrow();
		});

		Wt::WText* _cardSecText = _pageLayout->addWidget(make_unique<Wt::WText>("Credit Card CSV"));
		Wt::WLineEdit* _cardSecField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
		_cardSecField->setPlaceholderText("XXX");
		_cardSecField->changed().connect([=]
		{
			cardSecTmp = _cardSecField->text().narrow();
		});
	}
	else if (userFlag == 2) {
		// specialists
		_pageContent->clear();
		_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
		_pageContent->setId("pageContent");
		Wt::WText* _BSBText = _pageLayout->addWidget(make_unique<Wt::WText>("BSB"));
		Wt::WLineEdit* _BSBField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
		_BSBField->setPlaceholderText("XXX-XXX");
		_BSBField->changed().connect([=]
		{
			BSBTmp = _BSBField->text().narrow();
		});

		Wt::WText* _accNumText = _pageLayout->addWidget(make_unique<Wt::WText>("Account Number"));
		Wt::WLineEdit* _accNumField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
		_accNumField->setPlaceholderText("Bank account number, for your preferred payment account");
		_accNumField->changed().connect([=]
		{
			accNumTmp = _accNumField->text().narrow();
		});

		Wt::WText* _accNameText = _pageLayout->addWidget(make_unique<Wt::WText>("Account Name"));
		Wt::WLineEdit* _accNameField = _pageLayout->addWidget(make_unique<Wt::WLineEdit>());
		_accNameField->setPlaceholderText("Bank account name, for your preferred payment account");
		_accNameField->changed().connect([=]
		{
			accNameTmp = _accNameField->text().narrow();
		});
	}

	// create buttons for confirm and cancel
	Wt::WContainerWidget *_buttonsContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
	_buttonsContainer->setId("buttons");
	Wt::WHBoxLayout *_buttonsLayout = _buttonsContainer->setLayout(make_unique<Wt::WHBoxLayout>());
	// cancel to go back to login screen
	Wt::WPushButton *_retraceButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_retraceButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		cardNumTmp = "";
		cardExpTmp = "";
		cardSecTmp = "";
		BSBTmp = "";
		accNumTmp = "";
		accNameTmp = "";
		GRSS::registerPage3();
	});
	// confirm will create user profile and log them in (this assumes they've confirmed their account via email...)
	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
	_confirmButton->clicked().connect([=](const Wt::WMouseEvent &e)
	{
		// this should point to loginPage() such that the user can log in with the newly created user
		// customer creation
		if (userFlag == 1) {
			Customer joined = Customer(("c" + to_string(existingCustomers.size() + 1)), userTmp, pwTmp, fnameTmp, lnameTmp, licNumTmp, phoneTmp, emailTmp, licPlateTmp, modelYearTmp, makeTmp, modelTmp, shapeTmp, colourTmp, engineSizeTmp, subFlagTmp, cardNumTmp, cardSecTmp, cardExpTmp);
			joined.saveCustomer();
			existingCustomers.push_back(joined);
		}
		// specialist creation
		else if (userFlag == 2) {
			if (!opAreaTmp.empty()) cout << "notEmpty\n";
			Specialist joined = Specialist(("s" + to_string(existingSpecialists.size() + 1)), userTmp, pwTmp, fnameTmp, lnameTmp, licNumTmp, phoneTmp, emailTmp, qualNumTmp, BSBTmp, accNumTmp, accNameTmp, opAreaTmp);
			joined.save();
			existingSpecialists.push_back(joined);
		}
		GRSS::loginPage();
	});
}

bool GRSS::userAvailable(Wt::WString username)
{
	vector<Customer>::iterator cItr = existingCustomers.begin();
	while (cItr != existingCustomers.end())
	{
		if (cItr->getUserName() == username) return false;
		else if (cItr != existingCustomers.end()) cItr++;
	}
	vector<Specialist>::iterator sItr = existingSpecialists.begin();
	while (sItr != existingSpecialists.end())
	{
		if (sItr->getUserName() == username) return false;
		else if (sItr != existingSpecialists.end()) sItr++;
	}
	return true;
}

void GRSS::userMenu()
{
	// want to put current request somewhere in this menu, probably after the buttons, ONLY IF they have a current request
	_pageContent->clear();
	inProgress = Transaction::GRSSload("GRSScreated.csv"); // customer creates
	specAvailable = Transaction::GRSSload("GRSSspecAvailable.csv"); // specialists says they're available
	specAccepted = Transaction::GRSSload("GRSSspecialistAccepted.csv"); // customer chooses specialist
	completed = Transaction::GRSSload("GRSSjobCompleted.csv"); // specialist marks job as completed, customer will add review and rating and confirm payment
	Wt::WVBoxLayout *_menuLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());

	// links to for now 3 options that the customer can do
	// connect to create service request page
	if (userFlag == 1)
	{
		Wt::WPushButton *_requestButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Service Request"));
		// connect to service creation page
		_requestButton->clicked().connect([=]
		{
			bool hasCurrent = false;
			for (vector<Transaction>::iterator it = inProgress.begin(); it != inProgress.end(); it++)
			{
				if ((*it).getCustID() == logged_in_customer.custID)
				{
					hasCurrent = true;
					break;
				}
			}
			bool hasAccepted = false;
			for (vector<Transaction>::iterator it = specAccepted.begin(); it != specAccepted.end(); it++)
			{
				if ((*it).getCustID() == logged_in_customer.custID)
				{
					hasAccepted = true;
					break;
				}
			}
			bool hasCompleted = false;
			for (vector<Transaction>::iterator it = completed.begin(); it != completed.end(); it++)
			{
				if ((*it).getCustID() == logged_in_customer.custID)
				{
					hasCompleted = true;
					break;
				}
			}
			if (hasCompleted) GRSS::requestComplete();
			else if (hasCurrent && hasAccepted) GRSS::requestInProgress();
			else if (hasCurrent) GRSS::customerRequest();
			else GRSS::createRequestPage();
		});
	}
	else if (userFlag == 2)
	{
		// view current requests in area
		Wt::WPushButton *_currentRequestsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Current Requests"));
		// connect to view requests page
		_currentRequestsButton->clicked().connect([=]
		{
			bool hasAccepted = false;
			for (vector<Transaction>::iterator it = specAccepted.begin(); it != specAccepted.end(); it++)
			{
				if ((*it).getSpecID() == logged_in_specialist.specialistID)
				{
					hasAccepted = true;
					break;
				}
			}
			(!hasAccepted) ? GRSS::viewRequests() : GRSS::specialistRequest();
			
		});
	}

	// connect to view manage details page
	Wt::WPushButton *_viewDetailsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("User Details"));
	_viewDetailsButton->clicked().connect([=]
	{
		GRSS::viewUserDetails();
	});

	// connects to view reciepts
	Wt::WPushButton *_viewTransactionsButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Transactions"));
	_viewTransactionsButton->clicked().connect([=]
	{
		GRSS::viewTransactions();
	});

	// logout
	Wt::WPushButton *_logoutButton = _menuLayout->addWidget(make_unique<Wt::WPushButton>("Log Out"));
	_logoutButton->clicked().connect([=]
	{
		GRSS::loginPage();
	});
}

// customer request menus
void GRSS::createRequestPage()
{
	// STRETCH add map widget, and only if you can pass data to and get data from
	_pageContent->clear();
	_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());

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
	_serviceType->addItem("Out of Fuel");
	_serviceType->addItem("Other, please describe");
	Wt::WTextArea *_descriptionArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>());
	_descriptionArea->setPlaceholderText("Add a Description");

	Wt::WHBoxLayout *_buttonsLayout = _pageLayout->addLayout(make_unique<Wt::WHBoxLayout>());
	Wt::WPushButton *_cancelButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));
	// connect to customer menu
	_cancelButton->clicked().connect([=]
	{
		stNameTmp = "";
		stNumTmp = "";
		postCodeTmp = "";
		locationDescTmp = "";
		incidentTypeTmp = "";
		incidentDescTmp = "";
		GRSS::userMenu();
	});

	Wt::WPushButton *_confirmButton = _buttonsLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
	// present with dialog/page for information confirmation, then connect to saveRequest such that specialist can respond
	_confirmButton->clicked().connect([=]
	{
		stNameTmp = _streetField->text().narrow();
		stNumTmp = _streetNumberField->text().narrow();
		postCodeTmp = _postField->text().narrow();
		locationDescTmp = _locationDescriptionArea->text().narrow();
		incidentTypeTmp = _serviceType->valueText().narrow();
		incidentDescTmp = _descriptionArea->text().narrow();

		// saves info as new transaction
		Transaction requested;
		requested.GRSScreate(("t" + to_string(previousTransactions.size() + inProgress.size() + 1)), logged_in_customer.custID, logged_in_customer.getCardNumber(), logged_in_customer.getCardExpiry(), stNameTmp, postCodeTmp, stNumTmp, locationDescTmp, incidentTypeTmp, incidentDescTmp, logged_in_customer.returnSubFlag());
		inProgress.push_back(requested);

		requested.GRSSsave("GRSScreated.csv");

		GRSS::customerRequest();
	});
}

void GRSS::customerRequest()
{
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=] { GRSS::userMenu(); });
	_pageLayout->addWidget(make_unique<Wt::WText>(stNumTmp + " " + stNameTmp + ", " + postCodeTmp));
	Wt::WTextArea *_locationDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>(locationDescTmp));
	_locationDescArea->setReadOnly(true);
	_pageLayout->addWidget(make_unique<Wt::WText>(incidentTypeTmp));
	Wt::WTextArea *_incDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>(incidentDescTmp));
	_incDescArea->setReadOnly(true);

	for (vector<Transaction>::iterator it = specAvailable.begin(); it != specAvailable.end(); ++it)
	{
		Specialist related;
		if (logged_in_customer.custID == (*it).getCustID())
		{
			for (vector<Specialist>::iterator itr = existingSpecialists.begin(); itr != existingSpecialists.end(); ++itr)
			{
				if ((*itr).specialistID == (*it).getSpecID())
				{
					related = (*itr);
					break;
				}
			}

			Wt::WContainerWidget *_requestContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
			Wt::WHBoxLayout *_requestHLayout = _requestContainer->setLayout(make_unique<Wt::WHBoxLayout>());
			Wt::WContainerWidget *_requestInfoContainer = _requestHLayout->addWidget(make_unique<Wt::WContainerWidget>(), 1);
			Wt::WVBoxLayout *_requestInfoLayout = _requestInfoContainer->setLayout(make_unique<Wt::WVBoxLayout>());
			_requestInfoLayout->addWidget(make_unique<Wt::WText>("Specialist Information: " + related.getFullName() + " " + related.getQualNum() /* add rating info*/));
			Wt::WPushButton *_acceptRequestButton = _requestHLayout->addWidget(make_unique<Wt::WPushButton>("Accept"), 0, Wt::AlignmentFlag::Middle);
			_acceptRequestButton->setHeight(75);
			_acceptRequestButton->clicked().connect([=]
			{
				(*it).GRSSsave("GRSSspecialistAccepted.csv");
				GRSS::userMenu();
			});
		}
	}
}

void GRSS::requestInProgress()
{
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=] { GRSS::userMenu(); });
	_pageLayout->addWidget(make_unique<Wt::WText>(stNumTmp + " " + stNameTmp + ", " + postCodeTmp));
	Wt::WTextArea *_locationDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>(locationDescTmp));
	_locationDescArea->setReadOnly(true);
	_pageLayout->addWidget(make_unique<Wt::WText>(incidentTypeTmp));
	Wt::WTextArea *_incDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>(incidentDescTmp));
	_locationDescArea->setReadOnly(true);

	for (vector<Transaction>::iterator it = specAvailable.begin(); it != specAvailable.end(); ++it)
	{
		Specialist related;
		if (logged_in_customer.custID == (*it).getCustID())
		{
			for (vector<Specialist>::iterator itr = existingSpecialists.begin(); itr != existingSpecialists.end(); ++itr)
			{
				if ((*itr).specialistID == (*it).getSpecID())
				{
					related = (*itr);
					break;
				}
			}

			Wt::WContainerWidget *_requestContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
			Wt::WHBoxLayout *_requestHLayout = _requestContainer->setLayout(make_unique<Wt::WHBoxLayout>());
			Wt::WContainerWidget *_requestInfoContainer = _requestHLayout->addWidget(make_unique<Wt::WContainerWidget>(), 1);
			Wt::WVBoxLayout *_requestInfoLayout = _requestInfoContainer->setLayout(make_unique<Wt::WVBoxLayout>());
			_requestInfoLayout->addWidget(make_unique<Wt::WText>("Specialist Information: " + related.getFullName() + " " + related.getQualNum() /* add rating info*/));
		}
	}
}

void GRSS::requestComplete()
{
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=] { GRSS::userMenu(); });

	for (vector<Transaction>::iterator it = completed.begin(); it != completed.end(); ++it)
	{
		Specialist related;
		if (logged_in_customer.custID == (*it).getCustID())
		{
			for (vector<Specialist>::iterator itr = existingSpecialists.begin(); itr != existingSpecialists.end(); ++itr)
			{
				if ((*itr).specialistID == (*it).getSpecID())
				{
					related = (*itr);
					break;
				}
			}
			_pageLayout->addWidget(make_unique<Wt::WText>("Location Information: " + (*it).getRequestData().getStNum() + " " + (*it).getRequestData().getStName() + ", " + (*it).getRequestData().getPostCode()));
			Wt::WTextArea *_locationDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getLocDesc()));
			_locationDescArea->setReadOnly(true);
			_pageLayout->addWidget(make_unique<Wt::WText>("Incident infomration: " + (*it).getRequestData().getServiceType()));
			Wt::WTextArea *_incDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getIncDesc()));
			_incDescArea->setReadOnly(true);
			_pageLayout->addWidget(make_unique<Wt::WText>("Specialist Information: " + related.getFullName() + " " + related.getQualNum() /* add rating info*/));
			cout << (*it).getReceiptData().getBSB() << " " << (*it).getReceiptData().getAccNum() << " " << (*it).getReceiptData().getAccName();
			_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getBSB() + " " + (*it).getReceiptData().getAccNum() + " " + (*it).getReceiptData().getAccName()));
			_pageLayout->addWidget(make_unique<Wt::WText>("Customer Information: " + logged_in_customer.getFullName()));
			_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getCardNum() + " " + (*it).getReceiptData().getCardExpiry()));
			_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getCallOut() + " " + (*it).getReceiptData().getServiceCost()));
			_pageLayout->addWidget(make_unique<Wt::WText>("Rate the specialist:"));
			Wt::WDoubleSpinBox *_ratingSpin = _pageLayout->addWidget(make_unique<Wt::WDoubleSpinBox>());
			_ratingSpin->setRange(0, 5);
			_ratingSpin->setValue(3.5);
			_ratingSpin->setDecimals(1);
			_ratingSpin->setSingleStep(0.1);
			_ratingSpin->setValueText(to_string(_ratingSpin->value()));
			_pageLayout->addWidget(make_unique<Wt::WText>("Review the specialist:"));
			Wt::WTextArea *_reviewDesc = _pageLayout->addWidget(make_unique<Wt::WTextArea>());
			_reviewDesc->setPlaceholderText("Review how the specialist did on this job...");
			Wt::WPushButton *_confirmButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
			_confirmButton->clicked().connect([=]
			{
				(*it).GRSSaddReviewData(to_string(_ratingSpin->value()), _reviewDesc->text().narrow());
				(*it).GRSSsave("Transactions.csv");
				GRSS::unLoadData(*it);
				GRSS::userMenu();
			});
		}
	}
}

// specialist request menus
void GRSS::viewRequests()
{
	// generates a list of current requests that match the current specialists operational area
	// only if the specialist hasn't been accepted for a job
	// if they've been selected for a job, shows that job, and button to mark the job as complete
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=] { GRSS::userMenu(); });
	// while there are requests matching area
	for (vector<Transaction>::iterator it = inProgress.begin(); it != inProgress.end(); ++it)
	{
		if (std::find(logged_in_specialist.operationalAreas.begin(), logged_in_specialist.operationalAreas.end(), (*it).getRequestData().getPostCode()) != logged_in_specialist.operationalAreas.end())
		{
			Wt::WContainerWidget *_requestContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
			Wt::WHBoxLayout *_requestHLayout = _requestContainer->setLayout(make_unique<Wt::WHBoxLayout>());
			Wt::WContainerWidget *_requestInfoContainer = _requestHLayout->addWidget(make_unique<Wt::WContainerWidget>(), 1);
			Wt::WVBoxLayout *_requestInfoLayout = _requestInfoContainer->setLayout(make_unique<Wt::WVBoxLayout>());
			_requestInfoLayout->addWidget(make_unique<Wt::WText>("Address Information: " + (*it).getRequestData().getStNum() + " " + (*it).getRequestData().getStName() + " " + (*it).getRequestData().getPostCode()));
			Wt::WTextArea *_locDescription = _requestInfoLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getLocDesc()));
			_locDescription->setReadOnly(true);
			_requestInfoLayout->addWidget(make_unique<Wt::WText>("Incident Info: " + (*it).getRequestData().getServiceType()));
			Wt::WTextArea *_requestDescription = _requestInfoLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getIncDesc()));
			_requestDescription->setReadOnly(true);
			Wt::WPushButton *_acceptRequestButton = _requestHLayout->addWidget(make_unique<Wt::WPushButton>("Accept"), 0, Wt::AlignmentFlag::Middle);
			_acceptRequestButton->setHeight(75);
			_acceptRequestButton->clicked().connect([=]
			{
				(*it).GRSSspecialistAvailable(logged_in_specialist.specialistID);
				(*it).GRSSsave("GRSSspecAvailable.csv");
			});
		}
	}
}

void GRSS::specialistRequest()
{
	specAccepted = Transaction::GRSSload("GRSSspecialistAccepted.csv");
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"));
	_backButton->clicked().connect([=] { GRSS::userMenu(); });
	// shows current job with a completion button
	vector<Transaction>::iterator it = specAccepted.begin();

	for (; it != specAccepted.end(); ++it)
	{
		if ((*it).getSpecID() == logged_in_specialist.specialistID)
		{

			Wt::WContainerWidget *_requestContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
			Wt::WHBoxLayout *_requestHLayout = _requestContainer->setLayout(make_unique<Wt::WHBoxLayout>());
			Wt::WContainerWidget *_requestInfoContainer = _requestHLayout->addWidget(make_unique<Wt::WContainerWidget>(), 1);
			Wt::WVBoxLayout *_requestInfoLayout = _requestInfoContainer->setLayout(make_unique<Wt::WVBoxLayout>());
			_requestInfoLayout->addWidget(make_unique<Wt::WText>("Address Information: " + (*it).getRequestData().getStNum() + " " + (*it).getRequestData().getStName() + " " + (*it).getRequestData().getPostCode()));
			Wt::WTextArea *_locDescription = _requestInfoLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getLocDesc()));
			_locDescription->setReadOnly(true);
			_requestInfoLayout->addWidget(make_unique<Wt::WText>("Incident Info: " + (*it).getRequestData().getServiceType()));
			Wt::WTextArea *_requestDescription = _requestInfoLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getIncDesc()));
			_requestDescription->setReadOnly(true);
			Wt::WPushButton *_completeRequestButton = _requestHLayout->addWidget(make_unique<Wt::WPushButton>("Complete"), 0, Wt::AlignmentFlag::Middle);
			_completeRequestButton->setHeight(75);
			_completeRequestButton->clicked().connect([=]
			{
				(*it).GRSSaddReceiptData(logged_in_specialist.getBSB(), logged_in_specialist.getAccNum(), logged_in_specialist.getAccName(), to_string(rand() % 100 + 100));
				(*it).GRSSsave("GRSSjobCompleted.csv");
			});
		}
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

	if (userFlag == 1)
	{
		_pageLayout->addWidget(make_unique<Wt::WText>("User Details:"))->setId("buttons");
		Wt::WContainerWidget *_userContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		_userContainer->addWidget(make_unique<Wt::WText>("Username: " + logged_in_customer.getUserName()));

		_pageLayout->addWidget(make_unique<Wt::WText>("Personal Details:"))->setId("buttons");
		Wt::WContainerWidget *_personalContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		_personalContainer->addWidget(make_unique<Wt::WText>("First Name: " + logged_in_customer.getFirstName()));

		Wt::WContainerWidget *_lastContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_lastContainer->addWidget(make_unique<Wt::WText>("Last Name: " + logged_in_customer.getLastName()));

		Wt::WContainerWidget *_phoneContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_phoneContainer->addWidget(make_unique<Wt::WText>("Phone Number: " + logged_in_customer.getNumber()));

		Wt::WContainerWidget *_licNumContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_licNumContainer->addWidget(make_unique<Wt::WText>("License Number: " + logged_in_customer.getLicenseNumber()));

		Wt::WContainerWidget *_emailContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_emailContainer->addWidget(make_unique<Wt::WText>("eMail Address: " + logged_in_customer.getEmail()));

		_pageLayout->addWidget(make_unique<Wt::WText>("Card Details:"))->setId("buttons");
		Wt::WContainerWidget *_cardContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());

		Wt::WContainerWidget *_cardNumContainer = _cardContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_cardNumContainer->addWidget(make_unique<Wt::WText>("Card Number: " + logged_in_customer.getCardNumber()));

		Wt::WContainerWidget *_cardExpContainer = _cardContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_cardExpContainer->addWidget(make_unique<Wt::WText>("Card Expiry: " + logged_in_customer.getCardExpiry()));

		_pageLayout->addWidget(make_unique<Wt::WText>("Card Details:"))->setId("buttons");
		Wt::WContainerWidget *_carContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());

		Wt::WContainerWidget *_carYearContainer = _carContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_carYearContainer->addWidget(make_unique<Wt::WText>("Year Car Made: " + logged_in_customer.getCarYear()));

		Wt::WContainerWidget *_carMakeContainer = _carContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_carMakeContainer->addWidget(make_unique<Wt::WText>("Car Make: " + logged_in_customer.getCarMake()));

		Wt::WContainerWidget *_carModelContainer = _carContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_carModelContainer->addWidget(make_unique<Wt::WText>("Car Model: " + logged_in_customer.getCarModel()));

		Wt::WContainerWidget *_carShapeContainer = _carContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_carShapeContainer->addWidget(make_unique<Wt::WText>("Car Shape: " + logged_in_customer.getCarShape()));

		Wt::WContainerWidget *_carEngContainer = _carContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_carEngContainer->addWidget(make_unique<Wt::WText>("Car Engine Size: " + logged_in_customer.getCarEngineSize()));

		Wt::WContainerWidget *_carColourContainer = _carContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_carColourContainer->addWidget(make_unique<Wt::WText>("Car Colour: " + logged_in_customer.getCarColour()));
	}
	else if (userFlag == 2)
	{
		_pageLayout->addWidget(make_unique<Wt::WText>("User Details:"))->setId("buttons");
		Wt::WContainerWidget *_userContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		_userContainer->addWidget(make_unique<Wt::WText>("Username: " + logged_in_specialist.getUserName()));

		_pageLayout->addWidget(make_unique<Wt::WText>("Personal Details:"))->setId("buttons");
		Wt::WContainerWidget *_personalContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		_personalContainer->addWidget(make_unique<Wt::WText>("First Name: " + logged_in_specialist.getFirstName()));

		Wt::WContainerWidget *_lastContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_lastContainer->addWidget(make_unique<Wt::WText>("Last Name: " + logged_in_specialist.getLastName()));

		Wt::WContainerWidget *_phoneContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_phoneContainer->addWidget(make_unique<Wt::WText>("Phone Number: " + logged_in_specialist.getNumber()));

		Wt::WContainerWidget *_licNumContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_licNumContainer->addWidget(make_unique<Wt::WText>("License Number: " + logged_in_specialist.getLicenseNumber()));

		Wt::WContainerWidget *_emailContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_emailContainer->addWidget(make_unique<Wt::WText>("eMail Address: " + logged_in_specialist.getEmail()));

		_pageLayout->addWidget(make_unique<Wt::WText>("Payment Details:"))->setId("buttons");
		Wt::WContainerWidget *_paymentContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WContainerWidget *_BSBContainer = _paymentContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_BSBContainer->addWidget(make_unique<Wt::WText>("BSB: " + logged_in_specialist.getBSB()));

		Wt::WContainerWidget *_accNumContainer = _paymentContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_accNumContainer->addWidget(make_unique<Wt::WText>("Account Number: " + logged_in_specialist.getAccNum()));

		Wt::WContainerWidget *_accNameContainer = _paymentContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_accNameContainer->addWidget(make_unique<Wt::WText>("Account Name: " + logged_in_specialist.getAccName()));

		_pageLayout->addWidget(make_unique<Wt::WText>("Specialist Details:"))->setId("buttons");
		Wt::WContainerWidget *_specialistContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		_specialistContainer->addWidget(make_unique<Wt::WText>("Qualification Number: " + logged_in_specialist.getQualNum()));

		Wt::WContainerWidget *_opAreaContainer = _specialistContainer->addWidget(make_unique<Wt::WContainerWidget>());
		stringstream ss;
		ss << "Qualification Number: ";
		for (set<string>::iterator it = logged_in_specialist.operationalAreas.begin(); it != logged_in_specialist.operationalAreas.end(); ++it)
		{
			if (it != logged_in_specialist.operationalAreas.begin()) ss << ", ";
			ss << (*it);
		}
		_opAreaContainer->addWidget(make_unique<Wt::WText>(ss.str()));
	}
	else if (userFlag == 3)
	{
		_pageLayout->addWidget(make_unique<Wt::WText>("User Details:"))->setId("buttons");
		Wt::WContainerWidget *_userContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		_userContainer->addWidget(make_unique<Wt::WText>("Username: " + logged_in_admin.getUserName()));

		_pageLayout->addWidget(make_unique<Wt::WText>("Personal Details:"))->setId("buttons");
		Wt::WContainerWidget *_personalContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		_personalContainer->addWidget(make_unique<Wt::WText>("First Name: " + logged_in_admin.getFirstName()));

		Wt::WContainerWidget *_lastContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_lastContainer->addWidget(make_unique<Wt::WText>("Last Name: " + logged_in_admin.getLastName()));

		Wt::WContainerWidget *_phoneContainer = _personalContainer->addWidget(make_unique<Wt::WContainerWidget>());
		_phoneContainer->addWidget(make_unique<Wt::WText>("Phone Number: " + logged_in_admin.getNumber()));
	}

	Wt::WPushButton *_editButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Edit"));
	_editButton->clicked().connect([=] { GRSS::editUserDetails(); });
}

void GRSS::editUserDetails()
{
	pwTmp = "";
	// registerpage2 tmp
	fnameTmp = "";
	lnameTmp = "";
	licNumTmp = "";
	phoneTmp = "";
	emailTmp = "";
	// registerpage3 tmp
	// cust
	homeAddressTmp = "";
	customerTmp = "";
	licPlateTmp = "";
	modelYearTmp = "";
	makeTmp = "";
	modelTmp = "";
	shapeTmp = "";
	engineSizeTmp = "";
	colourTmp = "";
	// spec
	opAreaTmp.clear();
	check[15] = {};
	qualNumTmp = "";
	// registerPage4 tmp
	// cust
	cardNumTmp = "";
	cardExpTmp = "";
	cardSecTmp = "";
	subFlagTmp = "";
	// spec
	BSBTmp = "";
	accNumTmp = "";
	accNameTmp = "";

	// create request tmp
	// location
	stNameTmp = "";
	stNumTmp = "";
	postCodeTmp = "";
	locationDescTmp = "";
	// incident
	incidentTypeTmp = "";
	incidentDescTmp = "";

	// shows all user details, has button to edit, editable fields
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_cancelButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Cancel"));
	_cancelButton->clicked().connect([=]
	{
		GRSS::viewUserDetails();
	});

	if (userFlag == 1)
	{
		_pageLayout->addWidget(make_unique<Wt::WText>("User Details:"))->setId("buttons");
		Wt::WContainerWidget *_userContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_userLayout = _userContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		_userLayout->addWidget(make_unique<Wt::WText>("Username: " + logged_in_customer.getUserName()));

		_userLayout->addWidget(make_unique<Wt::WText>("Old Password: "));
		Wt::WLineEdit *_pwOldEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwOldEdit->setPlaceholderText("Enter your old password");
		_pwOldEdit->setEchoMode(Wt::EchoMode::Password);
		_userLayout->addWidget(make_unique<Wt::WText>("New Password: "));
		Wt::WLineEdit *_pwNewEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwNewEdit->setPlaceholderText("Enter your new password");
		_pwNewEdit->setEchoMode(Wt::EchoMode::Password);
		_userLayout->addWidget(make_unique<Wt::WText>("Confirm New Password: "));
		Wt::WLineEdit *_pwConNewEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwConNewEdit->setPlaceholderText("Confirm your new password");
		_pwConNewEdit->setEchoMode(Wt::EchoMode::Password);

		_pageLayout->addWidget(make_unique<Wt::WText>("Personal Details:"))->setId("buttons");
		Wt::WContainerWidget *_personalContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_personalLayout = _personalContainer->setLayout(make_unique<Wt::WVBoxLayout>());

		_personalLayout->addWidget(make_unique<Wt::WText>("First Name: " + logged_in_customer.getFirstName()));
		Wt::WLineEdit *_firstEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_firstEdit->setPlaceholderText("Enter your new First Name");

		_personalLayout->addWidget(make_unique<Wt::WText>("Last Name: " + logged_in_customer.getLastName()));
		Wt::WLineEdit *_lastEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_lastEdit->setPlaceholderText("Enter your new Last Name");

		_personalLayout->addWidget(make_unique<Wt::WText>("Phone Number: " + logged_in_customer.getNumber()));
		Wt::WLineEdit *_phoneEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_phoneEdit->setPlaceholderText("Enter your new Phone Number");

		_personalLayout->addWidget(make_unique<Wt::WText>("License Number: " + logged_in_customer.getLicenseNumber()));
		Wt::WLineEdit *_licenseEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_licenseEdit->setPlaceholderText("Enter your new License Number");

		_personalLayout->addWidget(make_unique<Wt::WText>("eMail Address: " + logged_in_customer.getEmail()));
		Wt::WLineEdit *_eMailEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_eMailEdit->setPlaceholderText("Enter your new eMail Address");

		_pageLayout->addWidget(make_unique<Wt::WText>("Card Details:"))->setId("buttons");
		Wt::WContainerWidget *_cardContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_cardLayout = _cardContainer->setLayout(make_unique<Wt::WVBoxLayout>());

		_cardLayout->addWidget(make_unique<Wt::WText>("Card Number: " + logged_in_customer.getCardNumber()));
		Wt::WLineEdit *_numEdit = _cardLayout->addWidget(make_unique<Wt::WLineEdit>());
		_numEdit->setPlaceholderText("Enter your new Card Number");

		_cardLayout->addWidget(make_unique<Wt::WText>("Card Expiry: " + logged_in_customer.getCardExpiry()));
		Wt::WLineEdit *_expEdit = _cardLayout->addWidget(make_unique<Wt::WLineEdit>());
		_expEdit->setPlaceholderText("Enter your new Card Expiry");

		_cardLayout->addWidget(make_unique<Wt::WText>("Card Security: " + logged_in_customer.getCardSec()));
		Wt::WLineEdit *_secEdit = _cardLayout->addWidget(make_unique<Wt::WLineEdit>());
		_secEdit->setPlaceholderText("Enter your new Card Security");

		_pageLayout->addWidget(make_unique<Wt::WText>("Car Details:"))->setId("buttons");
		Wt::WContainerWidget *_carContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_carLayout = _carContainer->setLayout(make_unique<Wt::WVBoxLayout>());

		_carLayout->addWidget(make_unique<Wt::WText>("Year Car Made: " + logged_in_customer.getCarYear()));
		Wt::WLineEdit *_yearEdit = _carLayout->addWidget(make_unique<Wt::WLineEdit>());
		_yearEdit->setPlaceholderText("Enter your new Car Year");

		_carLayout->addWidget(make_unique<Wt::WText>("Car Make: " + logged_in_customer.getCarMake()));
		Wt::WLineEdit *_makeEdit = _carLayout->addWidget(make_unique<Wt::WLineEdit>());
		_makeEdit->setPlaceholderText("Enter your new Car Make");

		_carLayout->addWidget(make_unique<Wt::WText>("Car Model: " + logged_in_customer.getCarModel()));
		Wt::WLineEdit *_modelEdit = _carLayout->addWidget(make_unique<Wt::WLineEdit>());
		_modelEdit->setPlaceholderText("Enter your new Car Model");

		_carLayout->addWidget(make_unique<Wt::WText>("Car Shape: " + logged_in_customer.getCarShape()));
		Wt::WLineEdit *_shapeEdit = _carLayout->addWidget(make_unique<Wt::WLineEdit>());
		_shapeEdit->setPlaceholderText("Enter your new Car Shape");

		_carLayout->addWidget(make_unique<Wt::WText>("Car Engine Size: " + logged_in_customer.getCarEngineSize()));
		Wt::WLineEdit *_sizeEdit = _carLayout->addWidget(make_unique<Wt::WLineEdit>());
		_sizeEdit->setPlaceholderText("Enter your new Car Engine Size");

		_carLayout->addWidget(make_unique<Wt::WText>("Car Colour: " + logged_in_customer.getCarColour()));
		Wt::WLineEdit *_colourEdit = _carLayout->addWidget(make_unique<Wt::WLineEdit>());
		_colourEdit->setPlaceholderText("Enter your new Car Colour");

		Wt::WPushButton *_confirmButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
		_confirmButton->clicked().connect([=]
		{
			if (logged_in_customer.getPassword() == _pwOldEdit->text().narrow()) {
				if ((_pwNewEdit->text() == _pwConNewEdit->text()) && (_pwNewEdit->text() != "")) pwTmp = _pwNewEdit->text().narrow();
				if (_firstEdit->text() != "") fnameTmp = _firstEdit->text().narrow();
				if (_lastEdit->text() != "") lnameTmp = _lastEdit->text().narrow();
				if (_phoneEdit->text() != "") phoneTmp = _phoneEdit->text().narrow();
				if (_licenseEdit->text() != "") licNumTmp = _licenseEdit->text().narrow();
				if ((_eMailEdit->text() != "") && (regex_match(_eMailEdit->text().narrow(), emailPattern))) emailTmp = _eMailEdit->text().narrow();
				if (_numEdit->text() != "") cardNumTmp = _numEdit->text().narrow();
				if (_expEdit->text() != "") cardExpTmp = _expEdit->text().narrow();
				if (_secEdit->text() != "") cardSecTmp = _secEdit->text().narrow();
				if (_yearEdit->text() != "") modelYearTmp = _yearEdit->text().narrow();
				if (_makeEdit->text() != "") makeTmp = _makeEdit->text().narrow();
				if (_modelEdit->text() != "") modelTmp = _modelEdit->text().narrow();
				if (_shapeEdit->text() != "") shapeTmp = _shapeEdit->text().narrow();
				if (_sizeEdit->text() != "") engineSizeTmp = _sizeEdit->text().narrow();
				if (_colourEdit->text() != "") colourTmp = _colourEdit->text().narrow();
			}
			// else emit error
			GRSS::updateUsers();
			GRSS::loadInfo();
			vector<Customer>::iterator it = existingCustomers.begin();
			while (it != existingCustomers.end() && (*it).custID != logged_in_customer.custID) ++it;
			logged_in_customer = *it;
			GRSS::viewUserDetails();
			// update details that were changed and go back to view user details
		});
	}
	else if (userFlag == 2)
	{
		_pageLayout->addWidget(make_unique<Wt::WText>("User Details:"))->setId("buttons");
		Wt::WContainerWidget *_userContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_userLayout = _userContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		_userLayout->addWidget(make_unique<Wt::WText>("Username: " + logged_in_specialist.getUserName()));

		_userLayout->addWidget(make_unique<Wt::WText>("Old Password: "));
		Wt::WLineEdit *_pwOldEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwOldEdit->setPlaceholderText("Enter your old password");
		_pwOldEdit->setEchoMode(Wt::EchoMode::Password);
		_userLayout->addWidget(make_unique<Wt::WText>("New Password: "));
		Wt::WLineEdit *_pwNewEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwNewEdit->setPlaceholderText("Enter your new password");
		_pwNewEdit->setEchoMode(Wt::EchoMode::Password);
		_userLayout->addWidget(make_unique<Wt::WText>("Confirm New Password: "));
		Wt::WLineEdit *_pwConNewEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwConNewEdit->setPlaceholderText("Confirm your new password");
		_pwConNewEdit->setEchoMode(Wt::EchoMode::Password);

		_pageLayout->addWidget(make_unique<Wt::WText>("Personal Details:"))->setId("buttons");
		Wt::WContainerWidget *_personalContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_personalLayout = _personalContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		
		_personalLayout->addWidget(make_unique<Wt::WText>("First Name: " + logged_in_specialist.getFirstName()));
		Wt::WLineEdit *_firstEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_firstEdit->setPlaceholderText("Enter your new First Name");

		_personalLayout->addWidget(make_unique<Wt::WText>("Last Name: " + logged_in_specialist.getLastName()));
		Wt::WLineEdit *_lastEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_lastEdit->setPlaceholderText("Enter your new Last Name");

		_personalLayout->addWidget(make_unique<Wt::WText>("Phone Number: " + logged_in_specialist.getNumber()));
		Wt::WLineEdit *_phoneEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_phoneEdit->setPlaceholderText("Enter your new Phone Number");

		_personalLayout->addWidget(make_unique<Wt::WText>("License Number: " + logged_in_specialist.getLicenseNumber()));
		Wt::WLineEdit *_licenseEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_licenseEdit->setPlaceholderText("Enter your new License Number");

		_personalLayout->addWidget(make_unique<Wt::WText>("eMail Address: " + logged_in_specialist.getEmail()));
		Wt::WLineEdit *_eMailEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_eMailEdit->setPlaceholderText("Enter your new eMail Address");

		_pageLayout->addWidget(make_unique<Wt::WText>("Payment Details:"))->setId("buttons");
		Wt::WContainerWidget *_paymentContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_paymentLayout = _paymentContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		
		_paymentLayout->addWidget(make_unique<Wt::WText>("BSB: " + logged_in_specialist.getBSB()));
		Wt::WLineEdit *_bsbEdit = _paymentLayout->addWidget(make_unique<Wt::WLineEdit>());
		_bsbEdit->setPlaceholderText("Enter your new BSB");

		_paymentLayout->addWidget(make_unique<Wt::WText>("Account Number: " + logged_in_specialist.getAccNum()));
		Wt::WLineEdit *_numEdit = _paymentLayout->addWidget(make_unique<Wt::WLineEdit>());
		_numEdit->setPlaceholderText("Enter your new Account Number");

		_paymentLayout->addWidget(make_unique<Wt::WText>("Account Name: " + logged_in_specialist.getAccName()));
		Wt::WLineEdit *_nameEdit = _paymentLayout->addWidget(make_unique<Wt::WLineEdit>());
		_nameEdit->setPlaceholderText("Enter your new Account Name");

		_pageLayout->addWidget(make_unique<Wt::WText>("Specialist Details:"))->setId("buttons");
		Wt::WContainerWidget *_specialistContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_specLayout = _specialistContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		
		_specLayout->addWidget(make_unique<Wt::WText>("Qualification Number: " + logged_in_specialist.getQualNum()));
		Wt::WLineEdit *_qualEdit = _specLayout->addWidget(make_unique<Wt::WLineEdit>());
		_qualEdit->setPlaceholderText("Enter your new Qualification Number");

		stringstream ss;
		ss << "Operation Areas: ";
		for (set<string>::iterator it = logged_in_specialist.operationalAreas.begin(); it != logged_in_specialist.operationalAreas.end(); ++it)
		{
			if (it != logged_in_specialist.operationalAreas.begin()) ss << ", ";
			ss << (*it);
		}
		_specLayout->addWidget(make_unique<Wt::WText>(ss.str()));

		Wt::WSelectionBox *_postCodeSelection = _specLayout->addWidget(make_unique<Wt::WSelectionBox>());
		_postCodeSelection->addItem("2515");
		_postCodeSelection->addItem("2516");
		_postCodeSelection->addItem("2517");
		_postCodeSelection->addItem("2518");
		_postCodeSelection->addItem("2519");
		_postCodeSelection->addItem("2500");
		_postCodeSelection->addItem("2525");
		_postCodeSelection->addItem("2526");
		_postCodeSelection->addItem("2527");
		_postCodeSelection->addItem("2528");
		_postCodeSelection->addItem("2529");
		_postCodeSelection->addItem("2530");
		_postCodeSelection->addItem("2502");
		_postCodeSelection->addItem("2505");
		_postCodeSelection->addItem("2506");
		_postCodeSelection->setSelectionMode(Wt::SelectionMode::Extended);
		_postCodeSelection->activated().connect([=]
		{
			std::set<int> selection = _postCodeSelection->selectedIndexes();
			for (std::set<int>::iterator it = selection.begin(); it != selection.end(); ++it)
			{
				opAreaTmp.insert(_postCodeSelection->itemText(*it).narrow());
			}
		});

		Wt::WPushButton *_confirmButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
		_confirmButton->clicked().connect([=]
		{
			if (logged_in_specialist.getPassword() == _pwOldEdit->text().narrow())
			{
				if ((_pwNewEdit->text() == _pwConNewEdit->text()) && (_pwNewEdit->text() != "")) pwTmp = _pwNewEdit->text().narrow();
				if (_firstEdit->text() != "") fnameTmp = _firstEdit->text().narrow();
				if (_lastEdit->text() != "") lnameTmp = _lastEdit->text().narrow();
				if (_phoneEdit->text() != "") phoneTmp = _phoneEdit->text().narrow();
				if (_licenseEdit->text() != "") licNumTmp = _licenseEdit->text().narrow();
				if ((_eMailEdit->text() != "") && (regex_match(_eMailEdit->text().narrow(), emailPattern))) emailTmp = _eMailEdit->text().narrow();
				if (_bsbEdit->text() != "") BSBTmp = _bsbEdit->text().narrow();
				if (_numEdit->text() != "") accNumTmp = _numEdit->text().narrow();
				if (_nameEdit->text() != "") accNameTmp = _nameEdit->text().narrow();
				if (_qualEdit->text() != "") qualNumTmp = _qualEdit->text().narrow();
			}
			// else emit error
			GRSS::updateUsers();
			GRSS::loadInfo();
			vector<Specialist>::iterator it = existingSpecialists.begin();
			while (it != existingSpecialists.end() && (*it).specialistID != logged_in_specialist.specialistID) ++it;
			logged_in_specialist = *it;
			GRSS::viewUserDetails();
			// update details that were changed and go back to view user details
		});
	}
	else if (userFlag == 3)
	{
		_pageLayout->addWidget(make_unique<Wt::WText>("User Details:"))->setId("buttons");
		Wt::WContainerWidget *_userContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_userLayout = _userContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		_userLayout->addWidget(make_unique<Wt::WText>("Username: " + logged_in_admin.getUserName()));

		_userLayout->addWidget(make_unique<Wt::WText>("Old Password: "));
		Wt::WLineEdit *_pwOldEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwOldEdit->setPlaceholderText("Enter your old password");
		_pwOldEdit->setEchoMode(Wt::EchoMode::Password);
		_userLayout->addWidget(make_unique<Wt::WText>("New Password: "));
		Wt::WLineEdit *_pwNewEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwNewEdit->setPlaceholderText("Enter your new password");
		_pwNewEdit->setEchoMode(Wt::EchoMode::Password);
		_userLayout->addWidget(make_unique<Wt::WText>("Confirm New Password: "));
		Wt::WLineEdit *_pwConNewEdit = _userLayout->addWidget(make_unique<Wt::WLineEdit>());
		_pwConNewEdit->setPlaceholderText("Confirm your new password");
		_pwConNewEdit->setEchoMode(Wt::EchoMode::Password);

		_pageLayout->addWidget(make_unique<Wt::WText>("Personal Details:"))->setId("buttons");
		Wt::WContainerWidget *_personalContainer = _pageLayout->addWidget(make_unique<Wt::WContainerWidget>());
		Wt::WVBoxLayout *_personalLayout = _personalContainer->setLayout(make_unique<Wt::WVBoxLayout>());
		
		_personalLayout->addWidget(make_unique<Wt::WText>("First Name: " + logged_in_admin.getFirstName()));
		Wt::WLineEdit *_firstEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_firstEdit->setPlaceholderText("Enter your new First Name");

		_personalLayout->addWidget(make_unique<Wt::WText>("Last Name: " + logged_in_admin.getLastName()));
		Wt::WLineEdit *_lastEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_lastEdit->setPlaceholderText("Enter your new Last Name");

		_personalLayout->addWidget(make_unique<Wt::WText>("Phone Number: " + logged_in_admin.getNumber()));
		Wt::WLineEdit *_phoneEdit = _personalLayout->addWidget(make_unique<Wt::WLineEdit>());
		_phoneEdit->setPlaceholderText("Enter your new Phone Number");

		Wt::WPushButton *_confirmButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Confirm"));
		_confirmButton->clicked().connect([=]
		{
			if (logged_in_admin.getPassword() == _pwOldEdit->text().narrow()) {
				if ((_pwNewEdit->text() == _pwConNewEdit->text()) && (_pwNewEdit->text() != "")) pwTmp = _pwNewEdit->text().narrow();
				cout << pwTmp << endl;
				if (_firstEdit->text() != "") fnameTmp = _firstEdit->text().narrow();
				if (_lastEdit->text() != "") lnameTmp = _lastEdit->text().narrow();
				if (_phoneEdit->text() != "") phoneTmp = _phoneEdit->text().narrow();
			}
			// else emit error
			GRSS::updateUsers();
			GRSS::loadInfo();
			vector<Administrator>::iterator it = existingAdmins.begin();
			while (it != existingAdmins.end() && (*it).adminID != logged_in_admin.adminID) ++it;
			logged_in_admin = *it;
			GRSS::viewUserDetails();
			// update details that were changed and go back to view user details
		});
	}
}

// view transactions
void GRSS::viewTransactions()
{
	_pageContent->clear();
	Wt::WVBoxLayout *_pageLayout = _pageContent->setLayout(make_unique<Wt::WVBoxLayout>());
	Wt::WPushButton *_backButton = _pageLayout->addWidget(make_unique<Wt::WPushButton>("Back"), 1, Wt::AlignmentFlag::Middle);
	_backButton->clicked().connect([=] { GRSS::userMenu(); });
	int i = 0;
	if (userFlag == 1)
	{
		for (vector<Transaction>::iterator it = previousTransactions.begin(); it != previousTransactions.end(); ++it)
		{
			Specialist related;
			if (logged_in_customer.custID == (*it).getCustID())
			{
				for (vector<Specialist>::iterator itr = existingSpecialists.begin(); itr != existingSpecialists.end(); ++itr)
				{
					if ((*itr).specialistID == (*it).getSpecID())
					{
						related = (*itr);
						break;
					}
				}
				_pageLayout->addWidget(make_unique<Wt::WText>("Transaction " + to_string(++i)));
				_pageLayout->addWidget(make_unique<Wt::WText>("Location Information: " + (*it).getRequestData().getStNum() + " " + (*it).getRequestData().getStName() + ", " + (*it).getRequestData().getPostCode()));
				Wt::WTextArea *_locationDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getLocDesc()));
				_locationDescArea->setReadOnly(true);
				_pageLayout->addWidget(make_unique<Wt::WText>("Incident Information: " + (*it).getRequestData().getServiceType()));
				Wt::WTextArea *_incDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getIncDesc()));
				_incDescArea->setReadOnly(true);
				_pageLayout->addWidget(make_unique<Wt::WText>("Specialist Information: " + related.getFullName() + " " + related.getQualNum() /* add average rating info? */));
				_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getBSB() + " " + (*it).getReceiptData().getAccNum() + " " + (*it).getReceiptData().getAccName()));
				_pageLayout->addWidget(make_unique<Wt::WText>("Customer Information: " + logged_in_customer.getFullName()));
				_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getCardNum() + " " + (*it).getReceiptData().getCardExpiry()));
				_pageLayout->addWidget(make_unique<Wt::WText>("Payment Information: " + (*it).getReceiptData().getCallOut() + " " + (*it).getReceiptData().getServiceCost()));
				_pageLayout->addWidget(make_unique<Wt::WText>("Review Information: " + (*it).getReviewData().getJobRating() + " " + (*it).getReviewData().getReviewDesc()));
				_pageLayout->addWidget(make_unique<Wt::WText>());
			}
		}
	}
	else if (userFlag == 2)
	{

		for (vector<Transaction>::iterator it = previousTransactions.begin(); it != previousTransactions.end(); ++it)
		{
			Customer related;
			if (logged_in_specialist.specialistID == (*it).getSpecID())
			{
				for (vector<Customer>::iterator itr = existingCustomers.begin(); itr != existingCustomers.end(); ++itr)
				{
					if ((*itr).custID == (*it).getCustID())
					{
						related = (*itr);
						break;
					}
				}
				_pageLayout->addWidget(make_unique<Wt::WText>("Transaction " + to_string(++i)));
				_pageLayout->addWidget(make_unique<Wt::WText>("Location Information: " + (*it).getRequestData().getStNum() + " " + (*it).getRequestData().getStName() + ", " + (*it).getRequestData().getPostCode()));
				Wt::WTextArea *_locationDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getLocDesc()));
				_locationDescArea->setReadOnly(true);
				_pageLayout->addWidget(make_unique<Wt::WText>("Incident Information: " + (*it).getRequestData().getServiceType()));
				Wt::WTextArea *_incDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getIncDesc()));
				_incDescArea->setReadOnly(true);
				_pageLayout->addWidget(make_unique<Wt::WText>("Specialist Information: " + logged_in_specialist.getFullName() + " " + logged_in_specialist.getQualNum() /* add average rating info? */));
				_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getBSB() + " " + (*it).getReceiptData().getAccNum() + " " + (*it).getReceiptData().getAccName()));
				_pageLayout->addWidget(make_unique<Wt::WText>("Customer Information: " + related.getFullName()));
				_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getCardNum() + " " + (*it).getReceiptData().getCardExpiry()));
				_pageLayout->addWidget(make_unique<Wt::WText>("Payment Information: " + (*it).getReceiptData().getCallOut() + " " + (*it).getReceiptData().getServiceCost()));
				_pageLayout->addWidget(make_unique<Wt::WText>("Review Information: " + (*it).getReviewData().getJobRating() + " " + (*it).getReviewData().getReviewDesc()));
				_pageLayout->addWidget(make_unique<Wt::WText>());
			}
		}
	}
	else if(userFlag == 3)
		{

		for (vector<Transaction>::iterator it = previousTransactions.begin(); it != previousTransactions.end(); ++it)
		{
			Customer relatedCust;
			Specialist relatedSpec;
			for (vector<Specialist>::iterator itr = existingSpecialists.begin(); itr != existingSpecialists.end(); ++itr)
			{
				if ((*itr).specialistID == (*it).getSpecID())
				{
					relatedSpec = (*itr);
					break;
				}
			}
			for (vector<Customer>::iterator itr = existingCustomers.begin(); itr != existingCustomers.end(); ++itr)
			{
				if ((*itr).custID == (*it).getCustID())
				{
					relatedCust = (*itr);
					break;
				}
			}
			_pageLayout->addWidget(make_unique<Wt::WText>("Transaction " + to_string(++i)));
			_pageLayout->addWidget(make_unique<Wt::WText>("Location Information: " + (*it).getRequestData().getStNum() + " " + (*it).getRequestData().getStName() + ", " + (*it).getRequestData().getPostCode()));
			Wt::WTextArea *_locationDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getLocDesc()));
			_locationDescArea->setReadOnly(true);
			_pageLayout->addWidget(make_unique<Wt::WText>("Incident Information: " + (*it).getRequestData().getServiceType()));
			Wt::WTextArea *_incDescArea = _pageLayout->addWidget(make_unique<Wt::WTextArea>((*it).getRequestData().getIncDesc()));
			_incDescArea->setReadOnly(true);
			_pageLayout->addWidget(make_unique<Wt::WText>("Specialist Information: " + relatedSpec.getFullName() + " " + relatedSpec.getQualNum() /* add average rating info? */));
			_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getBSB() + " " + (*it).getReceiptData().getAccNum() + " " + (*it).getReceiptData().getAccName()));
			_pageLayout->addWidget(make_unique<Wt::WText>("Customer Information: " + relatedCust.getFullName()));
			_pageLayout->addWidget(make_unique<Wt::WText>((*it).getReceiptData().getCardNum() + " " + (*it).getReceiptData().getCardExpiry()));
			_pageLayout->addWidget(make_unique<Wt::WText>("Payment Information: " + (*it).getReceiptData().getCallOut() + " " + (*it).getReceiptData().getServiceCost()));
			_pageLayout->addWidget(make_unique<Wt::WText>("Review Information: " + (*it).getReviewData().getJobRating() + " " + (*it).getReviewData().getReviewDesc()));
			_pageLayout->addWidget(make_unique<Wt::WText>());
		}
	}
}

void GRSS::updateUsers()
{
	if (userFlag == 1)
	{
		vector<Customer>::iterator it = existingCustomers.begin();
		while (it != existingCustomers.end() && (*it).custID != logged_in_customer.custID) ++it;
		if (pwTmp != "") (*it).setPassword(pwTmp);
		if (fnameTmp != "") (*it).setFirstName(fnameTmp);
		if (lnameTmp != "") (*it).setLastName(lnameTmp);
		if (phoneTmp != "") (*it).setNumber(phoneTmp);
		if (licNumTmp != "") (*it).setLicenseNumber(licNumTmp);
		if (emailTmp != "") (*it).setEmail(emailTmp);
		if (cardNumTmp != "") (*it).setCardNumber(cardNumTmp);
		if (cardExpTmp != "") (*it).setCardExpiry(cardExpTmp);
		if (cardSecTmp != "") (*it).setCardSec(cardSecTmp);
		if (modelYearTmp != "") (*it).setCarYear(modelYearTmp);
		if (makeTmp != "") (*it).setCarMake(makeTmp);
		if (modelTmp != "") (*it).setCarModel(modelTmp);
		if (shapeTmp != "") (*it).setCarShape(shapeTmp);
		if (engineSizeTmp != "") (*it).setCarEngineSize(engineSizeTmp);
		if (colourTmp != "") (*it).setCarColour(colourTmp);
		Customer::saveCustomerAll(existingCustomers);
	}
	else if (userFlag == 2)
	{
		vector<Specialist>::iterator it = existingSpecialists.begin();
		while (it != existingSpecialists.end() && (*it).specialistID != logged_in_specialist.specialistID) ++it;
		if (pwTmp != "") (*it).setPassword(pwTmp);
		if (fnameTmp != "") (*it).setFirstName(fnameTmp);
		if (lnameTmp != "") (*it).setLastName(lnameTmp);
		if (phoneTmp != "") (*it).setNumber(phoneTmp);
		if (licNumTmp != "") (*it).setLicenseNumber(licNumTmp);
		if (emailTmp != "") (*it).setEmail(emailTmp);
		if (BSBTmp != "") (*it).setBsb(BSBTmp);
		if (accNumTmp != "") (*it).setAccount_num(accNumTmp);
		if (accNameTmp != "") (*it).setAccount_name(accNameTmp);
		if (qualNumTmp != "") (*it).setQualification(qualNumTmp);
		Specialist::saveAll(existingSpecialists);
	}
	else if (userFlag == 3)
	{
		vector<Administrator>::iterator it = existingAdmins.begin();
		while (it != existingAdmins.end() && (*it).adminID != logged_in_admin.adminID) ++it;
		if (pwTmp != "") (*it).setPassword(pwTmp);
		if (fnameTmp != "") (*it).setFirstName(fnameTmp);
		if (lnameTmp != "") (*it).setLastName(lnameTmp);
		if (phoneTmp != "") (*it).setNumber(phoneTmp);
		Administrator::saveAdministratorAll(existingAdmins);
	}
}