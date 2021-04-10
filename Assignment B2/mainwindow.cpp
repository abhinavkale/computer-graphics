#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "math.h"

QRgb q;
int re = 123,gr=123,bl=123;

QImage img = QImage(700,700,QImage::Format_RGB888);
QRgb col = qRgb(255,255,0);
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
int a[10];
int b[10];
int i=0;
int flag = 0;

void MainWindow::mousePressEvent(QMouseEvent* ev){
    if(ev->button() == Qt::LeftButton && flag == 0){
        a[i] = ev->pos().x() - 160;
        b[i] = ev->pos().y() + 80;
        img.setPixel(a[i],b[i],col);
        i++;
    }
    if(ev->button() == Qt::RightButton){
        flag = 1;
        int m = ev->pos().x() - 160;
        int n = ev->pos().y() + 80;
        q = img.pixel(m,n);
        seedfill(m,n);
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_clicked()
{
    for(int j=0;j<i-1;j++){
        dda(a[j],b[j],a[j+1],b[j+1]);
    }
    dda(a[0],b[0],a[i-1],b[i-1]);
}

void MainWindow::dda(int x1,int y1,int x2,int y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps ;
    if(abs(dx) > abs(dy)){
        steps = abs(dx);
    }
    else{
        steps = abs(dy);
    }
    float xinc = dx/steps;
    float yinc = dy/steps;
    float k = x1;
    float l = y1;
    for(int j=0;j<steps;j++){
        img.setPixel(floor(k),floor(l),col);
        k = k + xinc;
        l = l + yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::seedfill(int xi,int yi){

    if(q == img.pixel(xi,yi) ){
        img.setPixel(xi,yi,qRgb(re,gr,bl));
        seedfill(xi+1,yi);
        seedfill(xi,yi+1);
        seedfill(xi-1,yi);
        seedfill(xi,yi-1);
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    re = ui->horizontalSlider->value();
    gr = ui->horizontalSlider_2->value();
    bl = ui->horizontalSlider_3->value();
}
