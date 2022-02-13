#include "registrwindow.h"
#include "ui_registrwindow.h"

RegistrWindow::RegistrWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::RegistrWindow)
{
    ui->setupUi(this);
    connect(ui->registerPushButton,&QPushButton::clicked,this,&RegistrWindow::registerBtnClicked);
    connect(ui->loginPushButton,&QPushButton::clicked,this,&RegistrWindow::loginBtnClicked);
}
RegistrWindow::~RegistrWindow()
{
    delete ui;
}

void RegistrWindow::loginBtnClicked(){
      emit loginBtnSignal(ui->loginLineEdit->text(),ui->passwordLineEdit->text());
}
void RegistrWindow::registerBtnClicked(){
      emit registerBtnSignal(ui->loginLineEdit->text(),ui->passwordLineEdit->text());
}
void RegistrWindow::setLable(QString new_lable){
    if(new_lable=="this username is already exist"){
        ui->label_2->setText("Пароль:(Такой логин уже существует)");
    }else if(new_lable=="dont find login or password"){
        ui->label_2->setText("Пароль:(Неверный пароль или логин)");
    }
}
void RegistrWindow::clearWindow()
{
    ui->label_2->setText("Пароль:");
    ui->passwordLineEdit->clear();
    ui->loginLineEdit->clear();
}
