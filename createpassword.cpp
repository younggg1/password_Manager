#include "createpassword.h"
#include "ui_createpassword.h"
//#include "mainwindow.h"
#include "QMessageBox"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QShortcut>
CreatePassword::CreatePassword(QWidget *parent, const QString &username)
    : QWidget(parent), ui(new Ui::CreatePassword), currentUser(username)  // 初始化 currentUser
{
    ui->setupUi(this);
    qDebug() << "CreatePassword window created for user:" << currentUser;
    // 初始化 enterShortcut，绑定 Enter 键到保存按钮
    enterShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(enterShortcut, &QShortcut::activated, ui->savepushButton, &QPushButton::click);
}
CreatePassword::~CreatePassword()
{
    delete enterShortcut;
    delete ui;
}
// // 密码加密函数（使用SHA-256）
// QString CreatePassword::encryptPassword(const QString &password) {
//     QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
//     return hash.toHex();
// }
// 保存密码到当前用户的文件
void CreatePassword::savePassword(const QString &name, const QString &url, const QString &username, const QString &password) {
    if (currentUser.isEmpty()) {
        qDebug() << "Error: currentUser is empty!";
        //QMessageBox::warning(this, "Error", "User not logged in.");
    }
    QString fileName = currentUser + "_passwords.json";  // 以当前用户的用户名作为文件名
    qDebug() << "Generated file name:" << fileName;
    QFile file(fileName);

    QJsonArray passwordArray;

    // 如果文件存在，读取现有数据
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "提示", "打开用户文件失败");
            return;
        }
        QByteArray fileData = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        passwordArray = doc.array();
        file.close();
    }

    // 创建密码对象
    QJsonObject passwordObject;
    passwordObject["name"] = name;
    passwordObject["url"] = url;
    passwordObject["username"] = username;
    passwordObject["password"] = password;  // 调用加密函数

    // 添加到 JSON 数组
    passwordArray.append(passwordObject);

    // 保存到文件
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "提示", "打开用户文件失败");
        return;
    }

    QJsonDocument doc(passwordArray);
    file.write(doc.toJson());
    file.close();
}

void CreatePassword::on_cancelpushButton_clicked()
{
    this->close();
}

void CreatePassword::on_savepushButton_clicked()
{
    QString name = ui->namelineEdit->text();
    QString username = ui->userNamelineEdit->text();
    QString password = ui->passwordlineEdit->text();
    QString url = ui->urllineEdit->text();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名不能为空");
        return;
    } else if (name.isEmpty()) {
        QMessageBox::warning(this, "提示", "网站名不能为空");
        return;
    } else if (password.isEmpty()) {
        QMessageBox::warning(this, "提示", "密码不能为空");
        return;
    } else if (url.isEmpty()) {
        QMessageBox::warning(this, "提示", "url不能为空");
        return;
    } else {
        savePassword(name, url, username, password);
        QMessageBox::information(nullptr, "提示", "保存成功");

        // 清除输入框内容
        ui->namelineEdit->clear();
        ui->urllineEdit->clear();
        ui->userNamelineEdit->clear();
        ui->passwordlineEdit->clear();
    }
}

