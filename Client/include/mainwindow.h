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
#include "ServerVoice.hpp"
#include "ClientVoice.hpp"

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
        void sendVoice(IVoiceStream *remote);
        void receiveVoice(unsigned char* buf, int size);
        void PressHangup();
        void PressCall();
        void handleContact(NetworkMessage::MsgQuery &msg);
        void handleCall(NetworkMessage::MsgCall &msg);
        void handleHangup();
        void call(IVoiceStream *remote);

    private:
        Ui::MainWindow *ui;
        Server *server = nullptr;
        IVoiceStream *udpServer = nullptr;
        IVoiceStream *udpClient = nullptr;
        boost::thread *tcpThread;
        boost::thread *udpServerThread = nullptr;
        boost::thread *udpClientThread = nullptr;
	    EncoderSystem es;
        bool onCall = false;
        std::vector<NetworkMessage::MsgQuery> clientsList;
        unsigned long long int target = 0;

};

#endif // MAINWINDOW_H
