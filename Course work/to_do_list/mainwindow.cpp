#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newtipwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QList>
#include <QBrush>
#include <QColor>
#include <QLCDNumber>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::read_Json();
    MainWindow::show_tip();
    MainWindow::show_habits();
    tipWindow=new NewTipWindow();
    taskWindow=new NewTaskWindow();
    habitWindow=new NewHabitWindow();
    registrWindow=new RegistrWindow();
    connect(ui->action_4,&QAction::triggered,this,&MainWindow::loginMenuBtn);
    connect(ui->action_5,&QAction::triggered,this,&MainWindow::logoutMenuBtn);
   // connect(registrWindow,SIGNAL(logiBtnSignal(QString,QString)),this,SLOT());
    ui->action_2->setEnabled(0);
    ui->action_3->setEnabled(0);
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&MainWindow::currentTabChanged);
    ui->tabWidget->setCurrentIndex(0);

    connect(tipWindow,&NewTipWindow::mainWindowSignal,this,&MainWindow::show_tip);
    connect(ui->new_tip_btn,&QPushButton::clicked,this,&MainWindow::new_tip_clicked);
    connect(tipWindow,SIGNAL(sendNewTip(QString,QString)),this,SLOT(receiveNewTip(QString,QString)));

    connect(taskWindow,&NewTaskWindow::mainWindowSignal,this,&MainWindow::show_tasks);
    connect(taskWindow,SIGNAL(newTagSignal(QColor,QString)),this,SLOT(saveNewTag(QColor,QString)));
    connect(ui->newTaskPushButton,&QPushButton::clicked,this,&MainWindow::newTaskButtonTriggered);
    connect(taskWindow,SIGNAL(newTaskSignal(QJsonObject,QString)),this,SLOT(saveNewTask(QJsonObject,QString)));
    connect(ui->searchPushButton,&QPushButton::clicked,this,&MainWindow::show_tasks);

    connect(ui->new_habit_btn,&QPushButton::clicked,this,&MainWindow::newHabitBtnClicked);
    connect(habitWindow,SIGNAL(newHabitSignal(QJsonObject)),this,SLOT(saveNewHabit(QJsonObject)));
    connect(habitWindow,&NewHabitWindow::toMainWindowSignal,this,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_tip_clicked()
{
    tipWindow->show();
    this->close();
}

void MainWindow::read_Json(){
    QString string_json;
    QFile file("save.json");
    if(!file.open(QIODevice::ReadOnly)){qDebug()<<"Json не открылся(";}
    string_json=file.readAll();
    file.close();
    QJsonDocument d=QJsonDocument::fromJson(string_json.toUtf8());
    this->m_currentJsonObject=d.object();
}

void MainWindow::save_Json(){
    QFileInfo fileInfo("save.json");
    QDir::setCurrent(fileInfo.path());
    QFile jsonFile("save.json");
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Файл не записывается";
    }
    jsonFile.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    jsonFile.close();
}

void MainWindow::receiveNewTip(QString title,QString content){
QJsonObject tipObject;
tipObject["title"]=title;
tipObject["content"]=content;
QJsonArray tipArray=m_currentJsonObject["tips"].toArray();
tipArray.append(tipObject);
m_currentJsonObject["tips"]=tipArray;
    MainWindow::save_Json();
}

void MainWindow::show_tip(){
    ui->table_tip->setRowCount(m_currentJsonObject.value("tips").toArray().size());

    for(int i=0;i<m_currentJsonObject.value("tips").toArray().size();i++)
    {
        QTableWidgetItem *itm_1=new QTableWidgetItem
        (m_currentJsonObject.value("tips").toArray().at(i).toObject().value("title").toString()),
        *itm_2=new QTableWidgetItem
         (m_currentJsonObject.value("tips").toArray().at(i).toObject().value("content").toString());
        ui->table_tip->setItem(i,0,itm_1);
        ui->table_tip->setItem(i,1,itm_2);
    }
    MainWindow::show();
}

void MainWindow::on_table_tip_itemSelectionChanged()
{
    ui->action_2->setEnabled(1);
    ui->action_3->setEnabled(1);
}

void MainWindow::on_tree_of_work_itemSelectionChanged()
{
    ui->action_2->setEnabled(1);
    ui->action_3->setEnabled(1);
}

