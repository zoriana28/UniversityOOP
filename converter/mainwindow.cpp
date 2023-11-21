#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextStream"
#include "QString"

double num_first;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_A, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_B, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_D, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_E, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_F, SIGNAL(clicked()), this, SLOT(digit_numbers()));

    ui->pushButton_system2->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::digit_numbers(){
    QPushButton *buttons = qobject_cast<QPushButton*>(sender());
    QString current_text = ui->label_result->text();
    if (current_text == "0") {
        current_text = buttons->text();
    }
    else {
        current_text += buttons->text();
    }
    if(current_text.contains('9')||current_text.contains('8')){
        ui->pushButton_system2_to_10->setEnabled(false);
        ui->pushButton_system8_to_10->setEnabled(false);
    }
    if(current_text.contains('2')||current_text.contains('3')||current_text.contains('4')||current_text.contains('5')||current_text.contains('6')||current_text.contains('7')){
        ui->pushButton_system2_to_10->setEnabled(false);
        //ui->pushButton_system2_to_10->setChecked(true);
    }
    if(current_text.contains('A')||current_text.contains('B')||current_text.contains('C')||current_text.contains('D')||current_text.contains('E')||current_text.contains('F')){
        ui->pushButton_system2_to_10->setEnabled(false);
        ui->pushButton_system8_to_10->setEnabled(false);
        ui->pushButton_system2->setEnabled(false);
        ui->pushButton_system8->setEnabled(false);
        ui->pushButton_system16->setEnabled(false);
    }
    ui->label_result->setText(current_text);
}

void MainWindow::on_pushButton_point_clicked()
{
    if(!(ui->label_result->text().contains('.')))
        ui->label_result->setText(ui->label_result->text()+'.');
}
void MainWindow::on_pushButton_10_clicked()
{
    ui->pushButton_system16->setChecked(false);
    ui->pushButton_system2->setChecked(false);
    ui->pushButton_system8->setChecked(false);
    ui->pushButton_system2_to_10->setEnabled(true);
    ui->pushButton_system8_to_10->setEnabled(true);
    //ui->pushButton_system_16_to_10->setEnabled(true);
    ui->pushButton_system2->setEnabled(true);
    ui->pushButton_system8->setEnabled(true);
    ui->pushButton_system16->setEnabled(true);
    ui->label_result->setText("0");

}
void MainWindow::on_pushButton_system2_clicked()
{
    QPushButton *buttons = qobject_cast<QPushButton*>(sender());
    num_first=ui->label_result->text().toDouble();
    buttons->setChecked(true);
    bool lower = false;
    if (num_first < 0)
        lower = true;
    num_first = fabs(num_first);
    int intPart = static_cast<int>(num_first);
    double Part = num_first - intPart;
    QString new_label;
    int result = 0, k = 1;
    while (intPart)
    {
        result += (intPart % 2) * k;
        k *= 10;
        intPart /= 2;
    }
    if(QString::number(num_first).contains('.')){
    int precision=6;
    QString PartStr = "";
    while (precision--) {
        Part *= 2;
        int bit = static_cast<int>(Part);
        PartStr += QString::number(bit);
        Part -= bit;
    }
    new_label=QString::number(result);
    new_label = new_label + "." + PartStr;
    }
    else
     new_label=QString::number(result);
    if (lower){
        new_label.prepend("-");
    }
    ui->label_result->setText(new_label);
    ui->pushButton_system2->setChecked(false);

}
void MainWindow::on_pushButton_system16_clicked()
{
    QPushButton *buttons=(QPushButton *)sender();
    num_first=ui->label_result->text().toDouble();
    buttons->setChecked(true);
    QString result=" ", revers = " ";
    bool lower = false;
    int r=0;
    if (num_first < 0)
        lower = true;
    while (num_first > 1)
    {
        if ((int)num_first % 16 >= 10)
        {
            result += char((int)num_first % 16+55);
        }
        else
        {
            r = (int)num_first % 16;
            result = result+ QString::number(r, 16);

        }
        num_first /= 16;
    }
    if (num_first == 1)
        result += "1";
    for (int i = result.size() - 1; i >= 0; i--)
    {
        revers += result[i];
    }

    if (lower)
        revers.prepend("-");
    ui->label_result->setText(revers);
    ui->pushButton_system16->setChecked(false);
}
void MainWindow::on_pushButton_system8_clicked()
{
    QPushButton *buttons=(QPushButton *)sender();
    num_first=ui->label_result->text().toDouble();
    buttons->setChecked(true);
    int result = 0, k = 1;
    bool lower = false;
    if (num_first < 0)lower = true;
    num_first = fabs(num_first);
    while (num_first)
    {
        result += ((int)num_first % 8) * k;
        k *= 10;
        num_first /= 8;
    }
    if (lower)
        result = result * -1;
    QString new_label;
    new_label=QString::number(result);
    ui->label_result->setText(new_label);
    ui->pushButton_system8->setChecked(false);
}

