#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <mainwindow.h>
#include <registerwindow.h>
#include <createpassword.h>
namespace Ui {
class Loginwindow;
}

class Loginwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Loginwindow(QWidget *parent = nullptr);
    ~Loginwindow();

private:
    Ui::Loginwindow *ui;
    RegisterWindow reg;
    MainWindow mainwindow;
    bool loginUser(const QString& username, const QString& password);
    void clearInputFields(); // 清除输入框内容的辅助函数
private slots:
    void on_registerButton_clicked();
    void on_pushButton_login_2_clicked();
    void toLogin();
};

#endif // LOGINWINDOW_H
