#include "dialog.h"
#include <QApplication>
#include "echoclient.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EchoClient client(QUrl(QStringLiteral("ws://chat.biosilico.com/:80")), true);
    Dialog w(nullptr,&client);
    w.show();

    return a.exec();
}
