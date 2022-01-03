//timer class. allows user to set a timer. smart mirror will alert user when timer is up 

#include "timer.h"
#include <QtDebug>
#include <QFile>
#include <time.h>
#include <iostream>


Timer::Timer(QWidget *parent) :QWidget(parent){

    setStyleSheet("font:bold 35px;");

   //initialize a precise timer
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);


    //setting up the layout
    titleLabel = new QLabel("TIMER",this);
    
    
    validateMin = new QIntValidator(0, 1000, this);
    validateSec = new QIntValidator(0, 59, this);
    minLabel = new QLabel("Min",this);
    colonLabel = new QLabel(":",this);
    secLabel = new QLabel("Sec",this);
    minutesInput = new QLineEdit("00",this);
    secondsInput = new QLineEdit("00",this);
    minutesInput->setValidator(validateMin);//validates the time
    secondsInput->setValidator(validateSec);
    button = new QPushButton("START",this);


    //adds to layout  
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);//main layout
    auto layoutTitle = new QHBoxLayout;
    layoutTitle -> setAlignment(Qt::AlignTop);
    layoutTitle -> addWidget(titleLabel,0,Qt::AlignCenter);
    auto layoutLabels = new QHBoxLayout;
    layoutLabels->setAlignment(Qt::AlignTop);
    layoutLabels -> addWidget(minLabel,0,Qt::AlignRight);
    layoutLabels -> addWidget(secLabel,0,Qt::AlignLeft);
    auto layoutInputs = new QHBoxLayout;
    layoutInputs->setAlignment(Qt::AlignTop);
    layoutInputs -> addWidget(minutesInput,0,Qt::AlignCenter);
    layoutInputs -> addWidget(colonLabel,0,Qt::AlignCenter);
    layoutInputs -> addWidget(secondsInput,0,Qt::AlignCenter);
    minutesInput->setAlignment(Qt::AlignRight);
    auto layoutButton = new QHBoxLayout;
    layoutButton->setAlignment(Qt::AlignTop);
    layoutButton -> addWidget(button,0,Qt::AlignCenter);

    vBoxLayout->addLayout(layoutTitle);
    vBoxLayout->addLayout(layoutLabels);
    vBoxLayout->addLayout(layoutInputs);
    vBoxLayout->addLayout(layoutButton);
    setLayout(vBoxLayout);

    this->setFixedSize(200,200);//size of display

    //sound
    timerSound = new QSoundEffect(this);
    timerSound->setSource(QUrl(QStringLiteral("qrc:/sound/alarm.wav")));
    timerSound->setLoopCount(5);

    connect(minutesInput, &QLineEdit::returnPressed, this, &Timer::startStopButton);
    connect(secondsInput, &QLineEdit::returnPressed, this, &Timer::startStopButton);
    connect(button, &QPushButton::clicked, this, &Timer::startStopButton);//command to take input when button is pushed
}

/**
* @brief Convert time to int and get total time in sec
*/
void Timer::getTime(int *minutes, int *seconds){
    int m = minutesInput->text().toInt();
    int s = secondsInput->text().toInt();
    int total = m *60 + s;//total time in sec
    *minutes = total /60;
    *seconds = total % 60;
}

/**
* @brief Makes display nice
*/
void Timer::setTime(int minutes, int seconds){
    QString sMinutes = "";
    QString sSeconds = "";
    //adds 0 in front
    if (minutes < 10){
        sMinutes += "0";
    }
    sMinutes += QString::number(minutes);
    if (seconds < 10) {
        sSeconds += "0";
    }
    sSeconds += QString::number(seconds);
    minutesInput->setText(sMinutes);
    secondsInput->setText(sSeconds);
}

/**
* @brief Resets timer to default
*/
void Timer::timerReset(){

    //reset button
    button->setText("START");
    button->setStyleSheet("color: white");


    minutesInput->setEnabled(true);
    secondsInput->setEnabled(true);
}


/**
* @brief Alert for when Timer is done
*/
void Timer::alertEffects(){
    
 
}

/**
* @brief Alert for when Timer is done
*/
void Timer::timerAlert(){
    int minutes, seconds, total;
    this->getTime(&minutes, &seconds);
    total = minutes*60 + seconds;//gets total seconds
    if(total > 0){// if the time has not hit 0 yet, subtract a second and set the time
        total --;
        minutes = total /60;
        seconds = total % 60;
        this->setTime(minutes,seconds);
    }
    if (total == 0) {//if the timer hit 0. stop the timer and respnd appropriatly
        timer->stop();
        disconnect(timer, SIGNAL(timeout()));
        button->setText("RESET");//set button value
        connect(timer, SIGNAL(timeout()),this, SLOT(alertEffects()));
        timer->start(7000);        
        timerSound->play();
    }
}

/**
* @brief Start and stop button for timer
*/
void Timer::startStopButton(){
    QString currentButton = button->text();
    if (!currentButton.compare("START")){
        int minutes, seconds;
        this->getTime(&minutes, &seconds);
        this->setTime(minutes, seconds);
        button->setText("STOP");
        button->setStyleSheet("color: #D2042D");
        connect(timer, SIGNAL(timeout()), this, SLOT(timerAlert()));
        timer->start(1000);
        minutesInput->setEnabled(false);
        secondsInput->setEnabled(false);
    }
    else if (!currentButton.compare("RESET") || !currentButton.compare("STOP")){
        timer->stop();
        disconnect(timer, SIGNAL(timeout()));        
        this->timerReset();
        if (!currentButton.compare("RESET")){
            timerSound->stop();
        }
    }
}
