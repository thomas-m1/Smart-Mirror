#include "SearchBox.h"
#include <QLabel>
#include <QHBoxLayout>


SearchBox::SearchBox(QWidget *parent) : QWidget(parent)
{    

    setStyleSheet("font:bold 35px;");

  	// adds title and search bar in verticle box layout
    QHBoxLayout *HBoxLayout = new QHBoxLayout(this);//main layout
    search = new QLineEdit(this);
    QLabel * title = new QLabel("SEARCH", this);
    HBoxLayout -> addWidget(title,0,Qt::AlignLeft);   
    search->setStyleSheet("background-color: #FFFFFF; font: #000000; color: #000000");

    HBoxLayout -> addWidget(search,0,Qt::AlignLeft);    
    setLayout(HBoxLayout);

	// call doSearch method on 'Enter'
    connect(search, SIGNAL(returnPressed()), this, SLOT(doSearch()));

    adjustSize();
    resize(400, height());
    setFocus();
}

/**
* @brief Opens browser window and searches user input on Google
*/
void SearchBox::doSearch()
{
    const QString googleUrl(QStringLiteral("http://google.com/search?q=%1"));
    QString url = googleUrl.arg(search->text());
    QDesktopServices::openUrl(QUrl(url));
}
