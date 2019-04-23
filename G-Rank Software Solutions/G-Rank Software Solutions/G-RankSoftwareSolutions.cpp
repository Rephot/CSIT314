// currently this is code for a simple Hello World esque example, this class shall have different functions that will create pages related to each of the user stories and will interact with the other classes in the program

#include"G-RankSoftwareSolutions.h"

GRankApplication::GRankApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	setTitle("CarTrubleAssistance by G-Rank Software Solutions");

	root()->addWidget(std::make_unique<Wt::WText>("I Knew It!!!"));

	root()->addWidget(std::make_unique<Wt::WBreak>());

	root()->addWidget(std::make_unique<Wt::WText>("A try at root() container"));

	for (unsigned int i = 0; i < 3; ++i) {
		// A widget can be added to a container by using addWidget()
		root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>Text {1}</p>").arg(i)));
	}

	root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
	nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
	root()->addWidget(std::make_unique<Wt::WBreak>());
	greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
	auto greet = [this] {
		greeting_->setText("Hello there, " + nameEdit_->text());
	};
	button->clicked().connect(greet);
}