/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** main
*/

#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include "voice.hpp"
#include "encode.hpp"
#include "Server.hpp"
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include "ClientVoice.hpp"
#include "ServerVoice.hpp"

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();

	/*
	IVoiceStream *srv = new ServerVoice(2222);
	boost::thread tSrv(boost::bind(&IVoiceStream::start, srv));
	IVoiceStream *cli = new ClientVoice("127.0.0.1", 2222);
	boost::thread tCli(boost::bind(&IVoiceStream::start, cli));
	cli->writeData((const unsigned char *) "Hello", 5);
	usleep(500);
	srv->writeData((const unsigned char *) "World", 5);
	tSrv.join();
	tCli.join();
	*/


	// Server s("127.0.0.1", 1111);
	// while (true) {
	// 	std::cout << "[BEFORE] Bytes Avail: " << s.socket->bytesAvailable() << std::endl;
	// 	s.socket->waitForReadyRead();
	// 	std::cout << "[AFTR] Bytes Avail: " << s.socket->bytesAvailable() << std::endl;
	// 	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	// 	std::cout << "Bytes Avail: " << s.socket->bytesAvailable() << std::endl;
	// 	std::cout << "READ DATA: " << s.socket->read(s.socket->bytesAvailable()) << std::endl;
	// }
	// return 0;

	// QTcpSocket *socket = new QTcpSocket();
	// socket->connectToHost(QString::fromStdString("127.0.0.1"), 1111);
	// if (!socket->waitForConnected())
	// 	throw std::logic_error("Connection timeout");
	// while (true) {
	// 	std::cout << "[BEFORE] Bytes Avail: " << socket->bytesAvailable() << std::endl;
	// 	socket->waitForReadyRead();
	// 	std::cout << "[AFTR] Bytes Avail: " << socket->bytesAvailable() << std::endl;
	// 	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	// 	std::cout << "Bytes Avail: " << socket->bytesAvailable() << std::endl;
	// 	//std::cout << "READ DATA: " << socket->read(50) << std::endl;
	// }
	// return 0;

	/*
	Voice ss;
	EncoderSystem es;
	unsigned char *before;
	unsigned char *after;
	if (!es.encoderCreate() || !es.decoderCreate())
		return (-1);
	ss.initPa();
	ss.initParams();
	ss.initStream();
	while (1) {
		es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
		es.decode(ss.getReadBuffer(), es.getEncodeLen());
		ss.writeOnStream(ss.getReadBuffer());
		ss.readFromStream();
	}
	*/
	return EXIT_SUCCESS;
}