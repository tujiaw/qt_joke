#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class NetManager;
class JokeResponse;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pbGet_clicked();
    void on_pbReset_clicked();

    void on_pbBack_clicked();

    void on_pbNext_clicked();

private:
    Ui::Dialog *ui;
    NetManager *m_netManager;
    JokeResponse *m_response;
};

#endif // DIALOG_H
