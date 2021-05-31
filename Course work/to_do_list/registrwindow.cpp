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

}
void RegistrWindow::registerBtnClicked(){

}
