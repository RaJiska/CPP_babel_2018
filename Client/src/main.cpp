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
}