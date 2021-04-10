#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "math.h"

QImage img(300,300,QImage::Format_RGB888);
float u[10][3];
float translation[3][3];
float scale[3][3];
float rotation[3][3];


int k = 0;
int flag = 0;
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
void MainWindow::drawinitial(){
    for(int i=0;i<k-1;i++){
        dda(int(u[i][0]),int(u[i][1]),int(u[i+1][0]),int(u[i+1][1]));
    }
    dda(u[0][0],u[0][1],u[k-1][0],u[k-1][1]);
    ui->label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::on_pushButton_clicked()
{
    drawinitial();
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton && flag == 0){
        u[k][0] = event->pos().x()+0;
        u[k][1] = event->pos().y()+0;
        u[k][2] = 1;
        img.setPixel(u[k][0],u[k][1],qRgb(255,0,0));
        if(k>=1){
            dda(u[k-1][0],u[k-1][1],u[k][0],u[k][1]);
        }
        ui->label->setPixmap(QPixmap::fromImage(img));
        k++;
    }
    if(event->button() == Qt::RightButton && flag == 0){
        flag = 1;
        dda(u[k-1][0],u[k-1][1],u[0][0],u[0][1]);
        ui->label->setPixmap(QPixmap::fromImage(img));
    }

}

void MainWindow::dda(float x1,float y1,float x2,float y2){
    float dx = (x2 - x1);
    float dy = (y2 - y1);
    float step;
    float x11 = x1;
    float y11 = y1;
    if(abs(dx) > abs(dy)){
        step = abs(dx);
    }
    else{
        step = abs(dy);
    }
    float xinc = dx/step;
    float yinc = dy/step;
    for(int i=0;i<step;i++){
        img.setPixel(int(x11),int(y11),qRgb(255,255,0));
        x11 = x11 + xinc;
        y11 = y11 + yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::intialize(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i!=j){
                translation[i][j] = 0;
                scale[i][j] = 0;
                rotation[i][j] = 0;
            }
            else{
                translation[i][j] = 1;
                scale[i][j] = 1;
                rotation[i][j] = 1;
            }
        }
    }

}
void MainWindow::clearWindow(){
    for(int i=0;i<300;i++){
        for(int j=0;j<300;j++){
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    clearWindow();
    intialize();
    float tx = ui->textEdit->toPlainText().toInt();
    float ty = ui->textEdit_2->toPlainText().toInt();
    translation[2][0] = tx;
    translation[2][1] = ty;
    float res[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res[i][j] = 0;
            for(int l=0;l<3;l++){
                res[i][j]+= u[i][l]*translation[l][j];
            }
        }
    }
    for(int i=0;i<k-1;i++){
        dda(res[i][0],res[i][1],res[i+1][0],res[i+1][1]);
    }
    dda(res[0][0],res[0][1],res[k-1][0],res[k-1][1]);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_3_clicked()
{
    clearWindow();
    intialize();
    translation[2][0] = (-1)*u[0][0];
    translation[2][1] = (-1)*u[0][1];
    float sx = ui->textEdit_3->toPlainText().toFloat();
    float sy = ui->textEdit_4->toPlainText().toFloat();
    scale[0][0] = sx;
    scale[1][1] = sy;

    float res[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            res[i][j] = 0;
            for(int l=0;l<3;l++){
                res[i][j]+= translation[i][l]*scale[l][j];
            }
        }
    }
    translation[2][0] = u[0][0];
    translation[2][1] = u[0][1];
    float res2[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            res2[i][j] = 0;
            for(int l=0;l<3;l++){
                res2[i][j]+= res[i][l]*translation[l][j];
            }
        }
    }

    float res3[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res3[i][j] = 0;
            for(int l=0;l<3;l++){
                res3[i][j]+= u[i][l]*res2[l][j];
            }
        }
    }

    for(int i=0;i<k-1;i++){
        dda(int(res3[i][0]),int(res3[i][1]),int(res3[i+1][0]),int(res3[i+1][1]));
    }
    dda(res3[0][0],res3[0][1],res3[k-1][0],res3[k-1][1]);
    ui->label->setPixmap(QPixmap::fromImage(img));


}

void MainWindow::on_pushButton_4_clicked()
{
    intialize();
    clearWindow();
    float angle = ui->textEdit_5->toPlainText().toFloat();
    angle = ((angle/180)*22)/7;
    float sinth = sin(angle);
    float costh = cos(angle);
    rotation[0][0] = costh;
    rotation[0][1] = sinth;
    rotation[1][0] = (-1)*sinth;
    rotation[1][1] = costh;


    translation[2][0] = (-1)*u[0][0];
    translation[2][1] = (-1)*u[0][1];

    float res[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            res[i][j] = 0;
            for(int l=0;l<3;l++){
                res[i][j]+= translation[i][l]*rotation[l][j];
            }
        }
    }


    translation[2][0] = u[0][0];
    translation[2][1] = u[0][1];
    float res2[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            res2[i][j] = 0;
            for(int l=0;l<3;l++){
                res2[i][j]+= res[i][l]*translation[l][j];
            }
        }
    }


    float res3[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res3[i][j] = 0;
            for(int l=0;l<3;l++){
                res3[i][j]+= u[i][l]*res2[l][j];
            }
        }
    }

    for(int i=0;i<k-1;i++){
        dda(int(res3[i][0]),int(res3[i][1]),int(res3[i+1][0]),int(res3[i+1][1]));
    }
    dda(res3[0][0],res3[0][1],res3[k-1][0],res3[k-1][1]);
    ui->label->setPixmap(QPixmap::fromImage(img));


}
