#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(ui->saveToFileFileButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(ui->loadFromFileButton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBookList() {
    ui->listWidget->clear();
    for(const auto& book : PhoneBook.keys()) {
        QString formattedBook = QString("%1 %2").arg(book).arg(PhoneBook.value(book));
        ui->listWidget->addItem(formattedBook);
    }
}


void MainWindow::onAddButtonClicked() {
    QString Name = QInputDialog::getText(this, tr("Add a contact"), tr("Enter the name:"));
    if(!Name.isEmpty()) {
        QString Number = QInputDialog::getText(this, tr("Add a contact"), tr("Enter the number:"));
        PhoneBook.insert(Name, Number);
        updateBookList();
    }
}

void MainWindow::onEditButtonClicked() {
    QListWidgetItem* selectedContact = ui->listWidget->currentItem();
    if(selectedContact) {
        QString currentName = selectedContact->text().section('"', 1, 1);
        QString newName = QInputDialog::getText(this, tr("Edit the contact"), tr("Enter the name:"), QLineEdit::Normal, currentName);
        if(!newName.isEmpty()) {
            QString newNumber = QInputDialog::getText(this, tr("Edit the contact"), tr("Enter the number:"), QLineEdit::Normal, PhoneBook.value(currentName));
            PhoneBook.remove(currentName);
            PhoneBook.insert(newName, newNumber);
            updateBookList();
        }
    }
}

void MainWindow::onDeleteButtonClicked() {
    QListWidgetItem* selectedBook = ui->listWidget->currentItem();
    if(selectedBook) {
        QString currentTitle = selectedBook->text().section('"', 1, 1);
        PhoneBook.remove(currentTitle);
        updateBookList();
    }
}

void MainWindow::onSaveButtonClicked() {
    saveToFile();
}

void MainWindow::onLoadButtonClicked() {
    loadFromFile();
}

void MainWindow::onSearchTextChanged(const QString &text) {
    filter(text);
}

void MainWindow::saveToFile() {
    QFile file("C:/Users/Zoryana/Documents/dictionary/contact.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for(const auto& book : PhoneBook.keys()) {
            out << book << " - " << PhoneBook.value(book) << "\n";
        }

        file.close();
    }

}

void MainWindow::loadFromFile() {
    QFile file("C:/Users/Zoryana/Documents/dictionary/contact.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        PhoneBook.clear();
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" - ");
            if (parts.size() == 2) {
                PhoneBook.insert(parts[0], parts[1]);
            }
        }

        file.close();
        updateBookList();
    }
}

void MainWindow::filter(const QString &text) {
    ui->listWidget->clear();
    if (text.isEmpty()) {
        updateBookList();
        return;
    }
    for (const auto& book : PhoneBook.keys()) {
        if (book.contains(text, Qt::CaseInsensitive) || PhoneBook.value(book).contains(text, Qt::CaseInsensitive)) {
            QString formattedBook = QString("\"%1\" %2").arg(book).arg(PhoneBook.value(book));
            ui->listWidget->addItem(formattedBook);
        }
    }
}

