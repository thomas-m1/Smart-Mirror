#ifndef COMMUTE_H
#define COMMUTE_H

#include <QMainWindow>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>


class Commute : public QLabel {
    Q_OBJECT
    public:
        Commute(QWidget *parent = nullptr);
    private slots:
        void readCoord(QNetworkReply *reply);
        void readTime(QNetworkReply *reply);
    private:
        QNetworkAccessManager *manager;
        QNetworkReply *reply;
        QNetworkRequest request;
        QLabel *result;
        std::vector<QString> vals;
};

#endif
