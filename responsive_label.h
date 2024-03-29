#ifndef RESPONSIVELABEL_H
#define RESPONSIVELABEL_H


#include <QLabel>
#include <QString>
#include <map>

using namespace std;

// label names that are displayed
const QString
        kHomeLink       = "home",
        kBackButton     = "back",
        kShoppingBasket = "basket",
        kSignIn         = "sign-in",
        kNavTabs        = "navigation tabs",
        kFooter         = "fat footer",
        kAdvert         = "advert",
        kSearchButton   = "search",
        kSearchResult   = "result",
        kSearchText     = "search query",
        kSearchForward  = ">",
        kSearchBackward = "<",
        kSearchOptions  = "search options",
		kFavorite = "favorite",
		kMessage = "messages",
		kResultSorting = "restult sorting",
        kBlank = " ";

// every label name has a colour
const map<QString, QString> kColours = {
        make_pair(kHomeLink,       "#ffaaff"),
        make_pair(kBackButton,     "#ffffaa"),
        make_pair(kShoppingBasket, "#ffaaaa"),
        make_pair(kSignIn,         "#aaffaa"),
        make_pair(kNavTabs,        "#ffa9d3"),
        make_pair(kFooter,         "#66ffaa"),
        make_pair(kAdvert,         "#ffaa66"),
        make_pair(kSearchButton,   "#aaffff"),
        make_pair(kSearchResult,   "#99ddff"),
        make_pair(kSearchText,     "#aaaaff"),
        make_pair(kSearchForward,  "#5caeff"),
        make_pair(kSearchBackward, "#5caeff"),
        make_pair(kSearchOptions,  "#9dceff"),
		make_pair(kFavorite,  "#fac775"),
		make_pair(kMessage, "#8acbe9"),
		make_pair(kResultSorting,  "#b6e98a"),
		make_pair(kBlank, "#ffffff")
    };

class ResponsiveLabel : public QLabel {
public:
    ResponsiveLabel(QString name, QWidget* widget) ;
    ResponsiveLabel(QString name, QString colour, QWidget* widget) ;
	ResponsiveLabel(QString name);
	ResponsiveLabel(QString name, QString colour);
};


#endif // RESPONSIVELABEL_H
