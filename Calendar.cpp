#include "Calendar.h"

#include <QTextCharFormat>


Calendar::Calendar(QWidget *parent) : QCalendarWidget(parent) {

	this->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
	this->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	this->setDateEditEnabled(false);
	// this->setNavigationBarVisible(false);
	// this->setSelectionMode(QCalendarWidget::NoSelection);

	// make a QTextCharFormat object that will be used to
	// format our calendar header which shows days of the week
	// we set the background black, font colour (foreground) white, and weight=75 (bold text)
	QTextCharFormat headerFormat;
	headerFormat.setForeground(QBrush(QColor(255, 255, 255)));
	headerFormat.setBackground(QBrush(QColor(0, 0, 0)));
	headerFormat.setFontWeight(75);

	// apply formatting
	this->setHeaderTextFormat(headerFormat);
	this->setWeekdayTextFormat(Qt::Saturday, headerFormat);
	this->setWeekdayTextFormat(Qt::Sunday, headerFormat);

	this->setStyleSheet("selection-background-color:black"); // set selection colour to black so that its invisible (same colour as background)
}


// overload paintCell method of the QCalendarWidget class to have conditional formatting of calendar days
void Calendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const {

	// paint cells for past dates light gray
	if (date < QDate::currentDate()) {
		painter->save();
		painter->setPen(QColor(200, 200, 200));
		painter->drawText(rect, Qt::TextSingleLine | Qt::AlignCenter, QString::number(date.day()));
		painter->restore();
	}

	// paints cells for current and future dates white
	else {
		painter->save();
		painter->setPen(QColor(255, 255, 255));
		painter->drawText(rect, Qt::TextSingleLine | Qt::AlignCenter, QString::number(date.day()));
		painter->restore();
	}
}
