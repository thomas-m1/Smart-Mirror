#include "Commute.h"

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGridLayout>
#include <QEventLoop>
#include <QUrl>
#include <cmath>


Commute::Commute(QWidget *parent) : QLabel(parent) {
    QString key = "AoGjtJ9Feb2DFZtlMEW8bvy776S0VT4J-FKxUwGwbPadc2j9R814aNBrAMElfLtw";
    QString home[4] = {"ON", "N683E9", "London", "539%20Richmond%20Street"};
    QString work[4] = {"ON", "N6A3K7", "London", "1151%20Richmond%20Street"};
	QString homeURL = "http://dev.virtualearth.net/REST/v1/Locations/CA/" + home[0] + "/" + home[1] + "/" + home[2] + "/" + home[3] + "?key=" + key;
	QString workURL = "http://dev.virtualearth.net/REST/v1/Locations/CA/" + work[0] + "/" + work[1] + "/" + work[2] + "/" + work[3] + "?key=" + key;

    result = new QLabel("");

	setStyleSheet("font:bold 35px;");
    // Get the coordinates of the home address.
	manager = new QNetworkAccessManager(this);
    QEventLoop loop;
    request.setUrl(QUrl(homeURL));
    reply = manager->get(request);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    readCoord(reply);
  
  	// Get the coordinates of the work address
	request.setUrl(QUrl(workURL));
    reply = manager->get(request);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    readCoord(reply);

  	// Get the time to travel between them
    QString timeURL = "https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=" + vals.at(0) + "," + vals.at(1) + "&destinations=" + vals.at(2) + "," + vals.at(3) + "&travelMode=driving&key=" + key;
    request.setUrl(QUrl(timeURL));
    reply = manager->get(request);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    readTime(reply);
}

/**
* @brief Reads JSON response from API containing coordinates and store them
* @parameters reply - the reply from the API call
*/
void Commute::readCoord(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject obj = jsonResponse.object();
        QJsonArray arr = obj["resourceSets"].toArray().at(0).toObject()["resources"].toArray().at(0).toObject()["point"].toObject()["coordinates"].toArray(); // locate coords
        QString lat = QString::number(arr.at(0).toDouble());
        QString lon = QString::number(arr.at(1).toDouble());
        vals.push_back(lat); // store latitutde
        vals.push_back(lon); // store longitude
    } else {
        qDebug() << reply->errorString();
    }
    reply->deleteLater();
}

/**
* @brief Reads JSON response from API containing distance matrix and outputs it
* @parameters reply - the reply from the API call
*/
void Commute::readTime(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject obj = jsonResponse.object();
        int minutes = (int) obj["resourceSets"].toArray().at(0).toObject()["resources"].toArray().at(0).toObject()["results"].toArray().at(0).toObject()["travelDuration"].toDouble(); // read distance
        ++minutes; // add one for good measure
        QString ret = QString::number(minutes) + QString(" minutes to work.");
        result->setText(ret);
        setText(ret); // output result

    } else {
        qDebug() << reply->errorString();
    }
    reply->deleteLater();
}
