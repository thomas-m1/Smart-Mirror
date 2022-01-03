#include "MainWindow.h"
#include "Clock.h"

#include <QApplication>
#include <QString>


int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setStyleSheet("background-color:black; color:white;");
	mainWindow.showMaximized();

	return app.exec();
}
