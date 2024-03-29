#include "responsive_window.h"
#include "responsive_layout.h"
#include "screenshot.h"
#include <iostream>
#include <QApplication>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <vector>


ResponsiveWindow::ResponsiveWindow() {

    setWindowTitle("2811: Coursework 1");
    setMinimumSize(320, 320);
	
    createWidgets();
}

void ResponsiveWindow::createWidgets() {

	ResponsiveLayout* rl = new ResponsiveLayout();                // main layout
	
	rl->addWidget(new ResponsiveLabel(kNavTabs));                 // add responsive labels to the layout
	rl->addWidget(new ResponsiveLabel(kSearchText));
	rl->addWidget(new ResponsiveLabel(kSearchButton));
	rl->addWidget(new ResponsiveLabel(kBackButton));
	rl->addWidget(new ResponsiveLabel(kSearchOptions));
	rl->addWidget(new ResponsiveLabel(kSignIn));
	rl->addWidget(new ResponsiveLabel(kShoppingBasket));
	rl->addWidget(new ResponsiveLabel(kHomeLink));
	rl->addWidget(new ResponsiveLabel(kFavorite));
	rl->addWidget(new ResponsiveLabel(kMessage));
	rl->addWidget(new ResponsiveLabel(kResultSorting));

	ResponsiveLabel* blank = new ResponsiveLabel(kBlank);         // add scrollarea to the layout
	rl->addWidget(blank);
	setScrollarea(blank, 12);

	rl->addWidget(new ResponsiveLabel(kSearchResult));            // we might have more than one search results
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kSearchResult));
	rl->addWidget(new ResponsiveLabel(kAdvert));
	rl->addWidget(new ResponsiveLabel(kSearchForward));
	rl->addWidget(new ResponsiveLabel(kSearchBackward));
	rl->addWidget(new ResponsiveLabel(kFooter));

	setLayout(rl);                                                // set layout
}

void ResponsiveWindow::setScrollarea(QWidget* qw, int n) {        // set scroll area
	
		QLayout* horizontal = new QHBoxLayout(qw);                // create a horizontal layout
		QScrollArea* scroll = new QScrollArea(qw);                // create a QScrollArea
		QWidget* all = new QWidget();                             // create a widget to contain results
		scroll->setWidgetResizable(true);                         // make widget resizable
		all->setMinimumSize(QSize(200, 80 * n + 5 * (n+1)));      // set minimum size of the widget to let it contain all results
		int i = 0;
		QLabel* result;
		for (i = 0; i < n; i++) {                                 // for each result
			result = new QLabel(all);
			result->setText("result");
			result->setAlignment(Qt::AlignCenter);
			result->setGeometry(QRect(qw->x() + 5, 5 + 80 * i + 5 * i, qw->width() - 386, 80));
			result->setStyleSheet("border:1px solid; background-color: #99ddff; border-radius:4px;color:black;");
		}
		
		scroll->setWidget(all);                                   // add widget to scroll area
		horizontal->addWidget(scroll);                            // add scroll area to layout
}

// please DO NOT edit this file beyond this line
int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    cout << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // create a window. See respsonsive_window.cpp!
    if (argc-1)  {
        // grading-mode - run the screenshot subclass
        Screenshot screenshot;
        screenshot.show();
        // wait for the app to terminate
        return app.exec();
    } else {
        // interactive mode - run the regular superclass
        ResponsiveWindow window;
        window.show();
        // wait for the app to terminate
        return app.exec();
    }

}