void MainWindow::delTipMenuBtn()
{
   int row=ui->table_tip->currentRow();
   QJsonArray tipArray= m_currentJsonObject["tips"].toArray();
   tipArray.removeAt(row);
    m_currentJsonObject["tips"]=tipArray;
    MainWindow::save_Json();
   ui->table_tip->removeRow(row);
   ui->action_2->setEnabled(0);
   ui->action_3->setEnabled(0);
}

void MainWindow::editTipMenuBtn()
{   QTableWidgetItem* current_item =ui->table_tip->currentItem();
    int row = current_item->row();
    tipWindow->setTitle(ui->table_tip->item(row,0)->text());
    tipWindow->setContent(ui->table_tip->item(row,1)->text());
    tipWindow->show();
    this->close();
    ui->action_2->setEnabled(0);
    ui->action_3->setEnabled(0);
}

void MainWindow::show_tasks()
{
    QVector<qint64> vectorOfDate;
    QStringList keysList= m_currentJsonObject["tasks"].toObject()["task_list"].toObject().keys();
    int task_listSize=m_currentJsonObject["tasks"].toObject()["task_list"].toObject().size();

    for (int i = 0; i < task_listSize; ++i) {
        QJsonArray tagArray=m_currentJsonObject["tasks"].toObject()["task_list"].toObject()[keysList.at(i)].toArray();
        for (int j=0;j<tagArray.size() ;j++ ) {
            int k=0;
            qint64 time=QDateTime::fromString(tagArray[j].toObject()["date"].toString()).toSecsSinceEpoch();
            for(int l=0;l<vectorOfDate.size();l++){
                if(vectorOfDate[l]==time) k++;
            }
            if(k==0) vectorOfDate.append(time);
        }
    }
    int sizeOfDate=vectorOfDate.size();
    qint64 temp;
        for(int i = 0; i < sizeOfDate - 1; i++)
        {
            for(int j = i + 1; j < sizeOfDate; j++)
            {
                if (vectorOfDate[i] < vectorOfDate[j])
                {
                    temp = vectorOfDate[i];
                    vectorOfDate[i] = vectorOfDate[j];
                    vectorOfDate[j] = temp;
                }
            }
        }
        ui->tree_of_work->clear();
        if(ui->search_type->currentText()=="тексту")
        {
           for (int i = sizeOfDate-1; i>=0; i--)
           {
               QTreeWidgetItem *child= new QTreeWidgetItem;
               QDateTime dtOfVector=QDateTime::fromSecsSinceEpoch(vectorOfDate[i]);
               child->setText(0,dtOfVector.date().toString());
               for (int j = 0; j < task_listSize; ++j)
               {
                   bool tagHaveThisTime=false;
                   QJsonArray tagArray=m_currentJsonObject["tasks"].toObject()["task_list"].toObject()[keysList.at(j)].toArray();
                   QTreeWidgetItem* child1= new QTreeWidgetItem;
                   child1->setText(0,keysList.at(j));
                   QJsonObject colorObj=m_currentJsonObject["tasks"].toObject()["tags"].toObject()[keysList.at(j)].toObject()["color"].toObject();
                   QColor backgroundColor(colorObj["red"].toInt(),colorObj["green"].toInt(),colorObj["blue"].toInt());
                   QBrush backgroundBrush(backgroundColor,Qt::BrushStyle::SolidPattern);
                   child1->setBackground(0,backgroundBrush);
                   if(backgroundColor==Qt::black||backgroundColor==Qt::darkRed||
                      backgroundColor==Qt::darkYellow|| backgroundColor==Qt::darkBlue||
                      backgroundColor==Qt::darkCyan|| backgroundColor==Qt::darkGray||
                      backgroundColor==Qt::darkGreen||backgroundColor==Qt::darkMagenta){
                       QFont childFont=child1->font(0);
                       childFont.setWeight(QFont::Thin);
                        child1->setFont(0,childFont);
                        child1->setForeground(0,QBrush(Qt::GlobalColor::white,Qt::BrushStyle::SolidPattern));
                   }
                   if(ui->search_type->currentText()=="тексту")
                   {
                       for (int l = 0; l < tagArray.size(); ++l)
                       {
                           if(ui->search_lineEdit->text()=="")
                            {
                               if(dtOfVector==QDateTime::fromString(tagArray[l].toObject()["date"].toString()))
                           {
                                   QTreeWidgetItem* child2=new QTreeWidgetItem;
                                   child2->setText(0,dtOfVector.time().toString()+" - "+tagArray[l].toObject()["text"].toString());
                                   child1->addChild(child2);
                                   tagHaveThisTime=true;
                           }
                            }else
                           {
                               if(dtOfVector==QDateTime::fromString(tagArray[l].toObject()["date"].toString())&&ui->search_lineEdit->text()==tagArray[l].toObject()["text"].toString())
                               {
                                   QTreeWidgetItem* child2=new QTreeWidgetItem;
                                   child2->setText(0,dtOfVector.time().toString()+" - "+tagArray[l].toObject()["text"].toString());
                                   child1->addChild(child2);
                                   tagHaveThisTime=true;
                               }
                           }
                       }
                   if(tagHaveThisTime)child->addChild(child1);
               }
            }
            if(i!=sizeOfDate-1)
            {
               if(QDateTime::fromSecsSinceEpoch(vectorOfDate[i+1]).date()==QDateTime::fromSecsSinceEpoch(vectorOfDate[i]).date())
                {
                   int a =ui->tree_of_work->topLevelItemCount();
                   QTreeWidgetItem * itm =ui->tree_of_work->takeTopLevelItem(ui->tree_of_work->topLevelItemCount()-1);
                   if(a==0)
                   {
                       ui->tree_of_work->addTopLevelItem(child);
                   }
                   else
                   {
                       QList<QTreeWidgetItem *> children=child->takeChildren(),itmChildren=itm->takeChildren();
                       for (int i = 0; i < children.count(); ++i) {
                           bool tagNotExist=true;
                           for (int j = 0; j < itmChildren.count(); ++j) {
                               if(itmChildren[j]->text(0)==children[i]->text(0)){
                                   itmChildren[j]->addChildren(children[i]->takeChildren());
                                   itmChildren[j]->sortChildren(0,Qt::SortOrder::DescendingOrder);
                                   tagNotExist=false;
                               }
                           }
                           if(tagNotExist){
                               children[i]->sortChildren(0,Qt::SortOrder::DescendingOrder);
                               itmChildren.append(children[i]);
                           }
                       }
                        itm->addChildren(itmChildren);
                        ui->tree_of_work->addTopLevelItem(itm);
                   }
                }
               else
               {
                   ui->tree_of_work->addTopLevelItem(child);
               }
            }
            else
            { ui->tree_of_work->addTopLevelItem(child);}

   }    }
        else if(ui->search_type->currentText()=="тегам")
        {
        QStringList keysList=m_currentJsonObject["tasks"].toObject()["task_list"].toObject().keys();
        bool haveThisTag=false;
        for (int i = 0; i < keysList.size(); ++i) {
            if(ui->search_lineEdit->text()==keysList[i]){
                haveThisTag=true;
                break;
            }}
        if(haveThisTag){
            QJsonArray tagArray=m_currentJsonObject["tasks"].toObject()["task_list"].toObject()[ui->search_lineEdit->text()].toArray();
            QTreeWidgetItem* child=new QTreeWidgetItem;
            QString prevChildText;
            child->setText(0,ui->search_lineEdit->text());
            QJsonObject colorObj=m_currentJsonObject["tasks"].toObject()["tags"].toObject()[ui->search_lineEdit->text()].toObject()["color"].toObject();
            QColor backgroundColor(colorObj["red"].toInt(),colorObj["green"].toInt(),colorObj["blue"].toInt());
            QBrush backgroundBrush(backgroundColor,Qt::BrushStyle::SolidPattern);
            child->setBackground(0,backgroundBrush);
            if(backgroundColor==Qt::black||backgroundColor==Qt::darkRed||
               backgroundColor==Qt::darkYellow|| backgroundColor==Qt::darkBlue||
               backgroundColor==Qt::darkCyan|| backgroundColor==Qt::darkGray||
               backgroundColor==Qt::darkGreen||backgroundColor==Qt::darkMagenta){
                QFont childFont=child->font(0);
                childFont.setWeight(QFont::Thin);
                 child->setFont(0,childFont);
                 child->setForeground(0,QBrush(Qt::GlobalColor::white,Qt::BrushStyle::SolidPattern));
            }
                for (int i = 0; i < sizeOfDate; ++i)
                {
                    QTreeWidgetItem* child1=new QTreeWidgetItem;
                    child1->setText(0,QDateTime::fromSecsSinceEpoch(vectorOfDate[i]).date().toString());
                    for (int j = 0; j < tagArray.size(); ++j)
                    {
                        if(QDateTime::fromString(tagArray[j].toObject()["date"].toString())==QDateTime::fromSecsSinceEpoch(vectorOfDate[i]))
                        {
                           QTreeWidgetItem* child2=new QTreeWidgetItem;
                           child2->setText(0,QDateTime::fromSecsSinceEpoch(vectorOfDate[i]).time().toString()+" - "+tagArray[j].toObject()["text"].toString());
                           child1->addChild(child2);
                        }
                    }
                    if(prevChildText==child1->text(0)){
                         QList<QTreeWidgetItem *> children=child1->takeChildren();
                         QTreeWidgetItem * prevChild=child->takeChild(child->childCount()-1);
                         prevChild->addChildren(children);
                         child->addChild(prevChild);
                    }else child->addChild(child1);

                    prevChildText=child1->text(0);
                }
                ui->tree_of_work->addTopLevelItem(child);
            }else{
        QTreeWidgetItem* itm=new QTreeWidgetItem;
        itm->setText(0,"Такого тега нет");
        ui->tree_of_work->addTopLevelItem(itm);
        }
       }
    ui->tree_of_work->setColumnCount(1);
    MainWindow::show();
}

