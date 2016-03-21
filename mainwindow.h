#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocalSocket>

class QLocalServer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_runServerButton_clicked();

    void on_runSocketButton_clicked();

private:
    Ui::MainWindow *ui;



    QLocalSocket *socket;
    QLocalServer *server;
    quint16 blockSize;

    void handleResponse();
    void displayError(QLocalSocket::LocalSocketError socketError);


    void sendRequest();
};

#endif // MAINWINDOW_H
