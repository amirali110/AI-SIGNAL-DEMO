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
    int num=0;
    int raw=0;
    int line=0;

    QVector<QVector<QString>> PROFIT;

    double sum_profits;


public:

    MainWindow(QWidget *parent = nullptr);



    ~MainWindow();

private slots:
    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
