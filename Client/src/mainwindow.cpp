#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->server = new Server("127.0.0.1", 1111);
    ui->setupUi(this);
    QObject::connect(ui->Login, SIGNAL(clicked()), this, SLOT (PressLogin()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PressLogin()
{
    this->server->sendLoginMsg(ui->LoginField->text().toStdString().substr(0,31));
}