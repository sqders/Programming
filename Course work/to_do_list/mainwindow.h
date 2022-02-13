#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <newtipwindow.h>
#include <newtaskwindow.h>
#include <newhabitwindow.h>
#include <registrwindow.h>
#include <QJsonObject>
#include <QByteArray>
#include <QNetworkAccessManager>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QJsonObject m_currentJsonObject;
    QByteArray data;
    QString server_info="http://localhost:5000";
private:
    Ui::MainWindow *ui;
    NewTipWindow *tipWindow;
    NewTaskWindow *taskWindow;
    NewHabitWindow * habitWindow;
    RegistrWindow * registrWindow;
    QNetworkAccessManager * manager;
public slots:
    void new_tip_clicked();
    void receiveNewTip(QString title,QString content);
    void show_tip();
    void show_tasks();
    void show_habits();
    void read_server();
    void read_Json();
    void save_Json();
    void saveNewTag(QColor,QString);
    void saveNewTask(QJsonObject,QString);
    void saveNewHabit(QJsonObject);
    void postLoginReady(QNetworkReply * reply);
    void postRegistrReady(QNetworkReply * reply);
    void postClientSynReady(QNetworkReply * reply);
    void postServerSynReady(QNetworkReply * reply);
    void sockDisc();
private slots:
    void on_table_tip_itemSelectionChanged();
    void editTipMenuBtn();
    void delTipMenuBtn();
    void newTaskButtonTriggered();
    void currentTabChanged(int);
    void delTaskMenuBtn();
    void editTaskMenuBtn();
    void on_tree_of_work_itemSelectionChanged();
    void newHabitBtnClicked();
    void on_currentHabitSpinBox_valueChanged(int);
    void plusCountBtnClicked();
    void delHabitMenuBtn();
    void editHabitMenuBtn();
    void loginMenuBtn();
    void logoutMenuBtn();
    void checkLogin(QString,QString);
    void registration(QString,QString);
    void synchronyzeServer();
    void synchronyzeClient();

signals:
    void sendCurTip(QString title,QString content);
};
#endif // MAINWINDOW_H21
