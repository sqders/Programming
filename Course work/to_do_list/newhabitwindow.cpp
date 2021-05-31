#include "newhabitwindow.h"
#include "ui_newhabitwindow.h"
NewHabitWindow::NewHabitWindow(QWidget *parent ):
    QWidget(parent),
    ui(new Ui::NewHabitWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&NewHabitWindow::newHabitBtnClicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&NewHabitWindow::toMainWindowBtn);

}

NewHabitWindow::~NewHabitWindow()
{
    delete ui;
}

void newHabitSignal(QJsonObject){}

void NewHabitWindow::newHabitBtnClicked(){
    QJsonObject habitObj;
    habitObj["name"]=ui->lineEdit->text();
    habitObj["strike"]=ui->spinBox->value();
    habitObj["periodicity"]=ui->comboBox->currentText();
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->spinBox->setValue(0);
emit newHabitSignal(habitObj);

}
void NewHabitWindow::setValue(int strike, QString name, QString periodicity){
    ui->lineEdit->setText(name);
    ui->spinBox->setValue(strike);
    ui->comboBox->setEditText(periodicity);
}

void NewHabitWindow::toMainWindowBtn(){
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->spinBox->setValue(0);
    emit toMainWindowSignal();
}
