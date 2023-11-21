#include "mainwindow.h"
#include "ui_mainwindow.h"

double num_first;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_pm, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_root, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_power, SIGNAL(clicked()), this, SLOT(math_operations()));
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_root->setCheckable(true);
    ui->pushButton_power->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::digit_numbers(){
    QPushButton *buttons=(QPushButton *)sender();
    double all_numbers;
    QString new_label;
    all_numbers=(ui->label_result->text()+buttons->text()).toDouble();
    new_label=QString::number(all_numbers, 'g', 15);

    ui->label_result->setText(new_label);

}
void MainWindow::operations(){
    QPushButton *buttons=(QPushButton *)sender();
    double all_numbers;
    QString new_label;

    if(buttons->text()=="+/-"){
        all_numbers=(ui->label_result->text()).toDouble();
        all_numbers=all_numbers * (-1);
    new_label=QString::number(all_numbers, 'g', 15);

    ui->label_result->setText(new_label);
    }
}
void MainWindow::math_operations()
{
    QPushButton *buttons=(QPushButton *)sender();
    num_first=ui->label_result->text().toDouble();
    ui->label_result->setText(" ");
    buttons->setChecked(true);

}
bool operator==(MainWindow& obj1, MainWindow& obj2){
    if (obj1.s1.length() != obj2.s1.length())
    return false;
    else
    {
    for (int i = 0; i < obj1.s1.length(); i++) {
        if (obj1.s1[i] == obj2.s1[i])
            continue;
        else
            return false;
    }
    return true;
    }
}
bool operator<(MainWindow& obj1, MainWindow& obj2)
{
    while (obj1.s1[0]=='0') {
    obj1.s1.remove(0, 1);
    }
    while (obj2.s1[0] == '0') {
    obj2.s1.remove(0, 1);
    }
    if (obj1.s1.length() < obj2.s1.length())
    return true;
    else if (obj1.s1.length() > obj2.s1.length())
    return false;
    else if (obj1.s1.length() == obj2.s1.length()) {
    for (int i = 0; i < obj1.s1.length(); i++) {
        if (obj1.s1[i] == obj2.s1[i])
            continue;
        else if (obj1.s1[i] > obj2.s1[i])
            return false;
        else if (obj1.s1[i] < obj2.s1[i])
            return true;
    }
    }
}
bool operator>(MainWindow& obj1, MainWindow& obj2)
{
    while (obj1.s1[0] == '0') {
    obj1.s1.remove(0, 1);
    }
    while (obj2.s1[0] == '0') {
    obj2.s1.remove(0, 1);
    }
    if (obj1.s1.length() > obj2.s1.length())
    return true;
    else if (obj1.s1.length() < obj2.s1.length())
    return false;
    else if (obj1.s1.length() == obj2.s1.length()) {
    for (int i = 0; i < obj1.s1.length(); i++) {
        if (obj1.s1[i] == obj2.s1[i])
            continue;
        else if (obj1.s1[i] < obj2.s1[i])
            return false;
        else if (obj1.s1[i] > obj2.s1[i])
            return true;
    }
    }
}
VeryLong operator+(VeryLong& obj1, VeryLong& obj2)
{
    VeryLong results;
    results.s1.clear();
    int carry = 0;
    int g = 0;
    bool minus = false;
    if (obj1.s1[0] == '-' && obj2.s1[0] == '-') {
    minus = true;
    obj2.s1.erase(0, 1);
    obj1.s1.erase(0, 1);
    }
    if (obj1.s1[0] == '-') {
    obj1.s1.erase(0, 1);
    //swap(obj1.s1, obj2.s1);
    results=obj2 - obj1;
    return results;
    }
    if (obj2.s1[0] == '-') {
    obj2.s1.erase(0, 1);
    results = obj1 - obj2;
    return results;
    }

    if (obj1.s1.length() < obj2.s1.length())
    swap(obj1.s1, obj2.s1);
    if (obj1.s1.length() > obj2.s1.length()) {
    while (obj1.s1.length() != obj2.s1.length())
        obj2.s1.insert(0, QString("0"));

    }
    for (int i = obj1.s1.length() - 1; i >= 0; i--)
    {
    int digit1 = obj1.s1[i] - '0';
    int digit2 = obj2.s1[i] - '0';
    int digit = digit1 + digit2 + carry;
    if (digit >= 10) {
        g = digit % 10;
        carry = digit / 10;
    }
    else {
        g = digit;
        carry = 0;
    }
    results.s1.append(to_string(g));
    }
    if (carry)
    results.s1.append(to_string(carry));
    reverse(results.s1.begin(), results.s1.end());
    if (minus == true)
    results.s1.insert(0, QString("-"));
    return results;
}
MainWindow operator-(MainWindow& obj1, MainWindow& obj2)
{
    MainWindow result;
    int carry = 0;
    int maxlength;
    result.s1.clear();
    bool minus = false;
    if (obj1.s1[0] == '-'&& obj2.s1[0] == '-') {
    obj2.s1.remove(0, 1);
    obj1.s1.remove(0, 1);
    swap(obj1.s1, obj2.s1);
    }
    else if (obj1.s1[0] == '-') {
    obj1.s1.remove(0, 1);
    result = obj1 + obj2;
    result.s1.insert(0, QString("-"));
    return result;
    }
    else if (obj2.s1[0] == '-') {
    obj2.s1.remove(0, 1);
    result = obj1 + obj2;
    return result;
    }
    if (obj1 < obj2)
    {
    swap(obj1.s1, obj2.s1);
    minus = true;
    }
    if (obj1.s1.length() > obj2.s1.length())
    maxlength = obj1.s1.length();
    else
    maxlength = obj2.s1.length();
    int digit1, digit2;
    for (int i = 0; i < maxlength; i++) {
    if (i < obj1.s1.length())
        digit1 = obj1.s1[obj1.s1.length() - 1 - i] - '0';
    else
        digit1 = 0;
    if (i < obj2.s1.length())
        digit2 = obj2.s1[obj2.s1.length() - 1 - i] - '0';
    else
        digit2 = 0;
    int diff = digit1 - digit2 - carry;
    if (diff < 0) {
        diff += 10;
        carry = 1;
    }
    else {
        carry = 0;
    }

    result.s1 += to_string(diff);
    }
    reverse(result.s1.begin(), result.s1.end());
    while (result.s1[0] == '0') {
    result.s1.remove(0, 1);
    }
    if(minus==true)
    result.s1.insert(0, QString("-"));
    obj1.s1 = result.s1;
    return MainWindow (result);
}
MainWindow operator*(MainWindow& object1, MainWindow& object2)
{
    if (object1.s1 < object2.s1)
    swap(object1.s1, object2.s1);
    bool minus = false;
    if (object1.s1.length() < object2.s1.length())
    swap(object1.s1, object2.s1);
    if (object1.s1[0] == '-' && object2.s1[0] == '-') {
    object1.s1.remove(0, 1);
    object2.s1.remove(0, 1);
    minus = false;
    }
    else if (object1.s1[0] == '-')
    {
    object1.s1.remove(0, 1);
    minus = true;
    }
    else if (object2.s1[0] == '-')
    {
    object2.s1.remove(0, 1);
    minus = true;
    }
    MainWindow result;
    result.s1.clear();
    int carry = 0;
    MainWindow transitive;
    transitive.s1.clear();
    for (int i = object2.s1.length() - 1; i >= 0; i--)
    {
    for (int j = object1.s1.length() - 1; j >= 0; j--)
    {
        int digit1 = object2.s1[i] - '0';
        int digit2 = object1.s1[j] - '0';
        int digit = (digit1 * digit2) + carry;
        int g;
        if (digit >= 10)
        {
            g = digit % 10;
            carry = digit / 10;
        }
        else
        {
            g = digit;
            carry = 0;
        }
        transitive.s1.append(to_string(g));
    }
    reverse(transitive.s1.begin(), transitive.s1.end());
    if (carry > 0)
    {
        transitive.s1.insert(transitive.s1.begin(), char(carry + '0'));
    }
    for (int k = 0; k < object2.s1.length() -1  - i; k++) {
        transitive.s1 = transitive.s1 + '0';

    }
    result = result + transitive;
    transitive.s1.clear();
    }
    if (minus==true) {
    result.s1.insert(0, QString("-"));
    }
    return MainWindow(result);
}
MainWindow operator/(MainWindow& obj1, MainWindow& obj2)
{
    MainWindow result;
    result.s1.clear();
    bool minus = false;
    if (obj1.s1[0] == '-' && obj2.s1[0] == '-') {
    minus = false;
    obj1.s1.remove(0, 1);
    obj2.s1.remove(0, 1);
    }
    else if (obj1.s1[0] == '-') {
    minus = true;
    obj1.s1.remove(0, 1);
    }
    else if (obj2.s1[0] == '-') {
    minus = true;
    obj2.s1.remove(0, 1);
    }
    int k = 0;
    while (obj2 < obj1)
    {
    obj1 - obj2;
    ++k;
    }
    int n = 0;
    QString c;
    for (int i = 0; i < 4; i++) {
    obj1.s1 += '0';
    while (obj2 < obj1)
    {
        obj1 - obj2;
        n++;
    }
    c += to_string(n);
    n = 0;
    }
    result.s1 = to_string(k)+','+ c;
    if (minus == true)
    result.s1.insert(0, QString("-"));
    return MainWindow(result);
}
void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_plus->setChecked(false);
     ui->pushButton_power->setChecked(false);
     ui->pushButton_root->setChecked(false);
    ui->label_result->setText("0");
}


