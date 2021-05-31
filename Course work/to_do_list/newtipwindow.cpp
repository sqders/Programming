#include "newtipwindow.h"
#include "ui_newtipwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
NewTipWindow::NewTipWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewTipWindow)
{
    ui->setupUi(this);
    connect(ui->backBtn,&QPushButton::clicked,this,&NewTipWindow::toMainWindow);
    connect(ui->saveBtn,&QPushButton::clicked,this,&NewTipWindow::saveTip);
}
NewTipWindow::~NewTipWindow()
{
    delete ui;
}

void NewTipWindow::toMainWindow()
{
    this->close();      // Закрываем окно
    ui->namelineEdit->clear();
    ui->contentPlainTextEdit->clear();
    emit mainWindowSignal(); // И вызываем сигнал на открытие главного окна
}

void NewTipWindow::saveTip()
{
    titl=ui->namelineEdit->text();
    cont=ui->contentPlainTextEdit->toPlainText();
    emit sendNewTip(ui->namelineEdit->text(),ui->contentPlainTextEdit->toPlainText());
}
void sendNewTip(QString title,QString content){};

void NewTipWindow::setTitle(QString title){
    ui->namelineEdit->setText(title);
}
void NewTipWindow::setContent(QString content){
    ui->contentPlainTextEdit->setPlainText(content);
}
