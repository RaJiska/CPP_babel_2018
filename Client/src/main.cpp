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

int main(int argc, char * const *argv)
{
	/* QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec(); */


	Voice ss;
	ss.initPa();
	ss.initParams();
	ss.initStream();
	while (1) {
		ss.readFromStream();
		ss.writeOnStream(ss.getReadBuffer());
	}
	return EXIT_SUCCESS;
}