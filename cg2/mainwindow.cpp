#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include <iostream>
#include <algorithm>
#include <QColorDialog>
using namespace std;
QColor c;
QImage img(500,500,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start=true;
    ver=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    int i;
    float dx,dy;

    a[ver]=a[0];
    b[ver]=b[0];

    for(i=0;i<ver;i++)
    {
        //Calculation of slope of each line
        dx= a[i+1]-a[i];
        dy= b[i+1]-b[i];
        if(dy==0)
            slope[i]=1;
        if(dx==0)
            slope[i]=0.0;
        if((dy!=0.0f)&&(dx!=0.0f)) //calculate inverse slope
            {
             slope[i]=dx/dy;
            }
    }

    for(int y=0;y<500;y++)
    {
        k=0;
        for(i=0;i<ver;i++)
        {
            if(((b[i]<=y)&&(b[i+1]>y))||((b[i]>y)&&(b[i+1]<=y)))
            {
                xi[k]=int(a[i]+(slope[i]*(y-b[i])));
                k++;
            }
        }

    sort(xi,xi+k);

    for(i=0;i<k;i+=2)
    {
        dda(xi[i],y,xi[i+1]+1,y);
    }
    }
}



void MainWindow::dda(int x1, int y1, int x2, int y2)
{
    float xinc,yinc,dx,dy,len,x,y;
    int i;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>=abs(dy))
        len=abs(dx);
    else
        len=abs(dy);
    x=x1;
    y=y1;
    i=0;
    xinc=dx/len;
    yinc=dy/len;

    while(i<len)
    {
        x=x+xinc;
        y=y+yinc;
        img.setPixel(x,y,c.rgb());
        i++;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start)
    {
        int p= event->pos().x();
        int q= event->pos().y();
        a[ver]=p;
        b[ver]=q;

        if(event->button()==Qt::RightButton)
        {
            dda(a[ver-1],b[ver-1],a[0],b[0]);
            start=false;
        }
        else
        {
            if(ver>0)
            {
                dda(a[ver],b[ver],a[ver-1],b[ver-1]);
            }
        }
        ver++;


    }
}

void MainWindow::on_pushButton_2_clicked()
{
    c= QColorDialog::getColor();
}