void MainWindow::saveNewTag(QColor tagColor,QString tagName )
{
    QJsonObject tagNameObj,colorObject,tasksObject=m_currentJsonObject["tasks"].toObject();
    QJsonObject  tagsObject=m_currentJsonObject["tasks"].toObject()["tags"].toObject();
   int     red=tagColor.red(),
           green=tagColor.green(),
           blue=tagColor.blue();
   colorObject["red"]=red;
   colorObject["green"]=green;
   colorObject["blue"]=blue;
   tagNameObj["color"]=colorObject;
   tagsObject[tagName]=tagNameObj;
   tasksObject["tags"]=tagsObject;
   m_currentJsonObject["tasks"]=tasksObject;
   MainWindow::save_Json();
   taskWindow->setTags(m_currentJsonObject);
}

void MainWindow::newTaskButtonTriggered()
{
    taskWindow->setTags(m_currentJsonObject);
    taskWindow->show();
    this->close();
}

void MainWindow::saveNewTask(QJsonObject newTaskObject,QString tagName){
    QJsonArray taskArray=m_currentJsonObject["tasks"].toObject()["task_list"].toObject()[tagName].toArray();
    QJsonObject taskArrayObject=m_currentJsonObject["tasks"].toObject()["task_list"].toObject(),
            tasksObject=m_currentJsonObject["tasks"].toObject(),tagObject;
    taskArray.append(newTaskObject);
    taskArrayObject.insert(tagName,taskArray);
    tasksObject.insert("task_list",taskArrayObject);
    m_currentJsonObject["tasks"]=tasksObject;
    MainWindow::save_Json();
}

