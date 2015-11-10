#include "dialog.h"
#include "ui_dialog.h"
#include "request.h"
#include "response.h"
#include "netmanager.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_response(NULL)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    m_netManager = new NetManager(this);
    this->setFixedWidth(450);

    ui->deDate->setDate(QDate::currentDate());
    emit ui->pbGet->clicked();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pbGet_clicked()
{
    JokeRequest req(12078, "c7288cbf5a0941598e3ab326c27f9668");
    req.setDate(ui->deDate->date());
    req.setPages(ui->spPages->value());
    req.setItems(ui->spItems->value());
    m_netManager->request(req.getUrl(), [this](const QByteArray &data) {
        if (m_response) {
            m_response->deleteLater();
        }
        m_response = new JokeResponse(data);
        ui->spPages->setMaximum(m_response->m_allPages);
        ui->spPages->setMinimum(1);
        ui->spPages->setValue(m_response->m_currentPage);

        ui->pbBack->setEnabled(m_response->m_currentPage > 1);
        ui->pbNext->setEnabled(m_response->m_currentPage < m_response->m_allPages);

        qDebug() << m_response->m_allNum;
        qDebug() << m_response->m_allPages;
        qDebug() << m_response->m_currentPage;
        qDebug() << m_response->m_maxResult;
        ui->listWidget->setData(m_response->m_contentList);
    });
}

void Dialog::on_pbReset_clicked()
{
    ui->deDate->setDate(QDate::currentDate());
    ui->spPages->setValue(1);
    ui->spItems->setValue(20);
}

void Dialog::on_pbBack_clicked()
{
    ui->spPages->setValue(ui->spPages->value() - 1);
    emit ui->pbGet->clicked();
}

void Dialog::on_pbNext_clicked()
{
    ui->spPages->setValue(ui->spPages->value() + 1);
    emit ui->pbGet->clicked();
}
