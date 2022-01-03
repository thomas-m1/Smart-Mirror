#ifndef NEWS_H
#define NEWS_H

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>


class News : public QLabel
{
    Q_OBJECT
public:
    News(QWidget *parent = nullptr);
private slots:
    void getData();
    void readData(QNetworkReply *reply);
// setting the private QTNetwork Fields for use in the News.cpp file
private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString title;
    QString date;
};
#endif
