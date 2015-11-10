#ifndef JOKELISTWIDGET_H
#define JOKELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include "response.h"

class QLabel;
class JokeItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JokeItemWidget(const JokeItem &item, QWidget *parent = 0);

private:
    QLabel *m_title;
    QLabel *m_time;
    QLabel *m_content;
};

class JokeListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit JokeListWidget(QWidget *parent = 0);
    void setData(const QList<JokeItem> &datas);
};

#endif // JOKELISTWIDGET_H
