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

    this->udpServer = new ServerVoice(2222);
    this->udpServer->setReadCallback(std::bind(&MainWindow::receiveVoice, this, std::placeholders::_1, std::placeholders::_2));
    this->udpServerThread = new boost::thread(boost::bind(&IVoiceStream::start, this->udpServer));
    this->udpClient = new ClientVoice();
    this->udpClient->setReadCallback(std::bind(&MainWindow::receiveVoice, this, std::placeholders::_1, std::placeholders::_2));
    this->udpClientThread = new boost::thread(boost::bind(&IVoiceStream::start, this->udpClient));
}

MainWindow::~MainWindow()
{
    if (this->server != nullptr) {
        this->server->sendLogoutMsg();
        this->server->io_service.stop();
        this->tcpThread->join();
        if (this->udpServer != nullptr) {
            this->udpServer->disconnect();
            this->udpServerThread->join();
        }
        if (this->udpClient != nullptr) {
            this->udpClient->disconnect();
            this->udpClientThread->join();
        }
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
        std::cout << "Der" << std::endl;
    }
    ui->Contact->setEnabled(true);
    ui->Login->setEnabled(false);
}

void MainWindow::PressContact()
{
    if (!ui->ContactField->text().toStdString().empty())
        this->server->sendQueryMsg(ui->ContactField->text().toStdString().substr(0,31));
}

void MainWindow::sendVoice(IVoiceStream *remote)
{
	es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
    remote->writeData(ss.getReadBuffer(), ss.getReadBufferSize());
}

void MainWindow::receiveVoice(unsigned char* buff, int size)
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
            this->onCall = true;
            this->call(this->udpServer);
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
    //this->target = msg.getHeader().from;
    this->udpClient->connect(std::string(msg.address), 2222);
    this->udpClient->start();
	this->onCall = true;
    this->call(this->udpServer);
}

void MainWindow::handleHangup()
{
    this->target = 0;
	this->onCall = false;
	ui->Call->setEnabled(true);
	ui->Hangup->setEnabled(false);
    //this->server->sendHangupMsg();
    this->udpClient->disconnect();
}

void MainWindow::call(IVoiceStream *remote)
{
    while (this->onCall) {
        sendVoice(remote);
    }
}