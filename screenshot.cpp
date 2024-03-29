#include "screenshot.h"
#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <fstream>
#include <QApplication>

// assessment class. do not edit.
void Screenshot::doScreenshot() {

    auto active_window = QApplication::activeWindow();

    // screen shot currently sized window
    if (active_window) {
        QPixmap pixmap(active_window->size());
        active_window->render(&pixmap);

        QSize &size = remaining.back();

        string s = "./report/images/rendered" +  to_string ( size.width() ) + "x" + to_string ( size.height() ) +".png";
        QFile file( QString::fromStdString(s));

        file.open(QIODevice::WriteOnly);
        pixmap.save(&file, "PNG");
    }
    remaining.pop_back();
    schedule();
}

// when we are shown for the first time, set the screenshot sizes and call the scheduler
void Screenshot::showEvent(QShowEvent *) {

#if defined _MSC_VER
    _mkdir("./report");
    _mkdir("./report/images");
#elif defined __GNUC__
	mkdir("./report", S_IRWXU);
	mkdir("./report/images", S_IRWXU);
#endif

    remaining.push_back(QSize(300,300));

    remaining.push_back(QSize(568,320));
    remaining.push_back(QSize(320,568));

    remaining.push_back(QSize(812,375));
    remaining.push_back(QSize(375,812));

    remaining.push_back(QSize(1024,1366));
    remaining.push_back(QSize(1366,1024));

    remaining.push_back(QSize(1920,1050));
    remaining.push_back(QSize(1200,1050));
    remaining.push_back(QSize(700 ,1050));
    remaining.push_back(QSize(500 ,1050));

    remaining.push_back(QSize(1920,300));
    remaining.push_back(QSize(1920,800));

    ofstream html;
    html.open("./report/index.html", fstream::in | fstream::out | fstream::app);

    html << "<html><body><h4>responsive layouts:</h4>" << endl;

    for (QSize size : remaining)
        html << "<p><img width = \"300px\" src=\"" << "images/rendered" +  to_string ( size.width() ) + "x" + to_string ( size.height() ) +".png\"/><br/>" << size.width() << "x" << size.height() << "</p>" <<endl ;

    html << "</body></html>" << endl;

    html.close();

    schedule();
}

// schedule the next sized screenshot from the remaining list.
void Screenshot::schedule() {
    if (remaining.size() == 0) {
        QApplication::quit();
        return;
    }

    QSize &size = remaining.back();
    resize(size);

    mTimer = new QTimer(NULL);
    mTimer->setSingleShot(true);
    mTimer->setInterval(200);
    mTimer->start();

    connect( mTimer, SIGNAL (timeout()), SLOT ( doScreenshot() ) );
}

