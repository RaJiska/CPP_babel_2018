#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Contact->setEnabled(false);
    QObject::connect(ui->Login, SIGNAL(clicked()), this, SLOT (PressLogin()));
    QObject::connect(ui->Contact, SIGNAL(clicked()), this, SLOT (PressContact()));
}

MainWindow::~MainWindow()
{
    this->server->sendLogoutMsg();
    this->tcpThread->join();
    delete ui;
}

void MainWindow::PressLogin()
{
    this->server = new Server(ui->IpField->text().toStdString(), ui->PortField->text().toInt());
    this->tcpThread = new boost::thread(boost::bind(&Server::run, this->server));
    this->server->sendLoginMsg(ui->LoginField->text().toStdString().substr(0,31));
    ui->Contact->setEnabled(true);
}

void MainWindow::PressContact()
{
    this->server->sendListMsg();
    ui->listWidget->clear();
    for (auto &it : this->server->clientsList)
        ui->listWidget->addItem(QString::fromStdString(it.name));
}