#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "math.h"

QImage img(500,500,QImage::Format_RGB888);
float a[20][3];
float reflect[3][3];
float translate[3][3];
float rotate[3][3];
int k = 0;
int flag = 0;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dda(250,0,250,500);
    dda(0,250,500,250);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && flag == 0){
        a[k][0] = event->pos().x() ;
        a[k][1] = event->pos().y() ;
        a[k][2] = 1;
        if(k>=1){
            dda(a[k][0],a[k][1],a[k-1][0],a[k-1][1]);
        }
        k++;
    }
    else if(event->button() == Qt::RightButton && flag ==0){
        flag = 1;
        dda(a[k-1][0],a[k-1][1],a[0][0],a[0][1]);
    }

}

void MainWindow::dda(float x1,float y1,float x2,float y2){
    float dy = y2-y1;
    float dx = x2-x1;
    float step;
    if(abs(dx)>abs(dy)){
        step = abs(dx);
    }
    else{
        step = abs(dy);
    }
    float xinc = dx/step;
    float yinc = dy/step;
    for(int i=0;i<step;i++){
        img.setPixel(x1,y1,qRgb(255,0,255));
        x1 = x1 + xinc;
        y1 = y1 + yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::initialize(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            reflect[i][j] = 0;
            translate[i][j] = 0;
            rotate[i][j] = 0;
            if(i==j){
                translate[i][j] = 1;
                rotate[i][j] = 1;
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    initialize();
    reflect[0][0] = 1;
    reflect[1][1] = -1;
    reflect[2][2] = 1;

    translate[2][0] = -250;
    translate[2][1] = 0;

    float res[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res[i][j] = 0;
            for(int l = 0;l<3;l++){
                res[i][j] += a[i][l]*translate[l][j];
            }
        }
    }

    float res2[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res2[i][j] = 0;
            for(int l = 0;l<3;l++){
                res2[i][j] += res[i][l]*reflect[l][j];
            }
        }
    }
    translate[2][0] = 250;
    translate[2][1] = 0;
    float res1[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res1[i][j] = 0;
            for(int l = 0;l<3;l++){
                res1[i][j] += res2[i][l]*translate[l][j];
            }
        }
    }
    for(int i=0;i<k-1;i++){
        dda(res1[i][0],500+res1[i][1],res1[i+1][0],500+res1[i+1][1]);
    }
    dda(res1[k-1][0],500+res1[k-1][1],res1[0][0],500+res1[0][1]);
}



void MainWindow::on_pushButton_2_clicked()
{
    initialize();
    reflect[0][0] = -1;
    reflect[1][1] = 1;
    reflect[2][2] = 1;

    translate[2][0] = 0;
    translate[2][1] = -250;

    float res[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res[i][j] = 0;
            for(int l = 0;l<3;l++){
                res[i][j] += a[i][l]*translate[l][j];
            }
        }
    }

    float res2[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res2[i][j] = 0;
            for(int l = 0;l<3;l++){
                res2[i][j] += res[i][l]*reflect[l][j];
            }
        }
    }
    translate[2][0] = 0;
    translate[2][1] = 250;
    float res1[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res1[i][j] = 0;
            for(int l = 0;l<3;l++){
                res1[i][j] += res2[i][l]*translate[l][j];
            }
        }
    }
    for(int i=0;i<k-1;i++){
        dda(500+res1[i][0],res1[i][1],500+res1[i+1][0],res1[i+1][1]);
    }
    dda(500+res1[k-1][0],res1[k-1][1],500+res1[0][0],res1[0][1]);
}




void MainWindow::on_pushButton_3_clicked()
{
    initialize();
 /*   float b[k][3];
    for(int i=0;i<k;i++){
        b[i][0] = a[i][0]-250;
        b[i][1] = 250 - a[i][1];
        b[i][2] = 1;
    }
    rotate[0][1] = 1;
    rotate[1][0] = 1;
    rotate[2][2] = 1;
    float res5[k][3];
    for(int i=0;i<k;i++){
        for(int j=0;j<3;j++){
            res5[i][j] = 0;
            for(int l=0;l<3;l++){
                res5[i][j] += b[i][l]*rotate[l][j];
            }
        }
    }
*/

    for(int i=0;i<k-1;i++){
        dda(500-a[i][1],500-a[i][0],500-a[i+1][1],500-a[i+1][0]);
    }
    dda(500-a[k-1][1],500-a[k-1][0],500-a[0][1],500-a[0][0]);
}
