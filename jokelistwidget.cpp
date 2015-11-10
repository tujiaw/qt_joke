#include "jokelistwidget.h"
#include <QtWidgets>

#define ROW_HEIGHT 18
#define ITEM_SPACE 10

JokeItemWidget::JokeItemWidget(const JokeItem &item, QWidget *parent) : QWidget(parent)
{
    m_title = new QLabel("[" + item.title + "]", this);
    m_time = new QLabel(item.ct, this);
    m_content = new QLabel(item.text, this);
    m_content->setWordWrap(true);

    QVBoxLayout *mLayout = new QVBoxLayout();
    mLayout->setContentsMargins(0, 0, 0, ITEM_SPACE);
    mLayout->setSpacing(0);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addStretch();
    hLayout->addWidget(m_time);

    mLayout->addWidget(m_title);
    mLayout->addWidget(m_content);
    mLayout->addLayout(hLayout);

    this->setLayout(mLayout);
}

JokeListWidget::JokeListWidget(QWidget *parent) : QListWidget(parent)
{
    this->setStyleSheet("QListWidget { border:0px; }");
}

void JokeListWidget::setData(const QList<JokeItem> &datas)
{
    this->clear();
    QFontMetrics fm = this->fontMetrics();
    int itemWidth = this->width() - ITEM_SPACE * 2;
    foreach (const JokeItem &data, datas) {
        QListWidgetItem *item = new QListWidgetItem(this);
        int row = fm.width(data.text) / itemWidth + 2;
        item->setSizeHint(QSize(itemWidth, row * ROW_HEIGHT + ITEM_SPACE));
        this->insertItem(0, item);
        this->setItemWidget(item, new JokeItemWidget(data));
    }
}
