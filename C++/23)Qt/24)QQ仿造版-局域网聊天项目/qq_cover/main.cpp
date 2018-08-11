#include <QApplication>
#include"dialoglist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DialogList d;
    d.show();

    return a.exec();
}
