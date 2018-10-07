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
    ui->Hangup->setEnabled(false);
    this->server = nullptr;
    QObject::connect(ui->Login, SIGNAL(clicked()), this, SLOT (PressLogin()));
    QObject::connect(ui->Contact, SIGNAL(clicked()), this, SLOT (PressContact()));
    QObject::connect(ui->Hangup, SIGNAL(clicked()), this, SLOT (PressHangup()));
    QObject::connect(ui->Call, SIGNAL(clicked()), this, SLOT (PressCall()));
}

MainWindow::~MainWindow()
{
    if (this->server != nullptr) {
	this->server->io_service.stop();
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
    if (!ui->ContactField->text().toStdString().empty())
        this->server->sendQueryMsg(ui->ContactField->text().toStdString());
}

unsigned char *MainWindow::sendVoice()
{
	es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
	return(ss.getReadBuffer());
}

void MainWindow::recieveVoice(unsigned char* buff, int size)
{
	es.decode(buff, size);
	ss.readFromStream(buff);
}

void MainWindow::PressHangup()
{
    this->onCall = false;
    ui->Call->setEnabled(true);
    ui->Hangup->setEnabled(false);
}

void MainWindow::PressCall()
{
    	QList <QListWidgetItem *> list = ui->listWidget->selectedItems();
	for (auto a : this->clientsList) {
		if (std::string(a.name) == list[0]->text().toStdString()) {
			this->server->sendCallMsg(a.id);
			ui->Hangup->setEnabled(true);
			ui->Call->setEnabled(false);
		}
	}

}

void MainWindow::handleContact(NetworkMessage::MsgQuery &msg)
{
	for (auto a : this->clientsList) {
		if (std::string(a.name) == msg.name && a.id == msg.id)
			return ;
	}
	this->clientsList.push_back(msg);
	ui->listWidget->addItem(QString::fromStdString(std::string(msg.name)));
}

void MainWindow::handleCall(NetworkMessage::MsgCall &msg)
{
	strcpy(this->target, msg.address);
	this->onCall = true;
}

void MainWindow::handleHangup()
{
	this->onCall = false;
	ui->Call->setEnabled(true);
	ui->Hangup->setEnabled(false);
}