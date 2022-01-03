#ifndef WEATHER_H
#define WEATHER_H

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

class Weather : public QLabel {
	Q_OBJECT

public:
	Weather(QWidget *parent = nullptr);
	void setLocation(const std::string &newLatitude, const std::string &newLongitude);

private slots:
	void getData();
	void readData(QNetworkReply *reply);

private:
	QNetworkAccessManager *manager;
	QNetworkRequest request;
	QString latitude;
	QString longitude;
};
#endif // WEATHER_H
