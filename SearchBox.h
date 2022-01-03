#ifndef SEARCHBOX_H
#define SEARCHBOX_H
#include <QLineEdit>
#include <QDesktopServices>
#include <QString>
#include <QStringLiteral>
#include <QUrl>
#include <QWidget>


class SearchBox : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBox(QWidget *parent = nullptr);

protected slots:
    void doSearch();

private:
    QLineEdit *search;

};
#endif
