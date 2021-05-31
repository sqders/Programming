#include "newtaskwindow.h"
#include "ui_newtaskwindow.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
NewTaskWindow::NewTaskWindow(QWidget * parent):
    QWidget(parent),
    ui(new Ui::NewTaskWindow)
{
    ui->setupUi(this);
    connect(ui->newTagPushButton,&QPushButton::clicked,this,&NewTaskWindow::newTagClicked);

    connect(ui->newTaskPushButton,&QPushButton::clicked,this,&NewTaskWindow::newTaskClicked);

    connect(ui->toMainWindowPushButton,&QPushButton::clicked,this,&NewTaskWindow::toMainWindow);
}

NewTaskWindow::~NewTaskWindow()
{
    delete ui;
}
void NewTaskWindow::newTagClicked()
{
        QString tagName=ui->newTagLineEdit->text();
        int tagColorInt=ui->tagColorComboBox->currentIndex();
        QColor tagColor;
        switch (tagColorInt) {
            case 0:
                tagColor=Qt::white;
            break;
            case 1:
                tagColor=Qt::black;
            break;
            case 2:
                tagColor=Qt::red;
            break;
            case 3:
                tagColor=Qt::darkRed;
            break;
            case 4:
                tagColor=Qt::green;
            break;
            case 5:
                tagColor=Qt::darkGreen;
            break;
            case 6:
                tagColor=Qt::blue;
            break;
            case 7:
                tagColor=Qt::darkBlue;
            break;
            case 8:
                tagColor=Qt::cyan;
            break;
            case 9:
                tagColor=Qt::darkCyan;
            break;
            case 10:
                tagColor=Qt::magenta;
            break;
            case 11:
                tagColor=Qt::darkMagenta;
            break;
            case 12:
                tagColor=Qt::yellow;
            break;
            case 13:
                tagColor=Qt::darkYellow;
            break;
            case 14:
                tagColor=Qt::gray;
            break;
            case 15:
            tagColor=Qt::darkGray;
            break;
            case 16:
            tagColor=Qt::lightGray;
            break;
            default:
            break;
        }
        emit newTagSignal(tagColor,tagName);
}

void NewTaskWindow::setTags(QJsonObject jsonObject)
{
    tags=jsonObject.value("tasks").toObject();
    ui->taskTagComboBox->clear();
    QJsonObject tagsObject = tags.value("tags").toObject();
    QStringList keyList=tagsObject.keys();
    for (int i=0;i<tagsObject.length() ;i++ )
        ui->taskTagComboBox->addItem(keyList[i]);
    ui->newTagLineEdit->clear();


}

void NewTaskWindow::newTaskClicked(){
    QString taskText=ui->taskLineEdit->text(),
            tagName=ui->taskTagComboBox->currentText();
    QDateTime taskDate=ui->taskDateTimeEdit->dateTime();
    QJsonObject taskObject;
    taskObject["text"]=taskText;
    taskObject["date"]=taskDate.toString();
    ui->taskLineEdit->clear();
    emit newTaskSignal(taskObject,tagName);

}
void NewTaskWindow::toMainWindow(){
    this->close();
    emit mainWindowSignal();
}

void NewTaskWindow::setTaskText(QString recieveText){ui->taskLineEdit->setText(recieveText);}

void NewTaskWindow::setTagText(QString recieveText){ui->taskTagComboBox->setCurrentText(recieveText);}

void NewTaskWindow::setTaskDate(QDateTime recieveDate){ui->taskDateTimeEdit->setDateTime(recieveDate);}
