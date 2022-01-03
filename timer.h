#ifndef Timer_H
#define Timer_H

#include <QTimer>
#include <QLineEdit>
#include <QIntValidator>
#include <QSoundEffect>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QUrl>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QFrame>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>


/**
* @brief Header file for Timer
* @author Thomas Michalski
*/
class Timer : public QWidget{
    Q_OBJECT

    public:
        Timer(QWidget *parent = nullptr);


    private slots:

        void startStopButton();
        void timerAlert();
        void alertEffects();
        void getTime(int *minutes, int *seconds);
        void setTime(int minutes, int seconds);
        void timerReset();


    private:
        // Ui::Timer *ui;
        QTimer *timer;
        QIntValidator *validateMin,*validateSec;
        QLabel *titleLabel, *minLabel, *secLabel, *colonLabel;
        QLineEdit *minutesInput;
        QLineEdit *secondsInput;
        QPushButton *button;
        QSoundEffect *timerSound;
        int colorIdx;   
        QColor initialBackgroundColor, initialButtonColor;
};

#endif // Timer_H
