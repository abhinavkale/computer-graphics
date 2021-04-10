#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<string.h>
#include<QThread>
  QImage image( 900, 900,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Bresenham(int x1,int y1,int x2,int y2)
{
    int x=x1;
    int y=y1;
    int dx=x2-x1;
    int dy=y2-y1;
    int p=2*dy-dx;
    while(x<=x2)
    {
        image.setPixel(x,y,qRgb(0,255,255));
        x++;
        if(p<0)
        {
            p=p+2*dy;
        }
        else
        {
            p=p+2*dy-2*dx;
            y++;
        }
    }
    while(x>x2)
    {
        image.setPixel(x,y,qRgb(0,255,255));
        x--;
        if(p<0)
        {
            p=p+2*dy;
        }
        else
        {
            p=p+2*dy-2*dx;
            y++;
        }
    }
}
void MainWindow::DDA(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1;
    int step,yi,xi;
    int dy=y2-y1;
    if(abs(dx)>abs(dy))
        step=abs(dx);
    else
        step=abs(dy);
     yi=dy/step;
     xi= dx/step;
    for(int i=0;i<=step;i++)
    {
        image.setPixel((int)x1,(int)y1,qRgb(0,255,255));
        x1=x1+xi;
        y1=y1+yi;
     }
}
void MainWindow::on_pushButton_clicked()
{


   int l= (ui->plainTextEdit->toPlainText()).toInt();
   int b = l;

    DDA(100,200,100+b,200);
    DDA(100,200,100,l+200);
    DDA(b+100,200,b+100,l+200);
    DDA(100,l+200,b+100,l+200);
    Bresenham(100+b/2,200,100,200+l/2);
    Bresenham(100+b/2,200,100+b,200+l/2);
    Bresenham(100,200+l/2,100+b/2,200+l);
    Bresenham(100+b,200+l/2,100+b/2,200+l);
    DDA(100+b/4,200+l/4,100+3*(b/4),200+l/4);
    DDA(100+b/4,200+l/4,100+b/4,200+3*(l/4));
    DDA(100+3*(b/4),200+l/4,100+3*(b/4),200+3*(l/4));
    DDA(100+b/4,200+3*(l/4),100+3*(b/4),200+3*(l/4));
    ui->label->setPixmap(QPixmap::fromImage(image));
}
