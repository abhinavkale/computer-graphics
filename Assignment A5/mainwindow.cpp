#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include<QDebug>

QImage img(500,500,QImage::Format_RGB888);
QImage img2(500,500,QImage::Format_RGB888);
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

float u[4][3];
float v[4][3];
 float rotate[3][3];
int k = 0;
float a;
void MainWindow::on_pushButton_clicked()
{


     a = ui->textEdit->toPlainText().toFloat();

    u[k][0] = 250-a/sqrt(2);
    u[k++][1] = 250;
    u[k][0] = 250;
    u[k++][1] = 250-a/sqrt(2);
    u[k][0] = 250+a/sqrt(2);
    u[k++][1] = 250;
    u[k][0] = 250;
    u[k++][1] = 250+a/sqrt(2);
    for(int i=0;i<4;i++){
        u[i][2] = 1;
    }


    drawchessboard();

    ui->label->setPixmap(QPixmap::fromImage(img));

}
void MainWindow::drawchessboard(){

    for(int i=0;i<5;i++){
        bres(u[0][0]+(i*a)/(4*sqrt(2)),u[0][1]+(i*a)/(4*sqrt(2)),u[1][0]+(i*a)/(4*sqrt(2)),u[1][1]+(i*a)/(4*sqrt(2)));
    }
    for(int i=0;i<5;i++){
        bres(u[1][0]-i*a/(4*sqrt(2)),u[1][1]+i*a/(4*sqrt(2)),u[2][0]-i*a/(4*sqrt(2)),u[2][1]+i*a/(4*sqrt(2)));
    }
    seedfill(250,250-a/(4*sqrt(2)));
    seedfill(250,250+a/(4*sqrt(2)));
    seedfill(250,250+3*a/(4*sqrt(2)));
    seedfill(250,250-3*a/(4*sqrt(2)));
    seedfill(250+a/(2*sqrt(2)),250+a/(4*sqrt(2)));
    seedfill(250-a/(2*sqrt(2)),250+a/(4*sqrt(2)));
    seedfill(250+a/(2*sqrt(2)),250-a/(4*sqrt(2)));
    seedfill(250-a/(2*sqrt(2)),250-a/(4*sqrt(2)));
    qDebug()<<250+a/8<<" "<<250+3*a/8;

}

void MainWindow::bres(float x1,float y1,float x2,float y2){
    float dx = x2-x1;
    float dy = y2-y1;
    float interchange;
    float s1,s2;
    if(dx<0){
        s1 = -1;
     }
    else if(dx == 0){
        s1 = 0;
    }
    else{
        s1 = 1;
    }
    if(dy<0){
        s2 = -1;
    }
    else if(dy == 0){
        s2 = 0;
    }
    else{
        s2 = 1;
    }
    dx = abs(dx);
    dy = abs(dy);
    if(dy > dx){
        float temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }
    else{
        interchange = 0;
    }
    float p = 2*dy-dx;
    for(int i=0;i<dx;i++){
        img.setPixel(x1,y1,qRgb(123,123,123));
        while(p>=0){
            if(interchange == 1){
                x1 = x1 + s1;
            }
            else{
                y1 = y1 + s2;
            }
            p = p - 2*dx;
        }
        if(interchange == 1){
            y1 = y1 + s2;
        }
        else{
            x1 = x1 + s1;
        }
        p = p + 2*dy;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::seedfill(float x1,float y1){
    if(img.pixel(x1,y1) == qRgb(0,0,0)){
        img.setPixel(x1,y1,qRgb(255,255,255));
        seedfill(x1+1,y1);
        seedfill(x1-1,y1);
        seedfill(x1,y1+1);
        seedfill(x1,y1-1);
    }
}

















