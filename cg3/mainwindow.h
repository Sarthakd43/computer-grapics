#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>

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
    void on_pushButton_2_clicked();
    void dda(int x1, int y1, int x2, int y2, int line_depth=1);
    void mousePressEvent(QMouseEvent *event);
    int getcode(int x, int y);
    void cohen_sutherland_clip(float x1,float y1,float x2, float y2);
    void on_pushButton_clicked();
    void eraseall();
    void polygon();

private:
    Ui::MainWindow *ui;
    int ver, a[20], b[20];
    bool start, line;
    int x_min, x_max, y_min, y_max;
    int LEFT, RIGHT, TOP, BOT, IN;
    QRgb global_color;
};
#endif // MAINWINDOW_H
