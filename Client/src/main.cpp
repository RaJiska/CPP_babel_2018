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
#include <QtNetwork>
#include "Server.hpp"

int main(int argc, char * const *argv)
{
	/* QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec(); */
	/* Server s("127.0.0.1", 1111);
	s.sendLoginMsg("Hello");
	return 0; */
	
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
		/* before = es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
		after = es.decode(before, es.getEncodeLen()); */
		ss.writeOnStream(ss.getReadBuffer());
		ss.readFromStream();
	}
	
	return EXIT_SUCCESS;
}