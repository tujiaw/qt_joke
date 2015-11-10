#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>
#include <QVariantMap>

class Response : public QObject
{
    Q_OBJECT
public:
    explicit Response(const QByteArray &data, QObject *parent = 0);

    int resCode() const;
    QString resError() const;

protected:
    int m_resCode;
    QString m_resError;
    QVariantMap m_resBody;
};

typedef struct {
    QString title;
    QString text;
    QString ct;
} JokeItem;

class JokeResponse : public Response
{
    Q_OBJECT
public:
    explicit JokeResponse(const QByteArray &data, QObject *parent = 0);


    int m_allNum;
    int m_allPages;
    QList<JokeItem> m_contentList;
    int m_currentPage;
    int m_maxResult;
};

#endif // RESPONSE_H
