#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    es.encoderCreate();
    es.decoderCreate();
    ss.initPa();
	ss.initParams();
	ss.initStream();
    ui->setupUi(this);
    ui->Contact->setEnabled(false);
    ui->listWidget->clear();
    this->server = nullptr;
    QObject::connect(ui->Login, SIGNAL(clicked()), this, SLOT (PressLogin()));
    QObject::connect(ui->Contact, SIGNAL(clicked()), this, SLOT (PressContact()));
    QObject::connect(ui->HangOut, SIGNAL(clicked()), this, SLOT (PressHangOut()));
    QObject::connect(ui->Call, SIGNAL(clicked()), this, SLOT (PressCall()));
}

MainWindow::~MainWindow()
{
    if (this->server != nullptr) {
        this->tcpThread->join();
        this->server->sendLogoutMsg();
    }
    delete ui;
}

void MainWindow::PressLogin()
{
    if (ui->LoginField->text().toStdString().empty() || ui->IpField->text().toStdString().empty() || ui->PortField->text().toStdString().empty())
        return;
    try {
    this->server = new Server(ui->IpField->text().toStdString(), ui->PortField->text().toInt(), *this);
    this->tcpThread = new boost::thread(boost::bind(&Server::run, this->server));
    this->server->sendLoginMsg(ui->LoginField->text().toStdString().substr(0,31));
    }
    catch (const std::exception& e) {
    }
    ui->Contact->setEnabled(true);
    ui->Login->setEnabled(false);
}

void MainWindow::PressContact()
{
    //this->server->sendListMsg();
    if (!ui->ContactField->text().toStdString().empty())
        ui->listWidget->addItem(QString::fromStdString(ui->ContactField->text().toStdString()));
}

void MainWindow::sendVoice()
{
	//while (this->onCall) {
		es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
        //sendVoicmsg
		ss.writeOnStream(ss.getReadBuffer());
	//}
}

void MainWindow::recieveVoice(unsigned char* buff, int size)
{
		es.decode(buff, size);
		ss.readFromStream(buff);

}

void MainWindow::PressHangOut()
{
    this->onCall = false;
}

void MainWindow::PressCall()
{
    //if ()
    //ui->listWidget->
}

void MainWindow::handleContact(NetworkMessage::MsgQuery &msg)
{
	this->clientsList.push_back(msg);
	ui->listWidget->addItem(QString::fromStdString(std::string(msg.name)));
}