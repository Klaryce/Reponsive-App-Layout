#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>
#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QLineEdit>
#include <QFont>

using namespace std;

void ResponsiveLayout::setGeometry(const QRect& r) {

	
	if (r.height() >= r.width()) {       // portrait screen
		if (r.width() > 400) {           // long width
			setLargeVGeometry(r);
		}
		else {                           // short width
			setSmallVGeometry(r);
		}
	}
	else {                               // landscape screen
		if (r.height() > 720)            // long height
			setLargeHGeometry(r);
		else if (r.height() > 550)       // medium height
			setMediumHGeometry(r);
		else                             // short height
			setSmallHGeometry(r);
	}
}

void ResponsiveLayout::setSmallVGeometry(const QRect& r) {                                   // set geometry for small vertical layout

	QLayout::setGeometry(r);
	int result_number = 0;                                                                   // initialize result_number
	int maxline = (r.height() - 40*3-25-35-5*4) / 105;                                       // calculate max number of lines of results

	for (int i = 0; i < list_.size(); i++) {                                                 // for all the Widgets added in ResponsiveWindow.cpp

		QLayoutItem* o = list_.at(i);

		try {
			ResponsiveLabel* label = static_cast<ResponsiveLabel*>(o->widget());             // cast the widget to one of our responsive labels
			smallVJudge(label, r, maxline, result_number);                                   // call function to judge where to put labels in small vertical screen
			
		}
		catch (bad_cast) {
			cout << "warning, unknown widget class in layout" << endl;                       // bad_case: cast failed on reference...
		}
	}
}

