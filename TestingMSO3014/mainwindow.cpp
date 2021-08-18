#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    ViSession rm= VI_NULL, vi= VI_NULL; //rm = resource manager (for finding resources and opening them)
    ViStatus status;
    ViChar buffer[256];
    ViUInt32 retCnt;

    //open default session
    status = viOpenDefaultRM(&rm);//access to default resource manager
    if(status< VI_SUCCESS) goto ERROR_CLEANUP; //if not success

    //open USB Port using Vendor id, model id, serial no
    status = viOpen(rm, "USB::1689::1057::C010783::INSTR ", VI_NULL,VI_NULL, &vi); //USBTMC config
    if(status< VI_SUCCESS) goto ERROR_CLEANUP;

    //send *IDN? query
    status = viWrite( vi , (ViBuf)"*idn?" , 5 , &retCnt ); //identify
    if(status< VI_SUCCESS) goto ERROR_CLEANUP;

    //clean buffer and read response
    memset(buffer,0, sizeof(buffer));
    status = viRead( vi, (ViBuf)buffer , sizeof(buffer) , &retCnt );
    if(status< VI_SUCCESS) goto ERROR_CLEANUP;

    //print response
    qDebug() << "id: " <<buffer;

    //clean up
    viClose(vi);
    viClose(rm);

ERROR_CLEANUP:

    viStatusDesc(vi,status,buffer);
    qDebug() << "Error: " << buffer;
    if (rm!= VI_NULL)
    {
        viClose(rm);
    }
}

