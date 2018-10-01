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

int main(int argc, char * const *argv)
{
	/* QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec(); */


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
		before = es.encode(ss.getReadBuffer(), ss.getReadBufferSize());
		after = es.decode(before, es.getEncodeLen());
		ss.writeOnStream(after);
		ss.readFromStream();
	}
	return EXIT_SUCCESS;
}