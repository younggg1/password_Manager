#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
Loginwindow::Loginwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Loginwindow)  // 初始化为空
{
    ui->setupUi(this);

    connect(&reg,SIGNAL(registerSignal()),this,SLOT(toLogin()));
    connect(ui->userNamelineEdit, &QLineEdit::returnPressed, ui->pushButton_login_2, &QPushButton::click);
    connect(ui->passwordlineEdit, &QLineEdit::returnPressed, ui->pushButton_login_2, &QPushButton::click);
}

Loginwindow::~Loginwindow()
{
    delete ui;
}
void Loginwindow::clearInputFields() {
    ui->userNamelineEdit->clear(); // 清除用户名输入框内容
    ui->passwordlineEdit->clear(); // 清除密码输入框内容
}
// 验证登录用户
bool Loginwindow::loginUser(const QString& username, const QString& password) {
    QFile file("users.json");

    // 打开文件用于读取
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "提示", "打开用户文件失败,请先尝试注册");
        return false;
    }

    // 读取文件中的JSON内容
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = doc.object();
    QJsonArray usersArray = jsonObj["users"].toArray();

    // 遍历用户数组，检查用户名和密码是否匹配
    for (const auto& user : usersArray) {
        QJsonObject obj = user.toObject();
        if (obj["username"].toString() == username) {
            // 加密输入的密码进行匹配
            QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
            QString encryptedPassword = hash.toHex();

            if (obj["password"].toString() == encryptedPassword) {
                QMessageBox::information(nullptr, "提示", "登录成功，进入主界面");

                return true;
            } else {
                QMessageBox::warning(nullptr, "提示", "密码错误");
                return false;
            }
        }
    }

    // 如果没有找到用户名，提示用户
    QMessageBox::warning(nullptr, "", "用户不存在");
    return false;
}
void Loginwindow::on_registerButton_clicked()
{
    reg.show();//展示注册窗口
    this->hide();// 隐藏当前窗口
}
void Loginwindow::on_pushButton_login_2_clicked()
{
    QString username = ui->userNamelineEdit->text();
    QString password = ui->passwordlineEdit->text();
    //检查输入是否为空
    if (username.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名不能为空");
        return;
    }else if(password.isEmpty()){
        QMessageBox::warning(this, "提示", "密码不能为空");
        return;
    }
    if(loginUser(username, password)){
            // 打开主窗口，并传递当前用户名
            MainWindow *passUsername = new MainWindow(nullptr, username);
            // 显示主窗口
            passUsername->show();
            // 使用 passUsername 来调用 MainWindow 中的方法
            passUsername->displayWelcomeMessage(username);
            //mainwindow.show();//进入主界面
            this->close();//隐藏登录界面
            clearInputFields(); // 登录成功后清除输入框内容
    }else {
        QMessageBox::warning(this, "错误", "用户名或密码不正确");
    }
}
void Loginwindow::toLogin(){
    reg.close();
    this->show();
}
