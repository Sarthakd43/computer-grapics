#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std ;
QImage img(500, 500, QImage :: Format_RGB888);
//QImage img2(500, 500, QImage :: Format_RGB888) ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dda(int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1 ;
    float dy = y2 - y1 ;
    float len ;
    if ( abs(dx) >= abs(dy) )
    {
        len = abs(dx);
    }
    else
    {
        len = abs(dy);
    }
    float Xinc = dx / len ;
    float Yinc = dy / len ;
    float x = x1 ;
    float y = y1 ;
    img.setPixel(x,y,qRgb(255,255,255));
    int i = 1 ;
    while(i<=len)
    {
        x = x + Xinc ;
        y = y + Yinc ;
        img.setPixel(x,y,qRgb(255,255,255));
        i++;
    }
     ui -> label->setPixmap(QPixmap :: fromImage(img));
}
void MainWindow::on_pushButton_clicked()
{
    dda(0,250,500,250);
    dda(250,0,250,500);
    int x1,y1,x2,y2,x3,y3;
    x1 = ui -> textEdit -> toPlainText().toInt();
    y1 = ui -> textEdit_2 -> toPlainText().toInt();
    x2 = ui -> textEdit_3 -> toPlainText().toInt();
    y2 = ui -> textEdit_4 -> toPlainText().toInt();
    x3 = ui -> textEdit_7 -> toPlainText().toInt();
    y3 = ui -> textEdit_8 -> toPlainText().toInt();
    dda(x1+250,y1+250,x2+250,y2+250);
    dda(x2+250,y2+250,x3+250,y3+250);
    dda(x3+250,y3+250,x1+250,y1+250);
}

void MainWindow::on_pushButton_2_clicked()
{
    int x1,y1,x2,y2,x3,y3, tx, ty ;
    x1 = ui -> textEdit -> toPlainText().toInt();
    y1 = ui -> textEdit_2 -> toPlainText().toInt();
    x2 = ui -> textEdit_3 -> toPlainText().toInt();
    y2 = ui -> textEdit_4 -> toPlainText().toInt();
    x3 = ui -> textEdit_7 -> toPlainText().toInt();
    y3 = ui -> textEdit_8 -> toPlainText().toInt();
    tx = ui -> textEdit_5 -> toPlainText().toInt();
    ty = ui -> textEdit_6 -> toPlainText().toInt();
    dda(x1+250+tx,y1+250+ty,x2+250+tx,y2+250+ty) ;
    dda(x2+250+tx,y2+250+ty,x3+250+tx,y3+250+ty) ;
    dda(x3+250+tx,y3+250+ty,x1+250+tx,y1+250+ty);
}

void MainWindow::on_pushButton_3_clicked()
{
    int x1,y1,x2,y2,x3,y3,Sx,Sy ;
    x1 = ui -> textEdit -> toPlainText().toInt();
    y1 = ui -> textEdit_2 -> toPlainText().toInt();
    x2 = ui -> textEdit_3 -> toPlainText().toInt();
    y2 = ui -> textEdit_4 -> toPlainText().toInt();
    x3 = ui -> textEdit_7 -> toPlainText().toInt();
    y3 = ui -> textEdit_8 -> toPlainText().toInt();
    Sx = ui -> textEdit_9 -> toPlainText().toInt();
    Sy = ui -> textEdit_10 -> toPlainText().toInt();
    x1 = x1 * Sx ;
    y1 = y1 * Sy ;
    x2 = x2 * Sx ;
    y2 = y2 * Sy ;
    x3 = x3 * Sx ;
    y3 = y3 * Sy ;
    dda(x1+250,y1+250,x2+250,y2+250) ;
    dda(x2+250,y2+250,x3+250,y3+250) ;
    dda(x3+250,y3+250,x1+250,y1+250);
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2,x3,y3,degree_angle ;
    x1 = ui -> textEdit -> toPlainText().toFloat();
    y1 = ui -> textEdit_2 -> toPlainText().toFloat();
    x2 = ui -> textEdit_3 -> toPlainText().toFloat();
    y2 = ui -> textEdit_4 -> toPlainText().toFloat();
    x3 = ui -> textEdit_7 -> toPlainText().toFloat();
    y3 = ui -> textEdit_8 -> toPlainText().toFloat();
    degree_angle = ui -> textEdit_11 -> toPlainText().toFloat();
    float radian_angle = (degree_angle) * (0.01745) ;
    cout<<radian_angle<<endl;
    float X1,Y1,X2,Y2,X3,Y3;
    X1 = x1 * cos(radian_angle) - y1 * sin(radian_angle) ;
    Y1 = x1 * sin(radian_angle) + y1 * cos(radian_angle) ;
    X2 = x2 * cos(radian_angle) - y2 * sin(radian_angle) ;
    Y2 = x2 * sin(radian_angle) + y2 * cos(radian_angle) ;
    X3 = x3 * cos(radian_angle) - y3 * sin(radian_angle) ;
    Y3 = x3 * sin(radian_angle) + y3 * cos(radian_angle) ;
    dda(X1+250,Y1+250,X2+250,Y2+250) ;
    dda(X2+250,Y2+250,X3+250,Y3+250) ;
    dda(X3+250,Y3+250,X1+250,Y1+250) ;
}
