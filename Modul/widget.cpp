#include "widget.h"
#include "ui_widget.h"
#include <QTabBar>
#include "stylehelper.h"
#include <QStyleOption>
#include <QDebug>
#include <QFontDatabase>
#include <QGridLayout>
#include <time.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    configurationTabWidget();
    addFonts();
    setInterfaceStyle();
    configurationGameAreaButtons();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::onComputerSlot);
    srand(time(0));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
void Widget::setInterfaceStyle()
{
    this->setStyleSheet(StyleHelper::getMainWidgetStyle());
    ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->aboutButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonActiveStyle());
    ui->rightButton->setStyleSheet(StyleHelper::getRightButtonStyle());
    ui->tabWidget->setStyleSheet(StyleHelper::getTabWidgetStyle());
    ui->tab->setStyleSheet(StyleHelper::getTabStyle());

    ui->messageLabel->setStyleSheet(StyleHelper::getVictoryMessageStyle());
    ui->messageLabel->setText("Хід хрестиків");

    setGameAreaButtonsStyle();
    ui->messageLabel->setText("");
    ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessageStyle());
    ui->aboutTextLabel->setStyleSheet(StyleHelper::getAboutTextStyle());
}


void Widget::changeButtonStatus(int num)
{
    if(num ==1){
        ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonActiveStyle());
        ui->rightButton->setStyleSheet(StyleHelper::getRightButtonStyle());
    }else{
        ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonStyle());
        ui->rightButton->setStyleSheet(StyleHelper::getRightButtonActiveStyle());
    }
}

void Widget::on_leftButton_clicked()
{
    changeButtonStatus(1);
    player = 'X';
}
void Widget::on_rightButton_clicked()
{
    changeButtonStatus(2);
    player = '0';
}

void Widget::configurationTabWidget()
{
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setMaximumHeight(320);
    ui->tabWidget->setCurrentIndex(0);
}

void Widget::addFonts()
{
    QFontDatabase::addApplicationFont(":/Roboto-Medium.ttf");
    int id=QFontDatabase::addApplicationFont(":/Roboto-MediumItalic.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    //qDebug() << family;
}

void Widget::changeButtonStyle(int row, int colum, QString style)
{
    QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
    QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(row, colum)->widget());
    btn->setStyleSheet(style);
}

void Widget::configurationGameAreaButtons()
{
    QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
    for(int row=0; row<3; row++){
        for(int column=0; column<3; column++){
            QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(row, column)->widget());
            btn->setProperty("row", row);
            btn->setProperty("column", column);
            connect(btn, &QPushButton::clicked, this, &Widget::onGameAreaButtonClicked);
        }
    }
}
void Widget::setGameAreaButtonsStyle()
{
    QString style = StyleHelper::getBlankButtonStyle();
    for(int row=0; row<3; row++){
        for(int column=0; column<3; column++){
            changeButtonStyle(row, column, style);
        }
    }
}

void Widget::start()
{
    setGameAreaButtonsStyle();
    for (int r=0;r<3;r++ ) {
        for(int c=0;c<3;c++){
            gameArea[r][c] = '-';
        }
    }
    progress = 0;
    gameStart = true;
    stop = false;
    if(player!='X')
        computerInGame();
}

void Widget::lockPlayer()
{
    if(player == 'X'){
        playerLocked = false;
    }else{
        playerLocked = true;
    }
}
void Widget::on_startButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    if(gameStart){
        playerLocked = true;
        ui->startButton->setText("Грати");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
        ui->leftButton->setDisabled(false);
        ui->rightButton->setDisabled(false);
        gameStart = false;
        ui->messageLabel->setText("Поразка");
        ui->messageLabel->setStyleSheet(StyleHelper::getLostMessageStyle());
    }else{
        ui->messageLabel->setText("Поїхали!");
        ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessageStyle());
        start();
        lockPlayer();
        ui->startButton->setText("Здаюсь");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonGameStyle());
        ui->leftButton->setDisabled(true);
        ui->rightButton->setDisabled(true);

    }
}
void Widget::computerInGame()
{
    if (stop)
        return;

    // Ініціалізація генератора випадкових чисел тільки один раз
    static bool srandInitialized = false;
    if (!srandInitialized) {
          srand(time(0));
          srandInitialized = true;
    }

    int listSize = 4;
    int index = rand() % listSize;

    QStringList list = {"Мій хід", "Так так так...", "Хм.. Важко..", "Дайте подумати"};

     //Перевірка коректності індексу перед використанням
    if (index >= 0 && index < listSize) {
        ui->messageLabel->setText(list.at(index));
    }

    timer->start(200);
}

