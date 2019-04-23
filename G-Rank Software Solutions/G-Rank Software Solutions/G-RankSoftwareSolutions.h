#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>

class GRankApplication : public Wt::WApplication
{
public:
	GRankApplication(const Wt::WEnvironment& env);

private:
	Wt::WLineEdit *nameEdit_;
	Wt::WText *greeting_;
	std::unique_ptr<Wt::WContainerWidget> container;
};