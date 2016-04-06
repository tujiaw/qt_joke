#include "request.h"
#include <QDateTime>
#include <QCryptographicHash>
#include <QDebug>

Request::Request(QObject *parent)
    : QObject(parent)
{
}

QString Request::getTimestamp()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return dateTime.toString("yyyyMMddHHmmss");
}

QString Request::getMd5(const QList<QPair<QString, QString> > &argv, const QString &secret)
{
   QList<QPair<QString, QString>> list = argv;
   qSort(list.begin(), list.end(), [](const QPair<QString, QString> &left, const QPair<QString, QString> &right) {
        return left.first < right.first;
   });
   QString str;
   for (auto iter = list.begin(); iter != list.end(); ++iter) {
       str += ((*iter).first + (*iter).second);
   }
   str += secret.toLower();
   return QCryptographicHash::hash(str.toLocal8Bit(), QCryptographicHash::Md5).toHex();
}

JokeRequest::JokeRequest(int appId, const QString &secret, QObject *parent)
    : Request(parent)
{
    m_address = "http://route.showapi.com/341-1";
    m_signMethod = "md5";
    m_appId = appId;
    m_secret = secret;

    this->setDate(QDate::currentDate());
    this->setPages(1);
    this->setItems(20);
}

QString JokeRequest::getUrl()
{
    QList<QPair<QString, QString>> argv;
    argv << QPair<QString, QString>("showapi_appid", QString::number(m_appId));
    argv << QPair<QString, QString>("showapi_timestamp", getTimestamp());
    argv << QPair<QString, QString>("time", m_date);
    argv << QPair<QString, QString>("page", QString::number(m_pages));
    argv << QPair<QString, QString>("maxResult", QString::number(m_items));
    m_sign = getMd5(argv, m_secret);

    QString result = m_address + "?showapi_sign=" + m_sign;
    for (auto iter = argv.begin(); iter != argv.end(); ++iter) {
        result += ("&" + (*iter).first + "=" + (*iter).second);
    }

    qDebug() << result;
    return result;
}

void JokeRequest::setDate(const QDate &date)
{
    m_date = QString("%1-%2-%3").arg(date.year()-1).arg(date.month()).arg(date.day());
    qDebug() << "date:" << m_date;
}

void JokeRequest::setPages(int pages)
{
    m_pages = pages;
}

void JokeRequest::setItems(int items)
{
    m_items = items;
}
