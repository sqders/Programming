#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QImage"
#include <iostream>
#include <math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::encodeMsg);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::decodeMsg);
}

QByteArray marker=QString("❤").toUtf8();
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", tr("Допустимые форматы (*.png)"));
    if(MainWindow::image.QImage::load(fileName,nullptr))
    {
        ui->label->setText("Изображение успешно загружено");
    }
    else
    {
        ui->label->setText( "Изображение не загружено");
    }
    image.convertTo(QImage::Format_ARGB32);
}
void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File",
                               "",
                               tr("Images (*.png)"));
    if(MainWindow::image.QImage::save(fileName,nullptr))
    {
        ui->label->setText("Изображение успешно сохранено");
    }
    else
    {
        ui->label->setText(  "Изображение не сохранено");
    }
}
void MainWindow::encodeMsg()
{
QString msg=ui->plainTextEdit->toPlainText();
QByteArray byte_msg=msg.toUtf8();
int size_of_msg=byte_msg.size();
for (int i = 0; i <4; ++i) {
    byte_msg.prepend(QByteArray::number(0,2));
    unsigned char byte_of_size=size_of_msg%255;
        size_of_msg/=255;
    byte_msg[0]=byte_of_size;
}

byte_msg.prepend(marker);

int bits_in_image=MainWindow::image.size().height()*MainWindow::image.size().width()*3;
if(byte_msg.size()*8+24+32>bits_in_image)
{
  ui->label->setText(  "Ошибка. Не достаточно места!");
}else
{
    int wi_img=MainWindow::image.width(),y=0,x=-1;
                                                                //0-red 1-green 2-blue
    unsigned char  p_red,p_green,p_blue;
    for (int i = 0; i < byte_msg.size(); ++i)/*i-current byte of msg*/ {
        for (int j = 0; j <8; j++)/*j-current bit of byte*/ {
            unsigned char mask=pow(2,7-j);
            switch (((i*8+j)%3)) {
            case 0:
                if(x==wi_img)
                {
                    y++;
                    x=0;
                }
                else
                {
                    x++;
                }
                p_red=MainWindow::image.QImage::pixelColor(x,y).red();
                p_green=MainWindow::image.QImage::pixelColor(x,y).green();
                p_blue=MainWindow::image.QImage::pixelColor(x,y).blue();

                if((byte_msg[i]&mask)==mask)
                {
                    p_red=(p_red>>1)<<1;
                    p_red|=0x01;
                }
                else
                {
                    p_red=(p_red>>1)<<1;
                }
                break;

            case 1:
                if((byte_msg[i]&mask)==mask)
                {
                    p_green=(p_green>>1)<<1;
                    p_green|=0x01;
                }
                else
                {
                    p_green=(p_red>>1)<<1;
                }
                break;
            case 2:
                if((byte_msg[i]&mask)==mask)
                {
                    p_blue=(p_blue>>1)<<1;
                    p_blue|=0x01;
                }
                else
                {
                    p_blue=(p_red>>1)<<1;
                }
                break;
            }
            MainWindow::image.QImage::setPixelColor(x,y,QColor(p_red,p_green,p_blue));
        }
    }

ui->label->setText(  "Сообщение добавлено в картинку!");
}
}
void MainWindow::decodeMsg()
{
    int wi_img=MainWindow::image.width(),y=0,x=-1;
                                            //0-red 1-green 2-blue
    unsigned char  p_red,p_green,p_blue;
    for(int i=0;i<marker.size();i++)
    {
        for(int j =0;j<8;j++)
        {
            unsigned char mask=pow(2,7-j);
            switch (((i*8+j)%3)) {
            case 0:
                if(x==wi_img)
                {
                    y++;
                    x=0;
                }
                else
                {
                    x++;
                }
                p_red=MainWindow::image.QImage::pixelColor(x,y).red();
                p_green=MainWindow::image.QImage::pixelColor(x,y).green();
                p_blue=MainWindow::image.QImage::pixelColor(x,y).blue();

                p_red<<=7;
                p_red>>=j;
                if((marker[i]&mask)==p_red)
                {} else{ ui->label->setText(  "Сообщение не обнаружено"); return ;}
                break;

            case 1:
                p_green<<=7;
                p_green>>=j;
                if((marker[i]&mask)==p_green)
                {}else { ui->label->setText(  "Сообщение не обнаружено"); return ;}

                break;
            case 2:
                p_blue<<=7;
                p_blue>>=j;
                if((marker[i]&mask)==p_blue)
                {}else { ui->label->setText(  "Сообщение не обнаружено"); return ;}
                break;
            }
        }
    }
    QByteArray size_of_msg;
    size_of_msg.resize(4);
    for(int i=0;i<4;i++)
    {
        for(int j =0;j<8;j++)
        {
            switch (((i*8+j)%3)) {
            case 0:
                if(x==wi_img)
                {
                    y++;
                    x=0;
                }
                else
                {
                    x++;
                }
                p_red=MainWindow::image.QImage::pixelColor(x,y).red();
                p_green=MainWindow::image.QImage::pixelColor(x,y).green();
                p_blue=MainWindow::image.QImage::pixelColor(x,y).blue();

                if((p_red&0x01)==0x01)
                {
                    size_of_msg[i]=(size_of_msg[i]<<1)|0x01;
                }
                else size_of_msg[i]=size_of_msg[i]<<1;
                break;

            case 1:
                if((p_green&0x01)==0x01)
                {
                    size_of_msg[i]=(size_of_msg[i]<<1)|0x01;
                }
                else size_of_msg[i]=size_of_msg[i]<<1;
                break;
            case 2:
                if((p_blue&0x01)==0x01)
                {
                    size_of_msg[i]=(size_of_msg[i]<<1)|0x01;
                }
                else size_of_msg[i]=size_of_msg[i]<<1;
                break;
            }
        }
    }
    int int_size_of_msg=0;
    unsigned char mask;
    for (int i = 0; i < 4; ++i) {
        for (int j=0;j<8 ;j++ ) {
            mask=pow(2,j);
            if((size_of_msg[i]&mask)==mask)int_size_of_msg+=pow(2,(j+8*(3-i)));
        }
    }
    ui->label->setText(QString("Присутствует сообщение длиной %1 байт").arg(int_size_of_msg));
    QByteArray byte_msg;
    byte_msg.resize(int_size_of_msg);
    for(int i=0;i<int_size_of_msg;i++)
    {
        for(int j =0;j<8;j++)
        {
            switch (((i*8+j)%3)) {
            case 1:
                if(x==wi_img)
                {
                    y++;
                    x=0;
                }
                else
                {
                    x++;
                }
                p_red=MainWindow::image.QImage::pixelColor(x,y).red();
                p_green=MainWindow::image.QImage::pixelColor(x,y).green();
                p_blue=MainWindow::image.QImage::pixelColor(x,y).blue();

                if((p_red&0x01)==0x01)
                {
                    byte_msg[i]=(byte_msg[i]<<1)|0x01;
                }
                else byte_msg[i]=byte_msg[i]<<1;
                break;

            case 2:
                if((p_green&0x01)==0x01)
                {
                    byte_msg[i]=(byte_msg[i]<<1)|0x01;
                }
                else byte_msg[i]=byte_msg[i]<<1;
                break;
            case 0:
                if((p_blue&0x01)==0x01)
                {
                    byte_msg[i]=(byte_msg[i]<<1)|0x01;
                }
                else byte_msg[i]=byte_msg[i]<<1;
                break;
            }
        }
    }
    QString msg=QString::fromUtf8(byte_msg);
    ui->plainTextEdit->setPlainText(msg);
}
