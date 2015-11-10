#include "response.h"
#include "json.h"
#include <QDebug>

Response::Response(const QByteArray &data, QObject *parent) : QObject(parent)
{
    QVariantMap json = json::toMap(data);
    m_resCode = json["showapi_res_code"].toInt();
    m_resError = json["showapi_res_error"].toString();
    m_resBody = json["showapi_res_body"].toMap();
}

int Response::resCode() const
{
    return m_resCode;
}

QString Response::resError() const
{
    return m_resError;
}

JokeResponse::JokeResponse(const QByteArray &data, QObject *parent)
    : Response(data, parent)
{
    m_allNum = m_resBody["allNum"].toInt();
    m_allPages = m_resBody["allPages"].toInt();
    QVariantList ls = m_resBody["contentlist"].toList();
    for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
        QVariantMap item = (*iter).toMap();
        JokeItem jokeItem;
        jokeItem.title = item["title"].toString();
        jokeItem.text = item["text"].toString();
        jokeItem.ct = item["ct"].toString();
        m_contentList.append(jokeItem);
    }
    m_currentPage = m_resBody["currentPage"].toInt();
    m_maxResult = m_resBody["maxResult"].toInt();
}
