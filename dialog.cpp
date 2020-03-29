#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent,EchoClient *echoClient) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    setClient(echoClient);
    ui->setupUi(this);
    //if(!p_EchoClient)
    QObject::connect(p_EchoClient,SIGNAL(connected()),this,SLOT(onConnected()));
    QObject::connect(p_EchoClient,SIGNAL(textMessageReceived(QString)),this,SLOT(onTextMessageReceived(QString)));
    QObject::connect(this,SIGNAL(sendTextMessage(QString)),p_EchoClient,SLOT(onSendTextMessage(QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
emit sendTextMessage( ui->lineEdit->text());
    ui->lineEdit->setText("");
}

void Dialog::onConnected()
{
    qDebug() << "Connected in dialog";
}

void Dialog::onTextMessageReceived(QString message)
{
    qDebug() << message;
    ui->textEdit->append(message);

}
