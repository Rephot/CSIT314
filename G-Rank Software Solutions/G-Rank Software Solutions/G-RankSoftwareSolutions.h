#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerwidget>
#include <Wt/WLink>
#include <Wt/WText>

using namespace Wt;
using namespace std;

class GRankSoftwareSolutions : public WApplication {
private:
	std::string appName;
	WContainerWidget* _content;

public:
	GRankSoftwareSolutions(const WEnvironment &env) : WApplication(env) {
		init();

		appName = "Application Name";
		setTitle(appName);
		_content = 0;
		internalPathChanged().connect(this, &GRankSoftwareSolutions::onInternalPathChange);

		header();
		home();
		sidebar();
		footer();
	};

	WContainerWidget* content();
	void onInternalPathChange();
	void header();
	void sidebar();
	void footer();
	void home();
	void page1();
	void init();
};