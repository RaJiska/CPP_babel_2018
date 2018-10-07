#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <algorithm>
#include "ui_mainwindow.h"
#include "Server.hpp"
#include "voice.hpp"
#include "encode.hpp"
#include "NetworkMessage.hpp"

namespace Ui {
class MainWindow;
}

class Server;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        virtual ~MainWindow();
        Voice ss;

    public slots:
        void PressLogin();
        void PressContact();
        void sendVoice();
        void recieveVoice(unsigned char* buf, int size);
        void PressHangOut();
        void PressCall();
        void handleContact(NetworkMessage::MsgQuery &msg);

    private:
        Ui::MainWindow *ui;
        Server *server = nullptr;
        boost::thread *tcpThread;
	    EncoderSystem es;
        bool onCall = false;
        std::vector<NetworkMessage::MsgQuery> clientsList;

};

#endif // MAINWINDOW_H
