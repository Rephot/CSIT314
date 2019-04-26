// currently this is code for a simple Hello World esque example, this class shall have different functions that will create pages related to each of the user stories and will interact with the other classes in the program
/*
nav page placeholder
serviceRequest creation
	links to ???
	map
	type
	description
*/

#include"G-RankSoftwareSolutions.h"

WContainerWidget* GRankSoftwareSolutions::content() {
	if (_content == 0) {
		_content = root()->addWidget(make_unique<WContainerWidget>());
		_content->setId("content");
	}
	return _content;
}

void GRankSoftwareSolutions::onInternalPathChange() {
	content()->clear();
	if (internalPath() == "/") {
		home();
	}
	else if (internalPath() == "/page1") {
		page1();
	}
}

void GRankSoftwareSolutions::header() {
	WContainerWidget* header = root()->addWidget(make_unique<WContainerWidget>());
	header->setId("header");
	header->addWidget(make_unique<WText>("<h1>" + appName + "</h1>"));
}

void GRankSoftwareSolutions::sidebar() {
	WContainerWidget* sidebar = root()->addWidget(make_unique<WContainerWidget>());
	sidebar->setId("sidebar");
	sidebar->addWidget(make_unique<WText>("Sidebar Information"));
}

void GRankSoftwareSolutions::footer() {
	WContainerWidget* footer = root()->addWidget(make_unique<WContainerWidget>());
	footer->setId("footer");
	footer->addWidget(make_unique<WText>("Developed using C++/Wt"));
}

void GRankSoftwareSolutions::home() {
	WText *t = new WText("<strong>Home</strong> content and a link to <a href='#/page1'>page1</a>");
	t->setInternalPathEncoding(true);
	content()->addWidget(make_unique<WText>("<strong>Home</strong> content and a link to <a href='#/page1'>page1</a>"));

}

void GRankSoftwareSolutions::page1() {
	content()->addWidget(make_unique<WText>("<strong>Home</strong> content and a link to "));
	WAnchor* a = new WAnchor(WLink("/"), "home");
}

void GRankSoftwareSolutions::init() {
	instance()->styleSheet().addRule("#header", "background-color: #262626; color: #fff; padding: 0.1em 0.5em; ");
	instance()->styleSheet().addRule("#content", "display: inline-block; width: 65 % ; padding: 0.5em; ");
	instance()->styleSheet().addRule("#sidebar", "display: inline-block; width: 30 % ; padding: 0.5em; ");
	instance()->styleSheet().addRule("#footer", "background-color: #262626; color: #fff; padding: 0.5em; ");
	instance()->styleSheet().addRule("body", "background-color: #F0F8FF; ");
}