void Widget::onGameAreaButtonClicked()
{
    if(!playerLocked){
        QPushButton *btn = qobject_cast<QPushButton*>(sender());
        int row = btn->property("row").toInt();
        int column = btn->property("column").toInt();
        QString style;
        if(player == 'X'){
            style = StyleHelper::getCrossNormalStyle();
            gameArea[row][column] = 'X';
        }else{
            style = StyleHelper::getZeroNormalStyle();
            gameArea[row][column] = '0';
        }
        changeButtonStyle(row, column, style);
        playerLocked = true;
        progress++;
        chekGameStop();
        endGame();
        computerInGame();
    }
}
void Widget::chekGameStop()
{
    winner = '-';
    QString style;
    char symbols[2] = {'X','0'};
    for(int i=0;i<2;i++){
        for (int row=0;row<3;row++ ) {
            if((gameArea[row][0]==symbols[i])and(gameArea[row][1]==symbols[i])and(gameArea[row][2]==symbols[i])){
                stop = true;
                winner = symbols[i];
                if(winner==player){
                    if(player == 'X'){
                        style=StyleHelper::getCrossVictoryStyle();
                    }else{
                        style=StyleHelper::getZeroVictoryStyle();
                    }
                }else{
                    if(player == 'X'){
                        style=StyleHelper::getZeroLostStyle();
                    }else{
                        style=StyleHelper::getCrossLostStyle();
                    }
                }
                changeButtonStyle(row,0,style);
                changeButtonStyle(row,1,style);
                changeButtonStyle(row,2,style);
                break;
            }
        }
        for (int col=0;col<3;col++ ) {
            if((gameArea[0][col]==symbols[i])and(gameArea[1][col]==symbols[i])and(gameArea[2][col]==symbols[i])){
                stop = true;
                winner = symbols[i];
                if(winner==player){
                    if(player == 'X'){
                        style=StyleHelper::getCrossVictoryStyle();
                    }
                    else{
                        style=StyleHelper::getZeroVictoryStyle();
                    }
                }
                else{
                    if(player == 'X'){
                        style=StyleHelper::getZeroLostStyle();
                    }
                    else{
                        style=StyleHelper::getCrossLostStyle();
                    }
                }
                changeButtonStyle(0,col,style);
                changeButtonStyle(1,col,style);
                changeButtonStyle(2,col,style);
                return;
            }
        }
        if((gameArea[0][0]==symbols[i])and(gameArea[1][1]==symbols[i])and(gameArea[2][2]==symbols[i])){
            stop = true;
            winner = symbols[i];
            if(winner==player){
                if(player == 'X'){
                    style=StyleHelper::getCrossVictoryStyle();
                }else{
                    style=StyleHelper::getZeroVictoryStyle();
                }
            }else{
                if(player == 'X'){
                    style=StyleHelper::getZeroLostStyle();
                }else{
                    style=StyleHelper::getCrossLostStyle();
                }
            }
            changeButtonStyle(0,0,style);
            changeButtonStyle(1,1,style);
            changeButtonStyle(2,2,style);
            return;
        }
        if((gameArea[0][2]==symbols[i])and(gameArea[1][1]==symbols[i])and(gameArea[2][0]==symbols[i])){
            stop = true;
            winner = symbols[i];
            if(winner==player){
                if(player == 'X'){
                    style=StyleHelper::getCrossVictoryStyle();
                }else{
                    style=StyleHelper::getZeroVictoryStyle();
                }
            }else{
                if(player == 'X'){
                    style=StyleHelper::getZeroLostStyle();
                }else{
                    style=StyleHelper::getCrossLostStyle();
                }
            }
            changeButtonStyle(0,2,style);
            changeButtonStyle(1,1,style);
            changeButtonStyle(2,0,style);
            return;
        }

    }
    if(progress==9){
        stop = true;
    }

}

void Widget::endGame()
{
    if(stop){
        if(winner == player){
            ui->messageLabel->setText("Перемога!");
            ui->messageLabel->setStyleSheet(StyleHelper::getVictoryMessageStyle());
        }else if(winner=='-'){
            ui->messageLabel->setText("нічия!");
        }else{
            ui->messageLabel->setText("Поразка");
            ui->messageLabel->setStyleSheet(StyleHelper::getLostMessageStyle());
        }
        playerLocked = true;
        ui->startButton->setText("Грати");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
        ui->leftButton->setDisabled(false);
        ui->rightButton->setDisabled(false);
        gameStart = false;
    }
}

void Widget::onComputerSlot()
{

    char comp;
    QString style;
    if(player == 'X'){
        comp = '0';
        style = StyleHelper::getZeroNormalStyle();
    }else{
        comp = 'X';
        style = StyleHelper::getCrossNormalStyle();
    }
    timer->stop();
    while(true){
        int row = rand()%3;
        int column = rand()%3;
        if(gameArea[row][column]=='-'){
            gameArea[row][column] = comp;
            changeButtonStyle(row, column, style);
            ui->messageLabel->setText("Ваш хід!");
            progress++;
            chekGameStop();
            endGame();
            playerLocked = false;
            return;
        }
    }

}

void Widget::on_aboutButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


