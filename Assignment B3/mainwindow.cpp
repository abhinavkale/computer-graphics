#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"


int INSIDE = 0;
int LEFT = 1;
int RIGHT = 2;
int BOTTOM = 4;
int TOP = 8;
QImage img1 = QImage(700,700,QImage::Format_RGB888);
QImage img2 = QImage(700,700,QImage::Format_RGB888);

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

void MainWindow::on_pushButton_clicked()
{
    ui->label->setPixmap(QPixmap::fromImage(img1));
}

int a[10],b[10];
int u[2],v[2];
int i=0;
int h=0;
int flag = 0;
QRgb q = qRgb(255,255,255);

void MainWindow::mousePressEvent(QMouseEvent* ev){
       if(ev->button() == Qt::LeftButton && flag == 0){
            a[i] = ev->pos().x() - 10;
            b[i] = ev->pos().y() + 200;
            img1.setPixel(a[i],b[i],q);
            if(i%2 == 1){
                Bres(a[i-1],b[i-1],a[i],b[i],img1);
            }
            i++;
            ui->label->setPixmap(QPixmap::fromImage(img1));
       }
       if(flag == 1){
            u[h] = ev->pos().x() - 10;
            v[h] = ev->pos().y() + 200;
            h++;
            img1.setPixel(u[h-1],v[h-1],q);
            if(h==2){
                Bres(u[0],v[0],u[0],v[1],img1);
                Bres(u[0],v[1],u[1],v[1],img1);
                Bres(u[1],v[1],u[1],v[0],img1);
                Bres(u[1],v[0],u[0],v[0],img1);
            }
            ui->label->setPixmap(QPixmap::fromImage(img1));
       }
       if(ev->button() == Qt::RightButton && flag==0){
           flag = 1;
       }

}


void MainWindow::Bres(int x1, int y1, int x2, int y2,QImage& img)
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
        img.setPixel(x,y,q);
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

void MainWindow::on_pushButton_2_clicked()
{
    startClip();
}
void MainWindow::startClip(){
    for(int l=0;l<i;l+=2){
        clip(a[l],b[l],a[l+1],b[l+1]);
    }
}
int MainWindow::value(int x1,int y1){
    int code = INSIDE;
    if(x1 < u[0]){
        code = code | LEFT;
    }
    else if(x1 > u[1]){
        code = code | RIGHT;
    }
    if(y1 < v[0]){
        code = code | BOTTOM;
    }
    else if(y1 > v[1]){
        code = code | TOP;
    }
    return code;
}

void MainWindow::clip(int x1,int y1, int x2, int y2){
    int q1 = value(x1,y1);
    int q2 = value(x2,y2);

    while(true){
        if(q1 == 0 && q2 == 0){
            Bres(x1,y1,x2,y2,img2);
            break;
        }
        else if(q1 & q2){
            break;
        }
        else{
            int code_out;
            float a,b;
            if(q1 != 0){
                code_out = q1;
            }
            else{
               code_out = q2;
            }
            if(code_out & TOP){
                b = v[1];
                a = x1 + ((v[1]-y1)*(x2-x1))/(y2-y1);
            }
            else if(code_out & BOTTOM){
                b = v[0];
                a = x1+ ((v[0]-y1)*(x2-x1))/(y2-y1);
            }
            else if(code_out & LEFT){
                a = u[0];
                b = y1 +  ((y2-y1)*(u[0]-x1))/(x2-x1);
            }
            else if(code_out & RIGHT){
                a = u[1];
                b = y1 + ((y2-y1)*(u[1]-x1))/(x2-x1);
            }

            if(code_out == q1){
                x1 = a;
                y1 = b;
                q1 = value(x1,y1);
            }
            else{
                x2 = a;
                y2 = b;
                q2 = value(x2,y2);
            }
        }
    }

    Bres(u[0],v[0],u[0],v[1],img2);
    Bres(u[0],v[1],u[1],v[1],img2);
    Bres(u[1],v[1],u[1],v[0],img2);
    Bres(u[1],v[0],u[0],v[0],img2);
}
