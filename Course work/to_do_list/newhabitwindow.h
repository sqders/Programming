#ifndef NEWHABITWINDOW_H
#define NEWHABITWINDOW_H
#include <QWidget>
#include <QJsonObject>

namespace Ui {class NewHabitWindow;}

class NewHabitWindow: public QWidget
{
     Q_OBJECT
public:
    explicit NewHabitWindow(QWidget *parent = 0);
     ~NewHabitWindow();
    void setValue(int,QString,QString);
private:
    Ui::NewHabitWindow *ui;
private slots:
    void newHabitBtnClicked();
    void toMainWindowBtn();
signals :
    void newHabitSignal(QJsonObject);
    void toMainWindowSignal();
};


#endif // NEWHABITWINDOW_H
