#include <QCoreApplication>
#include "downloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    downloader d;
    d.doDownload();

    return a.exec();
}
