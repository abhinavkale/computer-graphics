#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent *);
    void bresenham_line(int,int,int,int);

    void on_dial_sliderMoved(int position);

    void on_dial_2_sliderMoved(int position);

    void on_dial_3_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
