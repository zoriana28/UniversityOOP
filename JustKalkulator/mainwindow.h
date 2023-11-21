#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend bool operator==(MainWindow& obj1, MainWindow& obj2);
    friend bool operator<(MainWindow& obj1, MainWindow& obj2);
    friend bool operator>(MainWindow& obj1, MainWindow& obj2);
    friend MainWindow operator*(MainWindow& object1, MainWindow& object2);
    friend MainWindow operator+(MainWindow& obj1, MainWindow& obj2);
    friend MainWindow operator-( MainWindow& obj1, MainWindow& obj2);
    friend MainWindow operator/(MainWindow& obj1, MainWindow& obj2);

private:
    Ui::MainWindow *ui;
    QString s1;

private slots:
    void digit_numbers();
    void operations();
    void math_operations();
    void on_pushButton_clear_clicked();
    void on_pushButton_equal_clicked();

};
#endif // MAINWINDOW_H
