#include "News.h"

#include <QTimer>
#include <QByteArray>
#include <QUrl>
#include <cmath>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>


News::News(QWidget *parent) : QLabel(parent)
{
    // returns news sorted by popularity from apple news and the news api
	QString url = "https://newsapi.org/v2/everything?q=Apple&from=2021-11-09&sortBy=popularity&apiKey=fbefbe2b79b6458c8770fa13133d8da1";
	request.setUrl(QUrl(url));

	setStyleSheet("font:bold 35px;");
    // set a timer to continue refershing the news and returning new data
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &News::getData);
	// connect the manager with the read data function to parse through the data and retrive the required fields
	manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &News::readData);

	
	timer->start(3600000); 
	getData(); 
}

/**
* @brief Requests the data
*/
void News::getData(){
    manager->get(request);
}

/**
* @brief Reads JSON response and finds title, author, and description
*/
void News::readData(QNetworkReply *reply){
    if(reply->error()){
        // do something
    } else {

        QByteArray data = reply->readAll();
        QJsonDocument jsonResp = QJsonDocument::fromJson(data);
        QJsonObject obj = jsonResp.object();
        obj = obj["articles"].toArray().at(0).toObject();
        QString author = obj["author"].toString();
        QString title = obj["title"].toString();
        QString desc = obj["description"].toString();
        QString result = title + QString(": ") + author + QString("\n") + desc;
        setText(result);
        setWordWrap(true);
    }

    reply->deleteLater();
}
