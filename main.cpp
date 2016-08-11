#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //a.setFont(QFont(QStringLiteral("微软雅黑"), 10));

    Widget w;
    w.show();

    return a.exec();
}
