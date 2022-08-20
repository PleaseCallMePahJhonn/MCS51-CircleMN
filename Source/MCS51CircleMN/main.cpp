#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet=QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
    file.close();

    //qDebug()<<QApplication::applicationDirPath()<<endl;//获取程序当前路径
    Widget w;
    w.setWindowTitle("MCS51 CircleMN");
    w.setWindowIcon(QIcon(":/logo.png"));
    w.show();
    return a.exec();
}
