#include "dialog.h"
#include <QApplication>
#include "echoclient.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    EchoClient client(QUrl(QStringLiteral("ws://chat.biosilico.com/:80")), true);
    return a.exec();
}
