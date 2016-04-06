#include "dialog.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("Joke");
    QIcon icon(":/rc/smile.ico");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
