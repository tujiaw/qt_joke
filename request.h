#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);

    virtual QString getUrl() = 0;
    static QString getTimestamp();
    static QString getMd5(const QList<QPair<QString, QString>> &argv, const QString &secret);

protected:
    QString m_address;
    int m_appId;
    QString m_secret;
    QString m_sign;
    QString m_timestamp;
    QString m_signMethod;
};

class JokeRequest : public Request
{
    Q_OBJECT
public:
    JokeRequest(int appId, const QString &secret, QObject *parent = 0);
    QString getUrl();

    void setDate(const QDate &date);
    void setPages(int pages);
    void setItems(int items);

private:
    QString m_date;
    int m_pages;
    int m_items;
};

#endif // REQUEST_H
