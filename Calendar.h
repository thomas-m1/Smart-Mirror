#ifndef CALENDAR_H
#define CALENDAR_H

#include <QCalendarWidget>
#include <QPainter>
#include <QRect>
#include <QDate>


class Calendar : public QCalendarWidget {
	Q_OBJECT

public:
	Calendar(QWidget *parent = nullptr);

protected:
	void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override;
};
#endif // CALENDAR_H
