#include "loginwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Application started";
    // 创建登录窗口对象
    Loginwindow loginWindow;
    // 显示登录窗口
    loginWindow.show();
    qDebug() << "Login window shown";

    return a.exec();
}
