#ifndef NEWTIPWINDOW_H
#define NEWTIPWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {class NewTipWindow;}
QT_END_NAMESPACE

class NewTipWindow : public QWidget
{
    Q_OBJECT

    QString titl,cont;
public:
    explicit NewTipWindow(QWidget *parent = 0);
    ~NewTipWindow();
    void setTitle(QString title);
    void setContent(QString content);

signals:
    void mainWindowSignal();
    void sendNewTip(QString title,QString content);
private slots:
    void toMainWindow();
    void saveTip();
private:
    Ui::NewTipWindow *ui;

};

#endif // NEWTIPWINDOW_H12
