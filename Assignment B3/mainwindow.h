#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent*);
    void Bres(int x1,int y1,int x2,int y2,QImage &);
    void clip(int x1,int y1,int x2,int y2);
    void startClip();
    int value(int x1,int y1);
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
