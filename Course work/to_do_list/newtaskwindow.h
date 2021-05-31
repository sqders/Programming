#ifndef NEWTASKWINDOW_H
#define NEWTASKWINDOW_H

#include <QWidget>
#include <QJsonObject>
namespace Ui {class NewTaskWindow;}


class NewTaskWindow: public QWidget
{
    Q_OBJECT
    QJsonObject tags;
    QString taskText,tagText;
   public:
       explicit NewTaskWindow(QWidget *parent = 0);
       ~NewTaskWindow();
        void setTags(QJsonObject);
        void setTaskText(QString);
        void setTagText(QString);
        void setTaskDate(QDateTime);
   signals:
    void mainWindowSignal();
    void newTagSignal(QColor,QString);
    void newTaskSignal(QJsonObject,QString);
   private:
       Ui::NewTaskWindow *ui;
   private slots:
    void newTagClicked();
    void newTaskClicked();
    void toMainWindow();
};

#endif // NEWTASKWINDOW_H
