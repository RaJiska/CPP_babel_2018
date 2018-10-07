#include "mainwindow.h"

void print_hexa(unsigned char *a, size_t bytes, int type)
{
    printf(((type) ? "RECEIVE: \n" : "SEND: \n"));
    for (int it = 0; it < bytes; ++it)
        printf("%02X ", a + it);
    printf("\n");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if (!es.encoderCreate() || !es.decoderCreate() || !ss.initPa() || !ss.initParams() ||	!ss.initStream())
        exit(0);
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
}

MainWindow::~MainWindow()
{
    if (this->server != nullptr) {
        this->server->sendLogoutMsg();
        this->server->io_service.stop();
        this->tcpThread->join();
        this->udpServerThread->join();
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
        this->server->sendQueryMsg(ui->ContactField->text().toStdString());
}

void MainWindow::sendVoice(IVoiceStream *remote)
{
    std::cout << "send" << std::endl;
	ss.readFromStream(ss.getReadBuffer());
	//es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
    //print_hexa(ss.getReadBuffer(), es.getEncodeLen(), 0);
    remote->writeData(ss.getReadBuffer(), es.getEncodeLen());
    /* es.decode(ss.getReadBuffer(), es.getEncodeLen()); */
	/* ss.readFromStream(ss.getReadBuffer());
	es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
    //ss.writeOnStream(ss.getReadBuffer());
    print_hexa(ss.getReadBuffer(), es.getEncodeLen(), 0);
    remote->writeData(ss.getReadBuffer(), es.getEncodeLen());
    //es.decode(ss.getReadBuffer(), es.getEncodeLen()); */
}

void MainWindow::receiveVoice(unsigned char* buff, int size)
{
    std::cout << "receive" << std::endl;
	//es.decode(buff, size);
    ss.writeOnStream(buff);
    /* print_hexa(ss.getReadBuffer(), es.getEncodeLen(), 1);
    es.decode(buff, size);
    ss.writeOnStream(buff); */
	//ss.readFromStream(buff);
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
    std::cout << "Handle Call" << std::endl;
    this->udpClient = new ClientVoice(msg.address, 2222);
    std::cout << "Addr: " << std::string(msg.address) << std::endl;
    this->udpClient->setReadCallback(std::bind(&MainWindow::receiveVoice, this, std::placeholders::_1, std::placeholders::_2));
    this->udpClientThread = new boost::thread(boost::bind(&IVoiceStream::start, this->udpClient));
	this->onCall = true;
    this->call(this->udpClient);
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
    std::cout << "INSIDE" << std::endl;
    while (this->onCall) {
        sendVoice(remote);
    }
}