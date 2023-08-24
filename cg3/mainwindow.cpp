#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<iostream>
using namespace std;
QImage img(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver=0;
    start=0; line=0;
    x_min=100; x_max=300; y_min=100; y_max=300;
    global_color=qRgb(100, 100, 200);
//    polygon();
    TOP=8; BOT=4; RIGHT=2; LEFT=1, IN=100;
//    global_color=qRgb(150, 250, 250);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    start=!start;
}

void MainWindow::dda(int x1, int y1, int x2, int y2, int line_depth)
{
    float dx, dy, len, x, y, xinc, yinc;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>=abs(dy)){
        len=abs(dx);
    }
    else{
        len=abs(dy);
    }
    xinc=dx/len;
    yinc=dy/len;
    x=x1;
    y=y1;
    for(int i=0; i<len; i++){
        x+=xinc;
        y+=yinc;
        img.setPixel(x, y, qRgb(150, 150, 200));
        for(int offset=0; offset<line_depth; offset++)
        {
            img.setPixel(x+offset, y+offset, global_color);
         }
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start){
        int p=event->pos().x();
        int q=event->pos().y();
        a[ver]=p;
        b[ver]=q;
        if(line){
            dda(a[ver], b[ver], a[ver-1], b[ver-1]);
            line=false;
        }
        else{
            line=true;
        }
        ver++;
    }
}

int MainWindow::getcode(int x, int y)
{
    int res=0;
    if(x<x_min)res|=LEFT;
    if(x>x_max)res|=RIGHT;
    if(y<y_min)res|=BOT;
    if(y>y_max)res|=TOP;
    return res;
}


void MainWindow::cohen_sutherland_clip(float x1, float y1, float x2, float y2)
{
      int code1 = getcode(x1, y1);
      int code2 = getcode(x2, y2);

      bool flag = false;

      while (true) {
          float m=(x2-x1)/(y2-y1);
          if ((code1 == 0) && (code2 == 0))
          {
              flag = true;
              break;
          }
          else if (code1 & code2)
          {
              break;
          }
          else
          {
              int badcode;
              double x, y;
              if (code1 != 0)
              {
                  badcode = code1;
              }
              else
              {
                  badcode = code2;
              }
              if (badcode & TOP) {
                  x=x1 + m*(y_max-y1);
                  y = y_max;
              }
              else if (badcode & BOT) {
                  x=x1 + m*(y_min-y1);
                  y = y_min;
              }
              else if (badcode & RIGHT) {
                  y=y1+(x_max-x1)/m;
                  x = x_max;
              }
              else if (badcode & LEFT) {
                  y=y1+(x_min-x1)/m;
                  x = x_min;
              }
              if (badcode == code1) {
                  x1 = x;
                  y1 = y;
                  code1 = getcode(x1, y1);
              }
              else {
                  x2 = x;
                  y2 = y;
                  code2 = getcode(x2, y2);
              }
          }
      }
    if(flag)
    {
        dda(x1, y1, x2, y2);
    }
}


void MainWindow::on_pushButton_clicked()
{
    eraseall();
    for(int i=0; i<ver; i+=2){
//        global_color=qRgb(100, 150, 240);
        cohen_sutherland_clip(a[i+1], b[i+1], a[i], b[i]);
    }

}

void MainWindow::eraseall()
{
            for(int i=0; i<500; i++){
                for(int j=0; j<500; j++){
                    img.setPixel(i, j, qRgb(0,0,0));
                }
            }
//            global_color=qRgb(250, 250, 100);
            polygon();
            ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::polygon()
{
    dda(x_min, y_min, x_min, y_max);
    dda(x_min, y_max, x_max, y_max);
    dda(x_max, y_max, x_max, y_min);
    dda(x_max, y_min, x_min, y_min);
}
