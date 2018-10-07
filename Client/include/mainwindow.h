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

	    /// \brief
	    /// Constructor of the class MainWindow
	    /// \param parent : default value is nullptr, otherwise the parent QWidget
        MainWindow(QWidget *parent = nullptr);

    	/// \brief
    	/// Destructor of the class ClientVoice
	    /// \param None
        virtual ~MainWindow();
        Voice ss;

    public slots:

    	/// \brief
    	/// Slot called when the user press the login button
	    /// \param None
        void PressLogin();

    	/// \brief
    	/// Slot called when the user press the contact button
	    /// \param None
        void PressContact();

    	/// \brief
    	/// Encodes and sends the voice
	    /// \param remote : IVoiceStream that the voice has to be sent at
        void sendVoice(IVoiceStream *remote);

    	/// \brief
    	/// Decodes the voice and play it
	    /// \param buf : Voice buffer
	    /// \param size : Size of the voice buffer
        void receiveVoice(unsigned char* buf, int size);

    	/// \brief
    	/// Slot called when the user press the hangup button
	    /// \param None
        void PressHangup();

    	/// \brief
    	/// Slot called when the user press the call button
	    /// \param None
        void PressCall();

    	/// \brief
    	/// Adds a new contact in the list
	    /// \param msg : NetworkMessage of the new contact
        void handleContact(NetworkMessage::MsgQuery &msg);

    	/// \brief
    	/// Receives the call and answer
	    /// \param msg : NetworkMessage of the new call
        void handleCall(NetworkMessage::MsgCall &msg);

    	/// \brief
    	/// Handler function used when hanging up
	    /// \param None
        void handleHangup();

    	/// \brief
    	/// Handler function used when logging in
	    /// \param None
        void handleLogin();

    	/// \brief
    	/// Calls the remote
	    /// \param remote : Who is being called
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
