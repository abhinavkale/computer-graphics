#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
QImage image(300,300,(QImage::Format_RGB888));
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
void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    int dx=x2-x1;
    float step,yi,xi;
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
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::draw(int x,int y,int xc,int yc)
{
    image.setPixel(xc+x,yc+y,qRgb(0,255,255));
    image.setPixel(xc+y,yc+x,qRgb(0,255,255));
    image.setPixel(xc+y,yc-x,qRgb(0,255,255));
    image.setPixel(xc+x,yc-y,qRgb(0,255,255));
    image.setPixel(xc-x,yc-y,qRgb(0,255,255));
    image.setPixel(xc-y,yc-x,qRgb(0,255,255));
    image.setPixel(xc-y,yc+x,qRgb(0,255,255));
    image.setPixel(xc-x,yc+y,qRgb(0,255,255));
}
void MainWindow::circleBres(int xc,int yc,int r)
{
    int x=0,y=r;
    int d=3-2*r;
    draw(x,y,xc,yc);
    while(y>=x)
    {

        if(d>0)
        {
            d=d+4*(x-y)+10;
            y--;
        }
        else
              d=d+4*x+6;
        x++;
        draw(x,y,xc,yc);
    }
}
void MainWindow::circleDDA(int xc,int yc,int r)
{
      float xc1,xc2,yc1,yc2,eps,sx,sy;
      int val,i;
      xc1=r;
      yc1=0;
      sx=xc1;
      sy=yc1;
      i=0;
      do{
          val=pow(2,i);
          i++;
          }while(val<r);
      eps = 1/pow(2,i-1);
      do{

          xc2 = xc1 + yc1*eps;
          yc2 = yc1 - eps*xc2;
          image.setPixel(xc+xc2,yc-yc2,qRgb(0,255,255));
          xc1=xc2;
          yc1=yc2;
         }while((yc1-sy)<eps || (sx-xc1)>eps);
}
void MainWindow::on_pushButton_clicked()
{
    int xc=(ui->textEdit_2->toPlainText()).toInt();
    int yc=(ui->textEdit->toPlainText()).toInt();
    int r=(ui->textEdit_3->toPlainText()).toInt();
    circleBres(xc,yc,r);
    float x1,y1,x2,y2,x3,y3;
    x1=xc;
    y1=yc-r;
    x2=xc+r*0.866;
    y2=yc+r*0.5;
    x3=xc-r*0.866;
    y3=yc+r*0.5;
    dda(x1,y1,x2,y2);
    dda(x2,y2,x3,y3);
    dda(x3,y3,x1,y1);
    circleDDA(xc,yc,r/2);
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<300;i++)
    {
        for(int j=0;j<300;j++)
            image.setPixel(i,j,qRgb(0,0,0));
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
