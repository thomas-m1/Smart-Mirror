#include "MainWindow.h"
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

	// create layouts

	window = new QWidget(this);
	mainLayout = new QGridLayout(window);

	window->setLayout(mainLayout);
	setCentralWidget(window);

	// initialize widgets
	clockWidget = new Clock();
	weatherWidget = new Weather();
	newsWidget = new News();
	commuteWidget = new Commute();
	calendarWidget = new Calendar();
	quoteWidget = new Quote();
	searchWidget = new SearchBox();
	timerWidget = new Timer();

	// add widgets to layouts
	mainLayout->addWidget(clockWidget, 0,0, Qt::AlignLeft);
	mainLayout->addWidget(weatherWidget, 1,0, Qt::AlignLeft);
	mainLayout->addWidget(newsWidget, 3, 0, Qt::AlignLeft);
	mainLayout->addWidget(commuteWidget, 2,0, Qt::AlignLeft);
	mainLayout->addWidget(calendarWidget, 2,3 ,Qt::AlignRight);
	mainLayout->addWidget(quoteWidget, 3, 3, Qt::AlignRight);
	mainLayout->addWidget(searchWidget, 1,3, Qt::AlignRight);
	mainLayout->addWidget(timerWidget, 0,3, Qt::AlignRight);
	QLabel *l1 = new QLabel("",this);
	QLabel *l2 = new QLabel("",this);
	mainLayout->addWidget(l1, 0,1, Qt::AlignLeft);
	mainLayout->addWidget(l2, 0,2, Qt::AlignRight);
}