void MainWindow::on_pushButton_equal_clicked()
{
    double label_number=1, num_second;
    QString new_label;
    num_second=ui->label_result->text().toDouble();
    if(ui->pushButton_plus->isChecked()){
    label_number=num_first+num_second;
    new_label=QString::number(label_number, 'g', 15);
    ui->label_result->setText(new_label);
    ui->pushButton_plus->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked()){
    label_number=num_first-num_second;
    new_label=QString::number(label_number, 'g', 15);
    ui->label_result->setText(new_label);
    ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked()){
    label_number=num_first*num_second;
    new_label=QString::number(label_number, 'g', 15);
    ui->label_result->setText(new_label);
    ui->pushButton_multiply->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked()){
    label_number=num_first/num_second;
    if(num_second==0){
        ui->label_result->setText("no");
    }
    else{
    new_label=QString::number(label_number, 'g', 15);
        ui->label_result->setText(new_label);}
    ui->pushButton_divide->setChecked(false);
    }
    else if(ui->pushButton_root->isChecked()){
    label_number=sqrt(num_first);
    new_label=QString::number(label_number, 'g', 15);
    ui->label_result->setText(new_label);
    ui->pushButton_root->setChecked(false);
    }
    else if(ui->pushButton_power->isChecked()){
    for(int i=0; i<num_second; i++){
        label_number*=num_first;
    }
    new_label=QString::number(label_number, 'g', 15);
    ui->label_result->setText(new_label);
    ui->pushButton_power->setChecked(false);
    }
}

