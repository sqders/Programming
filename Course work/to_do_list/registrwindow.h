#ifndef REGISTRWINDOW_H
#define REGISTRWINDOW_H
#include <QWidget>
#include <QJsonObject>
namespace Ui {class RegistrWindow;}
class RegistrWindow: public QWidget
{
    Q_OBJECT
public:
   explicit RegistrWindow(QWidget *parent = 0);
    ~RegistrWindow();
    void setLable(QString);
    void clearWindow();
private:
    Ui::RegistrWindow *ui;
private slots :
    void loginBtnClicked();
    void registerBtnClicked();
signals:
    void loginBtnSignal(QString,QString);
    void registerBtnSignal(QString,QString);
};
#endif // REGISTRWINDOW_H
