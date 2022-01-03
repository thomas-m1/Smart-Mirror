#include "Weather.h"

#include <QTimer>
#include <QByteArray>
#include <QUrl>
#include <cmath>


Weather::Weather(QWidget *parent) : QLabel(parent) {

	//initialize latitude, longitude values (by default London, ON)
	latitude = "42.9836";
	longitude = "-81.2453";

	// build the url to access api. 
	QString url = "https://api.openweathermap.org/data/2.5/onecall?lat=&lon=&exclude=minutely,hourly,daily,alerts&units=metric&appid=2b59b3afb9a06a61800f6fa23e0ee5e7";
	url.insert(57, longitude);
	url.insert(52, latitude);
	request.setUrl(QUrl(url));

	setStyleSheet("font:bold 35px;");

	// timer acts to periodically refresh forecast so weather information stays current
	// timeout signal from timer going off is connected to getData method, which calls the api for current weather info
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Weather::getData);
	
	// manager emitting signal:finished means that the api reply has arrived so we can now extract the data
	manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &Weather::readData);

	
	timer->start(3600000); // timer to refresh weather info goes off every hour
	getData(); // initialize the weather info. without this line, we would need to wait for timeout to get weather info upon launching the program

}

/**
* @brief Gets data from API
*/
void Weather::getData() {
	manager->get(request);
}

/**
* @brief Parses JSON response from API to find temperature and description
*/
void Weather::readData(QNetworkReply *reply) {
	if (reply->error()) {
		// do something
		// qDebug() << reply->errorString();
	} else {
		QString data = reply->readAll();
		qDebug() << data;

		// extract temperature
		int tempStartIndex = data.indexOf("temp") + 6;
		int tempEndIndex = data.indexOf("feels") - 2;
		int temp = round(data.mid(tempStartIndex, tempEndIndex - tempStartIndex).toDouble());

		// extract description of weather condition
		int descriptionStartIndex = data.indexOf("description") + 14;
		int descriptionEndIndex = data.indexOf("\"", descriptionStartIndex);
		QString description = data.mid(descriptionStartIndex, descriptionEndIndex - descriptionStartIndex);

		// capitalize the first letter of each word in description
		description[0] = description[0].toUpper();
		
		for(int i = 0; i < description.size(); i++) {
			if(description[i].unicode() == ' ')
				description[i + 1] = description[i + 1].toUpper();
		}

		// build string that will display temperature and weather description. \u2103 is degrees celcius
		QString result = QString::number(temp) + QString("\u2103") + QChar('\n') + description;
		
		setText(result);
	}

	reply->deleteLater();
}

/**
* @brief Changes weather location to one specified
*/
void Weather::setLocation(const std::string &newLatitude, const std::string &newLongitude) {
	latitude = QString::fromStdString(newLatitude);
	longitude = QString::fromStdString(newLongitude);

	QString url = "https://api.openweathermap.org/data/2.5/onecall?lat=&lon=&exclude=minutely,hourly,daily,alerts&units=metric&appid=2b59b3afb9a06a61800f6fa23e0ee5e7";
	url.insert(57, longitude);
	url.insert(52, latitude);
	request.setUrl(QUrl(url));
}
