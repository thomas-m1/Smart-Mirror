#include "Clock.h"

#include <QTime>
#include <QTimer>
#include <QHBoxLayout>


Clock::Clock(QWidget *parent) : QWidget(parent) {
	format = 12; //12-hour format
	clock = new QLabel("", this);
	button = new QPushButton("", this);
	QHBoxLayout *layout = new QHBoxLayout();

	clock->setStyleSheet("font:bold 50px;");
	button->setMaximumSize(120, 75);
  	// changes between 12 and 24 hour formats
	connect(button, &QPushButton::clicked, this, &Clock::changeFormat);

	layout->addWidget(clock);
	layout->addWidget(button);
	setLayout(layout);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Clock::showTime);
	timer->start(1000);

	showTime();
}

/**
* @brief Displays time based on selected format
*/
void Clock::showTime() {
	QTime time = QTime::currentTime();
	QString clockText;
	QString buttonText;
	
  	// checks selected format and displays
	switch(format) {
		case 12:
			clockText = time.toString("hh:mm AP");
			buttonText = "Show 24H-Time";
			break;
		case 24:
			clockText = time.toString("hh:mm");
			buttonText = "Show 12H-Time";
			break;
	}

	clock->setText(clockText);
	button->setText(buttonText);
}

/**
* @brief Switches between formats
*/
void Clock::changeFormat() {
  	// switches format
	switch(format) {
		case 12:
			format = 24;
			break;
		case 24:
			format = 12;
			break;
	}

	showTime();
}
