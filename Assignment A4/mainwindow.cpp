#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
QImage img = QImage(500,500,QImage::Format_RGB888);
int re,gr,bl = 255;
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

void MainWindow::bresenham_line(int x1, int y1, int x2, int y2)
{
    int dx,dy,x=x1,y=y1;
    dx=x2-x1;
    dy=y2-y1;
    int s1,s2;
    if(dx>0)
        s1=1;
    else if(dx==0)
        s1=0;
    else
        s1=-1;


    if(dy>0)
        s2=1;
    else if(dy==0)
        s2=0;
    else
        s2=-1;


    if(dx<0)
        dx*=-1;
    if(dy<0)
        dy*=-1;
    int temp,inter;
    if(dy>dx)
    {
        temp=dx;
        dx=dy;
        dy=temp;
        inter=1;
    }
    else
        inter=0;
    int e=2*dy-dx;
    for(int i=0;i<=dx;i++)
    {
        img.setPixel(x,y,qRgb(re,gr,bl));
        while(e>=0)
        {
            if(inter==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-2*dx;
        }
        if(inter==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+2*dy;
    }


          ui->label->setPixmap(QPixmap::fromImage(img));
}


int f = 0;
int a[10];
int b[10];
int i = 0;

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton && f==0){
        a[i] = event->pos().x()-130;
        b[i] = event->pos().y()-20;
        img.setPixel(a[i],b[i],qRgb(re,gr,bl));
        i++;
    }
    if(event->button() == Qt::RightButton){
        f = 1;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_clicked()
{
    for(int j=0;j<i-1;j++){
        bresenham_line(a[j],b[j],a[j+1],b[j+1]);
    }
    bresenham_line(a[0],b[0],a[i-1],b[i-1]);
}


void MainWindow::on_dial_sliderMoved(int position)
{
    re = position;
}


void MainWindow::on_dial_2_sliderMoved(int position)
{
     gr = position;
}

void MainWindow::on_dial_3_sliderMoved(int position)
{
    bl = position;
}