void MainWindow::delTaskMenuBtn()
{
    QTreeWidgetItem * curItem=ui->tree_of_work->currentItem();
    QTreeWidgetItem * parCurItem=curItem->parent();
    QTreeWidgetItem * parparCurItem=parCurItem->parent();
    QString curItemStr=ui->tree_of_work->currentItem()->text(0);
            QString parItemStr=parCurItem->text(0);
    QString parparItemStr=parparCurItem->text(0);
    QString textPlusDateTime,timeStr,textStr;
    textPlusDateTime=parparItemStr+" "+curItemStr;
    QStringList dateANDtext=textPlusDateTime.split(QLatin1Char('-'));
    QDateTime curDate=QDateTime::fromString(dateANDtext[0]);
    QString curText=dateANDtext[1].remove(0,1);
    QJsonArray tagArray=m_currentJsonObject["tasks"].toObject()["task_list"].toObject()[parItemStr].toArray();
    for (int i = 0; i < tagArray.size(); ++i)
    {
        QDateTime arrDate=QDateTime::fromString( tagArray[i].toObject()["date"].toString());
        QString arrText=tagArray[i].toObject()["text"].toString();
        if(arrDate==curDate&&arrText==curText)
        {
            tagArray.removeAt(i);
        }
    }
    QJsonObject tasksObj= m_currentJsonObject["tasks"].toObject(),
            task_listObj=m_currentJsonObject["tasks"].toObject()["task_list"].toObject();
            task_listObj.insert(parItemStr,tagArray);
            tasksObj.insert("task_list",task_listObj);
            m_currentJsonObject["tasks"]=tasksObj;

    save_Json();
    show_tasks();
}

