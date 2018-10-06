#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->Login, SIGNAL(clicked()), this, SLOT (PressLogin()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PressLogin()
{
    this->server = new Server(ui->IpField->text().toStdString(), ui->PortField->text().toInt());
    this->server->sendLoginMsg(ui->LoginField->text().toStdString().substr(0,31));
}