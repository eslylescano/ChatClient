#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "echoclient.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr,EchoClient *echoClient = nullptr);

    void setClient(EchoClient *echoClient){
        p_EchoClient = echoClient;
    }
    ~Dialog();
Q_SIGNALS:
    void sendTextMessage(QString message);

private slots:
    void on_pushButton_clicked();
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    Ui::Dialog *ui;
    EchoClient *p_EchoClient;
    bool nameEntered=false;
};

#endif // DIALOG_H