void MainWindow::editTaskMenuBtn()
{

    QTreeWidgetItem * curItem=ui->tree_of_work->currentItem();
    QTreeWidgetItem * parCurItem=curItem->parent();
    QTreeWidgetItem * parparCurItem=parCurItem->parent();
    QString curItemStr=ui->tree_of_work->currentItem()->text(0);
            QString parItemStr=parCurItem->text(0);
    QString parparItemStr=parparCurItem->text(0);
    QString textPlusDateTime,timeStr,textStr;
    textPlusDateTime=parparItemStr+" "+curItemStr;
    QStringList dateANDtext=textPlusDateTime.split(QLatin1Char('-'));
    QDateTime curDate=QDateTime::fromString(dateANDtext[0]);
    QString curText=dateANDtext[1].remove(0,1);
    QJsonArray tagArray=m_currentJsonObject["tasks"].toObject()["task_list"].toObject()[parItemStr].toArray();
    for (int i = 0; i < tagArray.size(); ++i)
    {
        QDateTime arrDate=QDateTime::fromString( tagArray[i].toObject()["date"].toString());
        QString arrText=tagArray[i].toObject()["text"].toString();
        if(arrDate==curDate&&arrText==curText)
        {
            tagArray.removeAt(i);
        }
    }
    QJsonObject tasksObj= m_currentJsonObject["tasks"].toObject(),
            task_listObj=m_currentJsonObject["tasks"].toObject()["task_list"].toObject();
            task_listObj.insert(parItemStr,tagArray);
            tasksObj.insert("task_list",task_listObj);
            m_currentJsonObject["tasks"]=tasksObj;
    save_Json();
    taskWindow->setTags(m_currentJsonObject);
    taskWindow->setTagText(parItemStr);
    taskWindow->setTaskText(curText);
    taskWindow->setTaskDate(curDate);
    taskWindow->show();
    this->close();
}

void MainWindow::newHabitBtnClicked(){
   habitWindow->show();
   this->close();
}

void MainWindow::saveNewHabit(QJsonObject habitObj){
    QJsonArray habitsArray=m_currentJsonObject["habits"].toArray();
    habitsArray.append(habitObj);
    m_currentJsonObject.insert("habits",habitsArray);
    MainWindow::save_Json();
    habitWindow->close();
    ui->currentHabitSpinBox->setMaximum(habitsArray.size());
    this->show();
    MainWindow::show_habits();
}

void MainWindow::show_habits(){
    int currentWidgetIndex=ui->field_of_habits->currentIndex();
    QJsonArray habitsArray=m_currentJsonObject["habits"].toArray();
    for (int i = ui->field_of_habits->count(); i > 0; i--) {
       QWidget * someWidget=ui->field_of_habits->widget(i);
       ui->field_of_habits->removeWidget(someWidget);
    }
    for (int i = 0; i < habitsArray.size(); ++i) {
        QWidget* page=new QWidget();
        QVBoxLayout* verticalLayout=new QVBoxLayout(page);
        page->setObjectName("page"+QString::number(i));
        verticalLayout->setObjectName("verticalLayout"+QString::number(i));
        QLabel *label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label_2"));
        label->setMaximumSize(QSize(16777215, 25));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);
        label->setMargin(0);
        label->setIndent(-1);
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        label->setText("Периодичность - "+habitsArray[i].toObject()["periodicity"].toString());
        verticalLayout->addWidget(label);
        QLCDNumber* lcdNumber = new QLCDNumber(page);
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setFrameShadow(QFrame::Plain);
        int currentCount= habitsArray[i].toObject()["count"].toInt(),digit=0;
        lcdNumber->display(currentCount);
        while(1)
        {
            if(currentCount==0)break;
            digit++;
            currentCount/=10;
        }
        lcdNumber->setDigitCount(digit);
        if(digit==0) lcdNumber->setDigitCount(1);
        lcdNumber->setMode(QLCDNumber::Dec);
        QPushButton* pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton"+QString::number(i));
        pushButton->setText(habitsArray[i].toObject()["name"].toString());
        connect(pushButton,&QPushButton::clicked,this,&MainWindow::plusCountBtnClicked);
        verticalLayout->addWidget(lcdNumber);
        verticalLayout->addWidget(pushButton);
        ui->field_of_habits->addWidget(page);
    }
    ui->currentHabitSpinBox->setMaximum(habitsArray.size());
    ui->currentHabitSpinBox->setValue(currentWidgetIndex);
    ui->field_of_habits->setCurrentIndex(0);
    if(habitsArray.size()<currentWidgetIndex-1)
    {
    ui->field_of_habits->setCurrentIndex(1);
    }else{
    ui->field_of_habits->setCurrentIndex(currentWidgetIndex);
    }
}

