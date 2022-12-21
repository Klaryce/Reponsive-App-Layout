#ifndef RESPONSIVELAYOUT_H
#define RESPONSIVELAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include "responsive_label.h"

class ResponsiveLayout : public QLayout
{
public:
    ResponsiveLayout(): QLayout() {}
	ResponsiveLayout(QWidget* qWidget) : QLayout() {};
    ~ResponsiveLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);
	void setSmallVGeometry(const QRect& rect);
	void setLargeVGeometry(const QRect& rect);
	void setSmallHGeometry(const QRect& rect);
	void setLargeHGeometry(const QRect& rect);
	void setMediumHGeometry(const QRect& rect);

	void largeHJudge(ResponsiveLabel* label, int number, const QRect& r, int w, int h, int maxline, int& result_number, int& result_line);
	void mediumHJudge(ResponsiveLabel* label, int number, const QRect& r, int w, int h, int maxline, int& result_number, int& result_line);
	void smallHJudge(ResponsiveLabel* label, int number, const QRect& r, int w, int h, int maxline, int& result_number, int& result_line);
	void smallVJudge(ResponsiveLabel* label, const QRect& r, int maxline, int& result_number);
	void largeVJudge(ResponsiveLabel* label, const QRect& r, int maxline, int& result_number);
	void setMediumNav(ResponsiveLabel* label, const QRect& r);
	void setMediumMessage(ResponsiveLabel* label, const QRect& r);
	void setMediumFavorite(ResponsiveLabel* label, const QRect& r);
	void setMediumHomeLink(ResponsiveLabel* label, const QRect& r);
	void setSmallNav(ResponsiveLabel* label, const QRect& r);
	void setSmallMessage(ResponsiveLabel* label, const QRect& r);
	void setSmallFavorite(ResponsiveLabel* label, const QRect& r);
	void setSmallHomeLink(ResponsiveLabel* label, const QRect& r);
	void setLargeVNav(ResponsiveLabel* label, const QRect& r);
	void setLargeVMessage(ResponsiveLabel* label, const QRect& r);
	void setLargeVFavorite(ResponsiveLabel* label, const QRect& r);
	void setLargeVHomeLink(ResponsiveLabel* label, const QRect& r);

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);

private:
    QList<QLayoutItem*> list_;
};
#endif // RESPONSIVELAYOUT_H