void MainWindow::on_pushButton_system2_to_10_clicked()
{
    QPushButton *buttons=(QPushButton *)sender();
    QString num=ui->label_result->text();
    buttons->setChecked(true);
    bool lower_0 = false;
    float result = 0;

    if (num[0] == '-')
    {
        lower_0 = true;
        num.remove(0, 1);
    }
    for (int i = 0; i < num.length(); i++)
    {
        result += (num[i].digitValue()) * pow(2, num.length() - i - 1);

    }
    if (lower_0)
        result *= -1;
    QString new_label;
    new_label=QString::number(result);
    ui->label_result->setText(new_label);
    ui->pushButton_system2_to_10->setChecked(false);
}


void MainWindow::on_pushButton_16_to_10_clicked()
{
    QPushButton *buttons=(QPushButton *)sender();
    QString num=ui->label_result->text();
    buttons->setChecked(true);
    bool lower_0 = false;
    float result = 0;

    if (num[0] == '-')
    {
        lower_0 = true;
        num.remove(0, 1);
    }

    for (int i = 0; i < num.length(); i++)
    {
        QChar currentChar = num[i].toUpper();
        int currentDigit = currentChar.isDigit() ? currentChar.digitValue() : currentChar.toLatin1() - 'A' + 10;
        result += currentDigit * std::pow(16, num.length() - i - 1);
    }
    if (lower_0)
        result *= -1;
    QString new_label;
    new_label=QString::number(result);
    ui->label_result->setText(new_label);
    ui->pushButton_16_to_10->setChecked(false);
}


void MainWindow::on_pushButton_system8_to_10_clicked()
{
    QPushButton *buttons=(QPushButton *)sender();
    QString num=ui->label_result->text();
    buttons->setChecked(true);
    bool lower_0 = false;
    float result = 0;

    if (num[0] == '-')
    {
        lower_0 = true;
        num.remove(0, 1);
    }

    for (int i = 0; i < num.length(); i++)
    {
        result += (num[i].digitValue()) * pow(8, num.length() - i - 1);
    }
    if (lower_0)
        result *= -1;
    QString new_label;
    new_label=QString::number(result);
    ui->label_result->setText(new_label);
    ui->pushButton_system8_to_10->setChecked(false);
}

void MainWindow::on_pushButton_last_clear_clicked()
{
    QString current_text=ui->label_result->text().removeLast();
    ui->label_result->setText(current_text);
    ui->pushButton_system2_to_10->setEnabled(true);
    ui->pushButton_system8_to_10->setEnabled(true);
    ui->pushButton_system2->setEnabled(true);
    ui->pushButton_system8->setEnabled(true);
    ui->pushButton_system16->setEnabled(true);
    if(current_text.contains('9')||current_text.contains('8')){
        ui->pushButton_system2_to_10->setEnabled(false);
        ui->pushButton_system8_to_10->setEnabled(false);
    }
    if(current_text.contains('2')||current_text.contains('3')||current_text.contains('4')||current_text.contains('5')||current_text.contains('6')||current_text.contains('7')){
        ui->pushButton_system2_to_10->setEnabled(false);
        //ui->pushButton_system2_to_10->setChecked(true);
    }
    if(current_text.contains('A')||current_text.contains('B')||current_text.contains('C')||current_text.contains('D')||current_text.contains('E')||current_text.contains('F')){
        ui->pushButton_system2_to_10->setEnabled(false);
        ui->pushButton_system8_to_10->setEnabled(false);
        ui->pushButton_system2->setEnabled(false);
        ui->pushButton_system8->setEnabled(false);
        ui->pushButton_system16->setEnabled(false);
    }
    ui->pushButton_last_clear->setChecked(false);
}

