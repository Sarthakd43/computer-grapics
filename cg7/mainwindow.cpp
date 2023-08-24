#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;
QImage img(500, 500, QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    globalcolor=qRgb(100, 150, 250);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{  
    snowflake(310, 280, 120, 5);
}

void MainWindow::dda(int x1, int y1, int x2, int y2)
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
           img.setPixel(x, y, globalcolor);
       }
       ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::kochcurve(float x1, float y1, float x2, float y2, int epochs)
{
   if(epochs==0){
       dda(x1, y1, x2, y2);
       return;
   }
   float p1_x=(2*x1+x2)/3;
   float p1_y=(2*y1+y2)/3;
   float p2_x=(2*x2+x1)/3;
   float p2_y=(2*y2+y1)/3;
   float p_x=(p1_x+p2_x)*0.5 - (p2_y-p1_y)*0.867;
   float p_y=(p2_x-p1_x)*0.867 + (p1_y+p2_y)*0.5;
   kochcurve(x1, y1, p1_x, p1_y, epochs-1);
   kochcurve(p2_x, p2_y, x2, y2, epochs-1);
   kochcurve(p1_x, p1_y, p_x, p_y, epochs-1);
   kochcurve(p_x, p_y, p2_x, p2_y, epochs-1);
}

void MainWindow::snowflake(float x, float y, float r, int epochs){
   float s1_3=0.577;
   kochcurve(x-r*0.5, y+r*0.5*s1_3, x+r*0.5, y+r*0.5*s1_3, epochs);
   kochcurve(x+r*0.5, y+r*0.5*s1_3, x, y-r*s1_3, epochs);
   kochcurve(x, y-r*s1_3, x-r*0.5, y+r*0.5*s1_3, epochs);
}