void ResponsiveLayout::smallVJudge(ResponsiveLabel* label, const QRect& r, int maxline, int& result_number) {     // judge where to put labels in a small vertical layout

	if (label == NULL)                                                                                  // null: cast failed on pointer
		cout << "warning, unknown widget class in layout" << endl;

	else if (label->text() == kShoppingBasket)                                                          // line 1, 40 height
		label->setGeometry(r.width() - 5 - 60 + r.x(), 0 + r.y(), 60, 40);                             
	else if (label->text() == kSignIn)                                                                  
		label->setGeometry(r.width() - 5 * 2 - 60 * 2 + r.x(), 0 + r.y(), 60, 40);                      
	else if (label->text() == kBackButton)                                                              
		label->setGeometry(5 + r.x(), 0 + r.y(), 50, 40);                                               
	else if (label->text() == kNavTabs)                                                                 
		label->setGeometry(5 * 2 + 50 + r.x(), 0 + r.y(), r.width() - 5 * 5 - 60 * 2 - 50, 40);         
	else if (label->text() == kSearchOptions)                                                           // line 2, 40 height
		label->setGeometry(5 + r.x(), 45 + r.y(), 115, 40);
	else if (label->text() == kSearchText)                                                             
		label->setGeometry(125 + r.x(), 45 + r.y(), r.width() - 190, 40);
	else if (label->text() == kSearchButton)                                                            
		label->setGeometry(r.width() - 60 + r.x(), 45 + r.y(), 55, 40);
	else if (label->text() == kResultSorting)                                                           // line 3, 35 height
		label->setGeometry(5 + r.x(), 90 + r.y(), r.width() - 10, 35);
	else if (label->text() == kSearchResult &&  (r.width() > 320 || r.height() > 320)) {                // line 4-n, each 100 height, show results (if the window is big enough)
		if (result_number < maxline)                                                                    // if not fill the page
			label->setGeometry(5 + r.x(), 130 + 105 * result_number + r.y(), r.width() - 10, 100);
		else                                                                                            // if fill the page
			label->setGeometry(-1, -1, 0, 0);
		result_number++;
	}
	else if (label->text() == kBlank && r.width() <= 320 && r.height() <= 320)                          // if the window is too small, use scrollarea to show result
		label->setGeometry(5 + r.x(), 130 + r.y(), r.width() - 10, 150);
	else if (label->text() == kSearchBackward && (r.width() > 320 || r.height() > 320) && result_number > maxline ) { 
		label->setGeometry(r.width() / 2 - 35 + r.x(), r.height() - 25 - 35 - 5, 30, 25);               // if one page cannot contain all results, show searching backward button, 25 height
	}
	else if (label->text() == kSearchForward && (r.width() > 320 || r.height() > 320) && result_number > maxline )      
		label->setGeometry(r.width() / 2 + 5 + r.x(), r.height() - 25 - 35 - 5, 30, 25);                // if one page cannot contain all results, show searching forward button, 25 height
	else if (label->text() == kFooter)                                                                  // last line, 35 height
		label->setGeometry(5 + r.x(), r.height() - 35, r.width()-10, 35);
	else                                                                                                // otherwise: disappear label by moving out of bounds
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setLargeVGeometry(const QRect& r) {                             // set geometry for large vertical layout

	QLayout::setGeometry(r);
	int result_number = 0;
	int maxline = (r.height() - 155 - 35) / 105;                                       // calculate max number of lines of results
	
	for (int i = 0; i < list_.size(); i++) {                                           // for all the Widgets added in ResponsiveWindow.cpp

		QLayoutItem* o = list_.at(i);

		try {
			ResponsiveLabel* label = static_cast<ResponsiveLabel*>(o->widget());       // cast the widget to one of our responsive labels
			largeVJudge(label, r, maxline, result_number);                             // call function to judge where to put labels in large vertical screen
		}
		catch (bad_cast) {
			cout << "warning, unknown widget class in layout" << endl;                 // bad_case: cast failed on reference...
		}
	}
}

void ResponsiveLayout::largeVJudge(ResponsiveLabel* label, const QRect& r, int maxline, int& result_number) {        // judge where to put labels in a large vertical layout

	if (label == NULL)                                                                           // null: cast failed on pointer
		cout << "warning, unknown widget class in layout" << endl;

	else if (label->text() == kShoppingBasket)                                                   // line 1, 40 height
		label->setGeometry(r.width() - 10 - 75 + r.x(), 0 + r.y(), 75, 40);
	else if (label->text() == kSignIn)
		label->setGeometry(r.width() - 10 - 5 - 75 * 2 + r.x(), 0 + r.y(), 75, 40);
	else if (label->text() == kBackButton)
		label->setGeometry(10 + r.x(), 0 + r.y(), 50, 40);
	else if (label->text() == kMessage)
		setLargeVMessage(label, r);
	else if (label->text() == kFavorite)
		setLargeVFavorite(label, r);
	else if (label->text() == kHomeLink)
		setLargeVHomeLink(label, r);
	else if (label->text() == kNavTabs)
		setLargeVNav(label, r);
	else if (label->text() == kSearchOptions)                                                    // line 2, 40 height
		label->setGeometry(10 + r.x(), 45 + r.y(), 120, 40);
	else if (label->text() == kSearchText)
		label->setGeometry(135 + r.x(), 45 + r.y(), r.width() - 205, 40);
	else if (label->text() == kSearchButton)
		label->setGeometry(r.width() - 65 + r.x(), 45 + r.y(), 55, 40);
	else if (label->text() == kResultSorting)                                                    // line 3, 35 height
		label->setGeometry(10 + r.x(), 90 + r.y(), r.width() - 20, 35);
	else if (label->text() == kSearchResult && (r.width() > 320 || r.height() > 320)) {          // line 4-n, each 100 height
		if (result_number < maxline)                                                             // if not fill the page
			label->setGeometry(10 + r.x(), 130 + 105 * result_number + r.y(), r.width() - 20, 100);
		else                                                                                     // if fill the page
			label->setGeometry(-1, -1, 0, 0);
		result_number++;
	}
	else if (label->text() == kSearchBackward && result_number > maxline)                       // if one page cannot contain all results, show searching backward button, 25 height
		label->setGeometry(r.width() / 2 - 35 + r.x(), r.height() - 25 - 35 - 5, 30, 25);
	else if (label->text() == kSearchForward && result_number > maxline)                        // if one page cannot contain all results, show searching forward button, 25 height
		label->setGeometry(r.width() / 2 + 5 + r.x(), r.height() - 25 - 35 - 5, 30, 25);
	else if (label->text() == kFooter)                                                          // last line, 35 height
		label->setGeometry(10 + r.x(), r.height() - 35, r.width()-20, 35);
	else                                                                                        // otherwise: disappear label by moving out of bounds
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setLargeVNav(ResponsiveLabel* label, const QRect& r) {                                       // set geometry of the navigation in the large vertical layout

	if (r.width() > 720)                                                                                            // if kMessage, kFavorite and kHomeLink all show
		label->setGeometry(10 + 5 + 50 + 75 + 5 + r.x(), 0 + r.y(), r.width() - 6 * 5 - 75 * 5 - 50 - 10 * 2, 40);
	else if (r.width() > 550)                                                                                       // if kHomeLink shows, kMessage and kFavorite hide
		label->setGeometry(10 + 5 + 50 + 75 + 5 + r.x(), 0 + r.y(), r.width() - 4 * 5 - 75 * 3 - 50 - 10 * 2, 40);
	else                                                                                                            // if kHomeLink, kMessage and kFavorite all hide
		label->setGeometry(10 + 5 + 50 + r.x(), 0 + r.y(), r.width() - 3 * 5 - 75 * 2 - 50 - 10 * 2, 40);
}

void ResponsiveLayout::setLargeVMessage(ResponsiveLabel* label, const QRect& r) {            // set geometry of the message in the large vertical layout

	if (r.width() > 720)                                                                     // if width longer than 720 show label kMessage
		label->setGeometry(r.width() - 10 - 5 * 2 - 75 * 3 + r.x(), 0 + r.y(), 75, 40);
	else                                                                                     // else hide label
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setLargeVFavorite(ResponsiveLabel* label, const QRect& r) {           // set geometry of the favorite in the large vertical layout

	if (r.width() > 720)                                                                     // if width longer than 720 show label kFavorite
		label->setGeometry(r.width() - 10 - 5 * 3 - 75 * 4 + r.x(), 0 + r.y(), 75, 40);
	else                                                                                     // else hide label
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setLargeVHomeLink(ResponsiveLabel* label, const QRect& r) {           // set geometry of the homelink in the large vertical layout

	if (r.width() > 550)                                                                     // if width longer than 550 show label kHomeLink
		label->setGeometry(10 + 5 + 50 + r.x(), 0 + r.y(), 75, 40);
	else                                                                                     // else hide label
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setLargeHGeometry(const QRect& r) {                                   // set geometry for large horizontal layout

	QLayout::setGeometry(r);
	int result_number = 0;
	int result_line = 0;
	int advert_number = 0;
	int number = 5;

	if (r.width() > 1000)                                                                     // calculate the number of labels that fill a line
		number = 5;
	else if (r.width() > 800)
		number = 4;
	else if (r.width() >600)
		number = 3;
	else
		number = 2;
	int result_height_total = r.height() - (50 * 4 + 80 + 25 + 5 * 6);                        // calculate the height to contain results
	int w = (r.width() - 2*20 - 5 * (number - 1)) / number;                                   // calculate width of label kSearchResult
	int maxline = (r.height() - (50 * 4 + 80 + 25 + 5 * 5)) / (w + 5);                        // calculate max number of lines of results
	int h = w;                                                                                // height of label kSearchResult equals to width
	if (((result_height_total - h) % (h + 5) >= 0.75 * h)) {                                  // if the remaining space is too large
		maxline = maxline + 1;                                                                // max number of lines plus one
		h = result_height_total / maxline - 5;                                                // recalculate height of label kSearchResult
	}
	if (result_height_total < w+5) {                                                          // if the height to contain results is less than the initial height (w)
		h = result_height_total-1;                                                            // height of label minus one
		number = (r.width() - 35) / (w + 5);                                                  // recalculate the number of labels that fill a line
		maxline = 1;                                                                          // set maxline to 1
	}
	for (int i = 0; i < list_.size(); i++) {                                                  // for all the Widgets added in ResponsiveWindow.cpp
		QLayoutItem* o = list_.at(i);
		try {
			ResponsiveLabel* label = static_cast<ResponsiveLabel*>(o->widget());              // cast the widget to one of our responsive labels
			largeHJudge(label, number, r, w, h, maxline, result_number, result_line);         // call function to judge where to put labels in large horizontal screen
		}
		catch (bad_cast) {
			cout << "warning, unknown widget class in layout" << endl;                        // bad_case: cast failed on reference...
		}
	}
}

// judge where to put labels in a large horizontal layout
void ResponsiveLayout::largeHJudge(ResponsiveLabel* label, int number, const QRect& r, int w, int h, int maxline, int& result_number, int& result_line) {

	if (label == NULL)                                                                                      // null: cast failed on pointer
		cout << "warning, unknown widget class in layout" << endl;
	else if (label->text() ==kFavorite)                                                                     // line 1, 50 height
		label->setGeometry(r.width() - 20 - 90*4 - 15 + r.x(), 0 + r.y(), 90, 50);
	else if (label->text() == kShoppingBasket)
		label->setGeometry(r.width() - 20 - 90 + r.x(), 0 + r.y(), 90, 50);
	else if (label->text() == kSignIn)
		label->setGeometry(r.width() - 20 - 90*2 - 5 + r.x(), 0 + r.y(), 90, 50);
	else if (label->text() == kMessage)
		label->setGeometry(r.width() - 20 - 90*3 - 10 + r.x(), 0 + r.y(), 90, 50);
	else if (label->text() == kBackButton)
		label->setGeometry(20 + r.x(), 0 + r.y(), 60, 50);
	else if (label->text() == kHomeLink)
		label->setGeometry(20 + 60 + 5 + r.x(), 0 + r.y(), 90, 50);
	else if (label->text() == kNavTabs)
		label->setGeometry(20+5*2+60+90 + r.x(), 0 + r.y(), r.width() - 435-60-100-5-5 -5- 20+10*5, 50);
	else if (label->text() == kSearchOptions)                                                              // line 2, 50 height
		label->setGeometry(20 + r.x(), 50 + 5 + r.y(), 150, 50);
	else if (label->text() == kSearchText)
		label->setGeometry(20+5+150 + r.x(), 50 + 5 + r.y(), r.width() - 20*2-5*2-150-60-20, 50);
	else if (label->text() == kSearchButton)
		label->setGeometry(r.width() - 100 + r.x(), 50 + 5 + r.y(), 80, 50);
	else if (label->text() == kResultSorting)                                                              // line 3, 50 height
		label->setGeometry(20 + r.x(), 50 + 5 + 50 + 5 + r.y(), r.width() - 40, 50);
	else if (label->text() == kSearchResult) {                                                             // line 4-n, each h height
		result_line = result_number / number;
		if (result_number < maxline * number)                                                              // if not fill the page
			label->setGeometry(20 + (result_number % number) * (w + 5) + r.x(), 3 * (50+5) + result_line * (h + 5) + r.y(), w, h);
		else                                                                                               // if fill the page
			label->setGeometry(-1, -1, 0, 0);                              
		result_number++;
	}
	else if (label->text() == kAdvert)                                                                     // line 3 from bottom, 80 height
		label->setGeometry(20 + r.x(), r.height() - 50-80-5, r.width() - 40, 80);
	else if (label->text() == kSearchBackward && result_number > maxline * number)                         // line 2 from bottom, 25 height
		label->setGeometry(r.width() / 2 - 45 + r.x(), r.height() - 50 - 5 * 2 - 25 - 80 + r.y(), 40, 25); //if one page cannot contain all results, show searching backward button
	else if (label->text() == kSearchForward && result_number > maxline * number)
		label->setGeometry(r.width() / 2 + 5 + r.x(), r.height() - 50 - 5 * 2 - 25 - 80 + r.y(), 40, 25);  //if one page cannot contain all results, show searching forward button
	else if (label->text() == kFooter)                                                                     // last line, 50 height
		label->setGeometry(20 + r.x(), r.height() - 50 + r.y(), r.width()-40, 50);
	else                                                                                                   // otherwise: disappear label by moving out of bounds
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setMediumHGeometry(const QRect& r) {                                  // set geometry for medium horizontal layout

	QLayout::setGeometry(r);
	int result_number = 0;
	int result_line = 0;
	int advert_number = 0;
	int number = 5;

	if (r.width() > 1000)                                                                    // calculate the number of labels that fill a line
		number = 5;
	else if (r.width() > 800)
		number = 4;
	else if (r.width() > 600)
		number = 3;
	else
		number = 2;
	int w = (r.width() - 30 - 5 * (number - 1)) / number;                                      // calculate width of label kSearchResult
	int maxline = (r.height() - (45*3+40+25+5*4)) / (w + 5);                                   // calculate max number of lines of results
	int result_height_total = r.height() - (45 * 3+40 + 25 + 5*5);                             // calculate the height to contain results
	int h = w;                                                                                 // height of label kSearchResult equals to width
	if (((result_height_total - h) % (h + 5) >= 0.75 * h)) {                                   // if the remaining space is too large
		maxline = maxline + 1;                                                                 // max number of lines plus one
		h = result_height_total / maxline - 5;                                                 // recalculate height of label kSearchResult
	}
	if (result_height_total <= w+5) {                                                          // if the height to contain results is less than the initial height (w)
		h = result_height_total-1;                                                             // height of label minus one
		number = (r.width() - 25) / (w + 5);                                                   // recalculate the number of labels that fill a line
		maxline = 1;                                                                           // set max number of lines to one
	}
	for (int i = 0; i < list_.size(); i++) {                                                   // for all the Widgets added in ResponsiveWindow.cpp
		QLayoutItem* o = list_.at(i);
		try {
			ResponsiveLabel* label = static_cast<ResponsiveLabel*>(o->widget());              // cast the widget to one of our responsive labels
			mediumHJudge(label, number, r, w, h, maxline, result_number, result_line);        // call function to judge where to put labels in medium horizontal screen
		}
		catch (bad_cast) {
			cout << "warning, unknown widget class in layout" << endl;                        // bad_case: cast failed on reference...
		}
	}
}

// judge where to put labels in a medium horizontal layout
void ResponsiveLayout::mediumHJudge(ResponsiveLabel* label, int number, const QRect& r, int w, int h, int maxline, int& result_number, int& result_line) {

	if (label == NULL)                                                                                // null: cast failed on pointer
		cout << "warning, unknown widget class in layout" << endl;
	else if (label->text() == kShoppingBasket)                                                        // line 1, 45 height
		label->setGeometry(r.width() - 80 - 15 + r.x(), 0 + r.y(), 80, 45);                          
	else if (label->text() == kSignIn)
		label->setGeometry(r.width() - 80 * 2 - 15 - 5 + r.x(), 0 + r.y(), 80, 45);
	else if (label->text() == kBackButton)
		label->setGeometry(15 + r.x(), 0 + r.y(), 55, 45);
	else if (label->text() == kMessage)
		setMediumMessage(label, r);
	else if (label->text() == kFavorite)
		setMediumFavorite(label, r);
	else if (label->text() == kHomeLink)
		setMediumHomeLink(label, r);
	else if (label->text() == kNavTabs)
		setMediumNav(label, r);
	else if (label->text() == kSearchOptions)                                                         // line 2, 45 height
		label->setGeometry(15 + r.x(), 45 + 5 + r.y(), 120, 45);
	else if (label->text() == kSearchText)
		label->setGeometry(140 + r.x(), 45 + 5 + r.y(), r.width() - 220, 45);
	else if (label->text() == kSearchButton)
		label->setGeometry(r.width() - 75 + r.x(), 45 + 5 + r.y(), 60, 45);
	else if (label->text() == kResultSorting)                                                         // line 3, 45 height
		label->setGeometry(15 + r.x(), 45 * 2 + 5 * 2 + r.y(), r.width() - 30, 45);
	else if (label->text() == kSearchResult) {                                                        // line 4-n, each h height
		result_line = result_number / number;
		if (result_number < maxline * number)                                                         // if not fill the page
			label->setGeometry(15 + (result_number % number) * (w + 5) + r.x(), 120 + 10 * 3 + result_line * (h + 5) + r.y(), w, h);
		else                                                                                          // if fill the page
			label->setGeometry(-1, -1, 0, 0);
		result_number++;
	}
	else if (label->text() == kSearchBackward && result_number > maxline* number)                     // line 2 from bottom, 25 height
		label->setGeometry(r.width() / 2 - 45 + r.x(), r.height() - 40 - 25 - 5 + r.y(), 40, 25);     // if one page cannot contain all results, show searching backward button
	else if (label->text() == kSearchForward && result_number > maxline* number)
		label->setGeometry(r.width() / 2 + 5 + r.x(), r.height() - 40 - 25 - 5 + r.y(), 40, 25);      // if one page cannot contain all results, show searching forward button
	else if (label->text() == kFooter)                                                                // last line, 40 height
		label->setGeometry(15 + r.x(), r.height() - 40 + r.y(), r.width()-30, 40);
	else                                                                                              // otherwise: disappear label by moving out of bounds
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setMediumNav(ResponsiveLabel* label, const QRect& r) {                                             // set geometry of the navigation in the medium horizontal layout

	if (r.width() > 720)                                                                                                  // if kMessage, kFavorite and kHomeLink all show
		label->setGeometry(15 + 5 + 55 + 80 + 5 + r.x(), 0 + r.y(), r.width() - 6 * 5 - 80 * 5 - 55 - 15 * 2, 45);
	else if (r.width() > 550)                                                                                             // if kHomeLink shows, kMessage and kFavorite hide
		label->setGeometry(15 + 5 + 55 + 80 + 5 + r.x(), 0 + r.y(), r.width() - 4 * 5 - 80 * 3 - 55 - 15 * 2, 45);
	else                                                                                                                  // if kMessage, kFavorite and kHomeLink all hide
		label->setGeometry(15 + 5 + 55 + r.x(), 0 + r.y(), r.width() - 3 * 5 - 80 * 2 - 55 - 15 * 2, 45);
}

void ResponsiveLayout::setMediumMessage(ResponsiveLabel* label, const QRect& r) {                                         // set geometry of the message in the medium horizontal layout

	if (r.width() > 720)                                                                                                  // if width of window is long enough, show message
		label->setGeometry(r.width() - 15 - 5 * 2 - 80 * 3 + r.x(), 0 + r.y(), 80, 45);
	else                                                                                                                  // if width of window is not long enough, hide message
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setMediumFavorite(ResponsiveLabel* label, const QRect& r) {                                        // set geometry of the favorite in the medium horizontal layout

	if (r.width() > 720)                                                                                                  // if width of window is long enough, show favorite
		label->setGeometry(r.width() - 15 - 5 * 3 - 80 * 4 + r.x(), 0 + r.y(), 80, 45);
	else                                                                                                                  // if width of window is not long enough, hide favorite
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setMediumHomeLink(ResponsiveLabel* label, const QRect& r) {                                        // set geometry of the homelink in the medium horizontal layout

	if (r.width() > 550)                                                                                                  // if width of window is long enough, show homelink
		label->setGeometry(15 + 5 + 55 + r.x(), 0 + r.y(), 80, 45);
	else                                                                                                                  // if width of window is not long enough, hide homelink
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setSmallHGeometry(const QRect& r /* our layout should always fit inside r */) {      // set geometry for small horizontal layout

	QLayout::setGeometry(r);
	int result_number = 0;
	int result_line = 0;
	int advert_number = 0;
	int number = 5;
	if (r.width() > 1000)                                                                     // calculate the number of labels that fill a line
		number = 5;
	else if (r.width() > 800)
		number = 4;
	else if (r.width() > 600)
		number = 3;
	else
		number = 2;
	int w = (r.width() - 20 - 5 * (number - 1)) / number;                                      // calculate width of label kSearchResult
	int h = w;                                                                                 // height of label kSearchResult equals to width
	int maxline = (r.height() - (40*3+35+25+5*4)) / (w + 5);                                   // calculate max number of lines of results
	int result_height_total = r.height() - (40 * 3 + 35+25 + 5 * 5);                           // calculate the height to contain results
	if (result_height_total <= w+5) {                                                          // if the height to contain results is less than the initial height (w)
		h = result_height_total - 1;                                                           // height of label minus one
		number = (r.width() - 15) / (w + 5);                                                   // recalculate the number of labels that fill a line
		maxline = 1;                                                                           // set number of max line to one
		w = (r.width() - 2 * 10 - 5 * (number - 1)) / number;                                  // recalculate width of label kSearchResult
		if (w < 180 || h < 180) {                                                              // if width or height of label kSearchResult is less than 180
			if (r.width() < 400)                                                               // if width of window is short
				setSmallVGeometry(r);                                                          // set the layout as small vertical layout
			else                                                                               // if width of window is long
				setLargeVGeometry(r);                                                          // set the layout as large vertical layout
			return;
		}
	}
	for (int i = 0; i < list_.size(); i++) {                                                   // for all the Widgets added in ResponsiveWindow.cpp
		QLayoutItem* o = list_.at(i);
		try {
			ResponsiveLabel* label = static_cast<ResponsiveLabel*>(o->widget());               // cast the widget to one of our responsive labels
			smallHJudge(label, number, r, w, h, maxline, result_number, result_line);          // call function to judge where to put labels in small horizontal screen
		}
		catch (bad_cast) {
			cout << "warning, unknown widget class in layout" << endl;                         // bad_case: cast failed on reference...
		}
	}
}

// judge where to put labels in a small horizontal layout
void ResponsiveLayout::smallHJudge(ResponsiveLabel* label, int number, const QRect& r, int w, int h, int maxline, int& result_number, int& result_line) {

	if (label == NULL)                                                                              // null: cast failed on pointer
		cout << "warning, unknown widget class in layout" << endl;
	else if (label->text() == kShoppingBasket)                                                      // line 1, 40 height
		label->setGeometry(r.width() - 75 - 10 + r.x(), 0 + r.y(), 75, 40);
	else if (label->text() == kSignIn)
		label->setGeometry(r.width() - 75 * 2 - 10 - 5 + r.x(), 0 + r.y(), 75, 40);
	else if (label->text() == kBackButton)
		label->setGeometry(10 + r.x(), 0 + r.y(), 50, 40);
	else if (label->text() == kMessage)
		setSmallMessage(label, r);
	else if (label->text() == kFavorite)
		setSmallFavorite(label, r);
	else if (label->text() == kHomeLink)
		setSmallHomeLink(label, r);
	else if (label->text() == kNavTabs)
		setSmallNav(label, r);
	else if (label->text() == kSearchOptions)                                                       // line 2, 40 height
		label->setGeometry(10 + r.x(), 40 + 5 + r.y(), 120, 40);
	else if (label->text() == kSearchText)
		label->setGeometry(10 + 120 + 5 + r.x(), 40 + 5 + r.y(), r.width() - 10 * 2 - 55 - 5 * 2 - 120, 40);
	else if (label->text() == kSearchButton)
		label->setGeometry(r.width() - 65 + r.x(), 40 + 5 + r.y(), 55, 40);
	else if (label->text() == kResultSorting)                                                       // line 3, 40 height
		label->setGeometry(10 + r.x(), 40 * 2 + 5 * 2 + r.y(), r.width() - 20, 40);
	else if (label->text() == kSearchResult) {                                                      // line 4-n, each h height
		result_line = result_number / number;
		if (result_number < maxline * number)                                                       // if not fill the page
			label->setGeometry(10 + (result_number % number) * (w + 5) + r.x(), 120+15 + result_line * (h + 5) + r.y(), w, h);
		else                                                                                        // if fill the page
			label->setGeometry(-1, -1, 0, 0);
		result_number++;
	}
	else if (label->text() == kSearchBackward && result_number > maxline* number)                    // line 2 from bottom, 25 height
		label->setGeometry(r.width() / 2 - 40 + r.x(), r.height() - 35 - 25 - 5 + r.y(), 35, 25);    // if one page cannot contain all results, show searching backward button
	else if (label->text() == kSearchForward && result_number > maxline* number)              
		label->setGeometry(r.width() / 2 + 5 + r.x(), r.height() - 35 - 25 - 5 + r.y(), 35, 25);     // if one page cannot contain all results, show searching forward button
	else if (label->text() == kFooter)                                                               // last line, 35 height
		label->setGeometry(10 + r.x(), r.height() - 35 + r.y(), r.width() - 20, 35);
	else                                                                                             // otherwise: disappear label by moving out of bounds
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setSmallNav(ResponsiveLabel* label, const QRect& r) {                          // set geometry of the navigation in the small horizontal layout

	if (r.width() > 720)                                                                              // if kMessage, kFavorite and kHomeLink all show
		label->setGeometry(10 + 5 + 50 + 75 + 5 + r.x(), 0 + r.y(), r.width() - 6 * 5 - 75 * 5 - 50 - 10 * 2, 40);
	else if (r.width() > 550)                                                                         // if kHomeLink shows, kMessage and kFavorite hide
		label->setGeometry(10 + 5 + 50 + 75 + 5 + r.x(), 0 + r.y(), r.width() - 4 * 5 - 75 * 3 - 50 - 10 * 2, 40);
	else                                                                                              // if kMessage, kFavorite and kHomeLink all hide
		label->setGeometry(10 + 5 + 50 + r.x(), 0 + r.y(), r.width() - 3 * 5 - 75 * 2 - 50 - 10 * 2, 40);
}

void ResponsiveLayout::setSmallMessage(ResponsiveLabel* label, const QRect& r) {                      // set geometry of the message in the small horizontal layout

	if (r.width() > 720)                                                                              // if width of window is long enough, show message        
		label->setGeometry(r.width() - 10 - 5 * 2 - 75 * 3 + r.x(), 0 + r.y(), 75, 40);
	else                                                                                              // if width of window is not long enough, hide message
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setSmallFavorite(ResponsiveLabel* label, const QRect& r) {                     // set geometry of the favorite in the small horizontal layout

	if (r.width() > 720)                                                                              // if width of window is long enough, show favorite
		label->setGeometry(r.width() - 10 - 5 * 3 - 75 * 4 + r.x(), 0 + r.y(), 75, 40);  
	else                                                                                              // if width of window is not long enough, hide favorite
		label->setGeometry(-1, -1, 0, 0);
}

void ResponsiveLayout::setSmallHomeLink(ResponsiveLabel* label, const QRect& r) {                     // set geometry of the homelink in the small horizontal layout

	if (r.width() > 550)                                                                              // if width of window is long enough, show homelink
		label->setGeometry(10 + 5 + 50 + r.x(), 0 + r.y(), 75, 40);
	else                                                                                              // if width of window is not long enough, hide homelink
		label->setGeometry(-1, -1, 0, 0);
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
