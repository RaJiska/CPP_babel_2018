/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** main
*/

#include <iostream>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();

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