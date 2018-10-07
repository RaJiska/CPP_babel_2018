#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <boost/thread/thread.hpp>
#include <iostream>
#include "ui_mainwindow.h"
#include "Server.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        virtual ~MainWindow();

    public slots:
        void PressLogin();
        void PressContact();

    private:
        Ui::MainWindow *ui;
        Server *server;
        boost::thread *tcpThread;
};

#endif // MAINWINDOW_H
