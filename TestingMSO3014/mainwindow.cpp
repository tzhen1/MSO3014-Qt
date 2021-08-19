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
    bool Mso3014Active= false;
    ViSession rm= VI_NULL, vi= VI_NULL; //rm=resource manager,vi=visa, MSO (finding resources and opening them)
    ViStatus Status;
    ViChar buffer[256]; // holds responses from I/O (write/read)
    ViUInt32 retCnt;

    //open default session
    Status = viOpenDefaultRM(&rm);//access to default resource manager
    if(Status< VI_SUCCESS) goto ERROR_CLEANUP; //if not success

    //open USB Port using Vendor id, model id, serial no
    Status = viOpen(rm, "USB::1689::1057::C010783::INSTR ", VI_NULL,VI_NULL, &vi); //USBTMC config
    if(Status< VI_SUCCESS) goto ERROR_CLEANUP;

    //Clean and reset
    Status = viWrite( vi , (ViBuf)"*CLS;*OPC" , 9 , &retCnt );
    if(Status< VI_SUCCESS) goto ERROR_CLEANUP;

    Status =  viWrite( vi , (ViBuf)"*RST;*OPC" , 9 , &retCnt );
    if(Status< VI_SUCCESS) goto ERROR_CLEANUP;
    else{ qDebug() << "Scope INIT"; }

    Mso3014Active= true;

    //send *IDN? query
    Status = viWrite( vi , (ViBuf)"*idn?" , 5 , &retCnt ); //identify
    if(Status< VI_SUCCESS) goto ERROR_CLEANUP;

//    //Auto setup
//    Status = viWrite( vi , (ViBuf)"AUTOS EXEC;*OPC?" , 16 , &retCnt ); //identify
//    if(Status< VI_SUCCESS) goto ERROR_CLEANUP;
//    else{ qDebug() << "Scope autoset"; }

    //clean buffer and read response
    memset(buffer,0, sizeof(buffer));
    Status = viRead( vi, (ViBuf)buffer , sizeof(buffer) , &retCnt );
    if(Status< VI_SUCCESS) goto ERROR_CLEANUP;

    //print response
    qDebug() << "id: " <<buffer;

    //clean up
    viClose(vi);
    viClose(rm);

ERROR_CLEANUP:

    viStatusDesc(vi,Status,buffer);
    qDebug() << "Status: " << buffer;
    if (rm!= VI_NULL)
    {
        viClose(rm);
    }
}

