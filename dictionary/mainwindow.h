
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onSaveButtonClicked();
    void onLoadButtonClicked();
    void onSearchTextChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> PhoneBook;
    void updateBookList();
    void saveToFile();
    void loadFromFile();
    void filter(const QString &text);

};

#endif // MAINWINDOW_H
