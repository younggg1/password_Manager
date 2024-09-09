#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QWidget>
#include <loginwindow.h>
#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow)


{
    ui->setupUi(this);
    connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(registerSlot()));
    connect(ui->userNamelineEdit, &QLineEdit::returnPressed, ui->submitButton, &QPushButton::click);
    connect(ui->passwordlineEdit, &QLineEdit::returnPressed, ui->submitButton, &QPushButton::click);
}
RegisterWindow::~RegisterWindow()
{
    delete ui;
}
void RegisterWindow::registerSlot(){
    emit registerSignal();
}
// 注册用户到JSON文件，并进行密码加密
void RegisterWindow::registerUser(const QString& username, const QString& password) {
    QFile file("users.json");

    // 打开文件用于读写
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "提示", "打开用户文件失败");
        return;
    }

    // 读取文件中的JSON内容
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = doc.object();
    QJsonArray usersArray = jsonObj["users"].toArray();

    // 检查用户名是否已存在
    for (const auto& user : usersArray) {
        if (user.toObject()["username"].toString() == username) {
            QMessageBox::warning(nullptr, "提示", "用户名已存在");
            return;
        }
    }

    // // 加密用户密码（使用SHA-256哈希加密）
    // QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    // QString encryptedPassword = hash.toHex();

    // 创建新用户对象
    QJsonObject newUser;
    newUser["username"] = username;
    newUser["password"] = password;
    newUser["password_data"] = QJsonArray();  // 初始化空的密码数据

    // 将新用户添加到用户数组中
    usersArray.append(newUser);
    jsonObj["users"] = usersArray;

    // 将更改保存到文件
    doc.setObject(jsonObj);
    file.resize(0);  // 清空文件内容
    file.write(doc.toJson());
    file.close();
    QMessageBox::warning(nullptr, "提示", "注册成功");
}
void RegisterWindow::on_submitButton_clicked()
{

    QString username = ui->userNamelineEdit->text();
    QString password = ui->passwordlineEdit->text();

    //检查输入是否为空
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户名和密码不能为空");
        return;
    }
    registerUser(username, password);
}

