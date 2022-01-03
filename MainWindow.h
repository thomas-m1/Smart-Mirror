#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Clock.h"
#include "Weather.h"
#include "News.h"
#include "Commute.h"
#include "Calendar.h"
#include "Quote.h"
#include "timer.h"
#include "SearchBox.h"

#include <QMainWindow>
#include <QGridLayout>

/**
* @brief Header file for MainWindow
* @author All
*/

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

private slots:
	// void handleButton();

private:
	Clock *clockWidget;
	Weather *weatherWidget;
	News *newsWidget;
	Commute *commuteWidget;
	Timer *timerWidget;
	QGridLayout *mainLayout;
	QWidget *window;
	Calendar *calendarWidget;
	Quote *quoteWidget;
	SearchBox *searchWidget;

	// QPushButton *executeButton;
};
#endif // MAINWINDOW_H