void MainWindow::on_currentHabitSpinBox_valueChanged(int currentIndex)
{
    ui->field_of_habits->setCurrentIndex(currentIndex);
}

void MainWindow::plusCountBtnClicked(){
      QJsonArray habitsArray=m_currentJsonObject["habits"].toArray();
      QJsonObject habitObj=habitsArray[ui->currentHabitSpinBox->value()-1].toObject();
      int currentCount=habitObj["count"].toInt();
      if(habitObj["periodicity"].toString()=="Каждую секунду (тест)"){
          if(QDateTime::fromString( habitObj["time"].toString()).secsTo(QDateTime::currentDateTime())>qint64(3))
              currentCount=0;
      }
      if(habitObj["periodicity"].toString()=="Ежедневно"){
            if(QDateTime::fromString( habitObj["time"].toString()).daysTo(QDateTime::currentDateTime())>qint64(1))
                    currentCount=0;
      }
      if(habitObj["periodicity"].toString()=="Раз в неделю"){
          if(QDateTime::fromString( habitObj["time"].toString()).daysTo(QDateTime::currentDateTime())>qint64(7))
              currentCount=0;}
      if(habitObj["periodicity"].toString()=="Раз в месяц"){
          if(QDateTime::fromString( habitObj["time"].toString()).daysTo(QDateTime::currentDateTime())>qint64(30))
              currentCount=0;}
      habitObj["time"]=QDateTime::currentDateTime().toString();
      habitObj["count"]=currentCount+1;
      habitsArray[ui->currentHabitSpinBox->value()-1]=habitObj;
      m_currentJsonObject["habits"]=habitsArray;
          save_Json();
          show_habits();
}

void MainWindow::delHabitMenuBtn(){

        QJsonArray habitsArray=m_currentJsonObject["habits"].toArray();
        habitsArray.removeAt(ui->currentHabitSpinBox->value()-1);
        m_currentJsonObject["habits"]=habitsArray;
        save_Json();
        show_habits();
}

void MainWindow::editHabitMenuBtn(){
    QJsonArray habitsArray=m_currentJsonObject["habits"].toArray();
    QJsonObject habitObj=habitsArray[ui->currentHabitSpinBox->value()-1].toObject();
    habitsArray.removeAt(ui->currentHabitSpinBox->value()-1);
    m_currentJsonObject["habits"]=habitsArray;
    save_Json();
    habitWindow->setValue(habitObj["strike"].toInt(),habitObj["name"].toString(),habitObj["periodicity"].toString());
    habitWindow->show();
    this->close();
}

void  MainWindow::loginMenuBtn(){
    registrWindow->show();
    this->close();
}

void  MainWindow::logoutMenuBtn(){

}

void MainWindow::checkLogin(){}
void MainWindow::addLogin(){}
void MainWindow::synchronyze(){}
void MainWindow::currentTabChanged(int currentTab){
    disconnect(ui->action_2,&QAction::triggered,nullptr,nullptr);
    disconnect(ui->action,&QAction::triggered,nullptr,nullptr);
    disconnect(ui->action_3,&QAction::triggered,nullptr,nullptr);
    ui->action_2->setEnabled(0);
    ui->action_3->setEnabled(0);
    switch(currentTab){
    case 0:
        connect(ui->action_2,&QAction::triggered,this,&MainWindow::delTipMenuBtn);
        connect(ui->action,&QAction::triggered,this,&MainWindow::new_tip_clicked);
        connect(ui->action_3,&QAction::triggered,this,&MainWindow::editTipMenuBtn);
        break;
    case 1:
        connect(ui->action_2,&QAction::triggered,this,&MainWindow::delTaskMenuBtn);
        connect(ui->action,&QAction::triggered,this,&MainWindow::newTaskButtonTriggered);
        connect(ui->action_3,&QAction::triggered,this,&MainWindow::editTaskMenuBtn);
        MainWindow::show_tasks();
        break;
    case 2:
        connect(ui->action_2,&QAction::triggered,this,&MainWindow::delHabitMenuBtn);
        connect(ui->action,&QAction::triggered,this,&MainWindow::newHabitBtnClicked);
        connect(ui->action_3,&QAction::triggered,this,&MainWindow::editHabitMenuBtn);
        ui->action_2->setEnabled(1);
        ui->action_3->setEnabled(1);
        MainWindow::show_habits();
        break;
    default:
        break;
    }
}


