#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bits/stdc++.h"
    QImage image( 300, 300,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::clearimage()
{
    for(int i=0;i<=300;i++)
    {
        for(int j=0;j<=300;j++)
            image.setPixel(i,j,qRgb(0,0,0));
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{

        clearimage();
        float x1= (ui->textEdit->toPlainText()).toFloat();
        float y1= (ui->textEdit_2->toPlainText()).toFloat();
        float x2= (ui->textEdit_3->toPlainText()).toFloat();
        float y2= (ui->textEdit_4->toPlainText()).toFloat();
        float dx=x2-x1;
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

void MainWindow::on_pushButton_4_clicked()
{
    clearimage();
    float x1= (ui->textEdit->toPlainText()).toFloat();
    float y1= (ui->textEdit_2->toPlainText()).toFloat();
    float x2= (ui->textEdit_3->toPlainText()).toFloat();
    float y2= (ui->textEdit_4->toPlainText()).toFloat();
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
        if(i%9<5)
            image.setPixel((int)x1,(int)y1,qRgb(0,255,255));
        x1=x1+xi;
        y1=y1+yi;
     }
     ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
    clearimage();
    float x1= (ui->textEdit->toPlainText()).toFloat();
    float y1= (ui->textEdit_2->toPlainText()).toFloat();
    float x2= (ui->textEdit_3->toPlainText()).toFloat();
    float y2= (ui->textEdit_4->toPlainText()).toFloat();
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
        if(i%2==0)
        image.setPixel((int)x1,(int)y1,qRgb(0,255,255));
        x1=x1+xi;
        y1=y1+yi;
     }
     ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    clearimage();
    float x1= (ui->textEdit->toPlainText()).toFloat();
    float y1= (ui->textEdit_2->toPlainText()).toFloat();
    float x2= (ui->textEdit_3->toPlainText()).toFloat();
    float y2= (ui->textEdit_4->toPlainText()).toFloat();
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
    {   if(i%10<5)
        {
            image.setPixel((int)x1,(int)y1,qRgb(0,255,255));
        }
        if(i%10==7)
        {
            image.setPixel((int)x1,(int)y1,qRgb(0,255,255));
        }
        x1=x1+xi;
        y1=y1+yi;
     }
     ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_5_clicked()
{

        clearimage();
        float x1 = (ui->textEdit->toPlainText()).toFloat();
        float y1 = (ui->textEdit_2->toPlainText()).toFloat();
        float x2 = (ui->textEdit_3->toPlainText()).toFloat();
        float y2 = (ui->textEdit_4->toPlainText()).toFloat();
        int w = (ui->textEdit_5->toPlainText()).toInt();
        int step;
        if(abs(y2-y1)>abs(x2-x1)){
            step = abs(y2-y1);
        }
        else{
            step = abs(x2-x1);
        }
        float xinc = abs(x2-x1)/step;
        float yinc = abs(y2-y1)/step;
        if(abs(y2-y1)>abs(x2-x1)){
            for(int j=y1;j<=y2;j++){
                for(int i=0;i<w/2;i++){
                    image.setPixel(int(x1-i),int(j),qRgb(0,255,255));
                    image.setPixel(int(x1+i),int(j),qRgb(0,255,255));
                }
                x1 = x1 + xinc;
                y1 = y1 + yinc;
            }
        }
        else{
            for(int j=x1;j<=x2;j++){
                for(int i=0;i<w/2;i++){
                    image.setPixel(int(j),int(y1-i),qRgb(0,255,255));
                    image.setPixel(int(j),int(y1+i),qRgb(0,255,255));
                }
                x1 = x1 + xinc;
                y1 = y1 + yinc;
            }
        }
         ui->label->setPixmap(QPixmap::fromImage(image));
}
