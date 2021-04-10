#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage img(500,500,QImage::Format_RGB888);
  float a=200,b=200;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


     ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     hilbert(1,2,3,4,1,10,a,b);
}

void MainWindow :: hilbert(float r, float d, float l, float u, float i, float h, float &x, float &y)
{
    if(i>0)
    {
        i--;
        hilbert(d,r,u,l,i,h,x,y);   //will draw 3 sided rect
        //pr+=2;
        move(r,h,x,y);      //shift it
        hilbert(r,d,l,u,i,h,x,y);
        //pg+=2;
        move(d,h,x,y);
        hilbert(r,d,l,u,i,h,x,y);
        //pb+=2;
        move(l,h,x,y);
        hilbert(u,l,d,r,i,h,x,y);   //calling hilbert recursively
    }
}
void MainWindow::move(float j,float h,float &x,float &y){
    float x1 = x,y1 = y;
      switch((int)j){
        case 1: y -= h;
                break;
        case 2: x += h;
                break;
        case 3: y += h;
                break;
        case 4: x -= h;
                break;
      }
      dda(x1,y1,x,y);
}


void MainWindow::dda(float x1,float y1, float x2, float y2){
    float dx = x2 - x1;
    float dy = y2-y1;
    float step;
    if(abs(dy) > abs(dx)){
        step = abs(dy);
    }
    else{
        step = abs(dx);
    }
    float xinc = dx/step;
    float yinc = dy/step;
    for(int i=0;i<step;i++){
        img.setPixel(x1,y1,qRgb(255,0,0));
        x1 = x1 + xinc;
        y1 = y1 + yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_2_clicked()
{
     hilbert(1,2,3,4,2,10,a,b);
}

void MainWindow::on_pushButton_3_clicked()
{
     hilbert(1,2,3,4,3,10,a,b);
}
