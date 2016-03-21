#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new QLocalSocket(this)),
    server(new QLocalServer(this))
{
    ui->setupUi(this);
    connect(server, &QLocalServer::newConnection, this, &MainWindow::sendRequest);

    connect(socket, &QLocalSocket::readyRead, this, &MainWindow::handleResponse);
    connect(socket, static_cast<void (QLocalSocket::*)(QLocalSocket::LocalSocketError)>(&QLocalSocket::error),
            this, &MainWindow::displayError);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleResponse()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (in.atEnd())
        return;
    QString func, arg1, arg2;
    in >> func >> arg1 >> arg2;
    if ( func == "Information" )
        QMessageBox::information(this, arg1, arg2);
}

void MainWindow::displayError(QLocalSocket::LocalSocketError socketError)
{
    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:
    case QLocalSocket::ConnectionRefusedError:
    case QLocalSocket::PeerClosedError:
        break;
    default:
        break;
    }

}

void MainWindow::sendRequest()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << (quint16)0;
    out << QString("Information") << QString("arg1") << QString("arg2");
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QLocalSocket *clientConnection = server->nextPendingConnection();
    connect(clientConnection, &QLocalSocket::disconnected,
            clientConnection, &QLocalSocket::deleteLater);

    clientConnection->write(block);
    clientConnection->flush();
    clientConnection->disconnectFromServer();

}

void MainWindow::on_runServerButton_clicked()
{
    if (!server->listen("function"))
        close();
}

void MainWindow::on_runSocketButton_clicked()
{
    blockSize = 0;
    socket->abort();
    socket->connectToServer("function");
}
