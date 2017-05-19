#include "downloader.h"
#include <iostream>

using namespace std;

downloader::downloader(QObject *parent) : QObject(parent)
{
    manager=0;
}

void downloader::doDownload()
{
    manager=new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,
            SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://meta.ua")));
}

downloader::~downloader()
{
    delete manager;
}

void downloader::replyFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
       cout<<qPrintable(QString("Error!"))<<endl;
       cout<<qPrintable(reply->errorString())<<endl;
    }
    else
    {
        cout<<
    qPrintable(reply->header(QNetworkRequest::ContentTypeHeader).toString())<<endl;
        cout<<
    qPrintable(reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString())<<endl;
        cout<<
    reply->header(QNetworkRequest::ContentLengthHeader).toULongLong()<<endl;
        cout<<
    reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()<<endl;
        cout<<
    qPrintable(reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString())<<endl;

        QFile *file=new QFile("E:/temp/downloaded.html");
        if(file->open(QFile::Append))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        delete file;
    }
    reply->deleteLater();
}
