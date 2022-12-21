#ifndef RESPONSIVEWINDOW_H
#define RESPONSIVEWINDOW_H

#include <QWidget>

using namespace std;

class ResponsiveWindow: public QWidget {

public:
    ResponsiveWindow();
	void setScrollarea(QWidget* qw, int n);

protected:
    void createWidgets();
};


#endif //RESPONSIVEWINDOW_H
