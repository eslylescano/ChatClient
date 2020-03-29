#include "dialog.h"
#include "ui_dialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

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
    ui->pushButton->setText("Choose name");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(!nameEntered){
        emit sendTextMessage( ui->lineEdit->text());
        ui->lineEdit->setText("");
        ui->pushButton->setText("Send Message");
        nameEntered=true;
    }else{
        emit sendTextMessage( ui->lineEdit->text());
        ui->lineEdit->setText("");
    }

}

void Dialog::onConnected()
{
    qDebug() << "Connected in dialog";
}

void Dialog::onTextMessageReceived(QString message)
{
    QJsonDocument messageJsonDocument= QJsonDocument::fromJson(message.toUtf8());
    QJsonObject messageJsonObject = messageJsonDocument.object();


    //qDebug() << message;

    QString type = messageJsonObject["type"].toString();

    if (type == "color")
    {
       //qDebug() << "color type";


    }else if (type == "history") {
    QJsonArray data = messageJsonObject["data"].toArray();
    foreach (const QJsonValue & value, data) {
        QJsonObject obj = value.toObject();
        QString author = obj["author"].toString();
        QString color = obj["color"].toString();
        QString text = obj["text"].toString();
        double time = obj["time"].toDouble();
       QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(time);
       QString dateFormated = dateTime.toString("MM-dd HH:mm:ss");


        author = "<font color="+color+">"+author+"</font>";
        ui->textEdit->append(author+"@@ "+dateFormated+": "+text+"<br>");
    }

    //qDebug() << "history type";


    }else if (type == "message") {
        QJsonObject messageObject = messageJsonObject["data"].toObject();

            QString author = messageObject["author"].toString();
            QString color = messageObject["color"].toString();
            QString text = messageObject["text"].toString();
            double time = messageObject["time"].toDouble();
           QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(time);
           QString dateFormated = dateTime.toString("MM-dd HH:mm:ss");


            author = "<font color="+color+">"+author+"</font>";
            ui->textEdit->append(author+"@@ "+dateFormated+": "+text+"<br>");


        //qDebug() << "message type";
    }

    //ui->textEdit->append(messageJsonDocument.toJson());

}
