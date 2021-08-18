#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//install tekVisa
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"
#include "memory.h"
#include "stdio.h"
#include <QDebug>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
