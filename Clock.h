#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>


class Clock : public QWidget {
	Q_OBJECT

public:
	Clock(QWidget *parent = nullptr);

private slots:
	void showTime();
	void changeFormat();

private:
	int format;
	QLabel *clock;
	QPushButton *button;
};
#endif // CLOCK_H
