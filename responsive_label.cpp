#include <QFrame>
#include "responsive_label.h"

ResponsiveLabel::ResponsiveLabel(QString name, QWidget* qwidget) : ResponsiveLabel(name, kColours.at(name), qwidget) {
}

ResponsiveLabel::ResponsiveLabel(QString name, QString colour, QWidget* qwidget) : QLabel() {
    setText(name);

    // create a darker shade of the given colour for the border
    QColor qc (colour);
    qc = qc.darker(150);

    // make a nice looking label for the layout
    setStyleSheet("border: 1px solid "+ qc.name() +"; border-radius: 4px; background-color : "+colour+"; color : black;");
    setAlignment(Qt::AlignCenter);
}

ResponsiveLabel::ResponsiveLabel(QString name) : ResponsiveLabel(name, kColours.at(name)) {
}

ResponsiveLabel::ResponsiveLabel(QString name, QString colour) : QLabel() {
	setText(name);

	// create a darker shade of the given colour for the border
	QColor qc(colour);
	qc = qc.darker(150);

	// make a nice looking label for the layout
	setStyleSheet("border: 1px solid " + qc.name() + "; border-radius: 4px; background-color : " + colour + "; color : black;");
	setAlignment(Qt::AlignCenter);
}