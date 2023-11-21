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

private:
    Ui::MainWindow *ui;
private slots:
    void digit_numbers();
    //void math_operations();
    //void system_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_system16_clicked();
    void on_pushButton_system2_clicked();
    void on_pushButton_system8_clicked();
    void on_pushButton_system2_to_10_clicked();
    void on_pushButton_16_to_10_clicked();
    void on_pushButton_system8_to_10_clicked();
    void on_pushButton_point_clicked();
    void on_pushButton_last_clear_clicked();
};
#endif // MAINWINDOW_H
