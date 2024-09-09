#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QShortcut>
MainWindow::MainWindow(QWidget *parent, const QString &username) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    currentUser(username)  // 保存用户名
{
    ui->setupUi(this);
    //this->setLayout(ui->verticalLayout);

    displayWelcomeMessage(currentUser);  // 显示欢迎信息
    //绑定按键到新建密码上
    QShortcut *shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+N")),this);
    connect(shortcutOpen,&QShortcut::activated,[=](){
        on_createpushButton_clicked();
    });
    // 加载当前用户的密码并显示
    loadPasswordsForUser(currentUser);

}
void MainWindow::on_createpushButton_clicked()
{
    // 创建 CreatePassword 对象并传递用户名
    CreatePassword *ctrpassUsername = new CreatePassword(nullptr, currentUser);
    //CreatePassword createwindow(*this, currentUser);
    ctrpassUsername->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

// 加载指定用户的密码并在 QTableView 中显示
void MainWindow::loadPasswordsForUser(const QString &username) {
    QString fileName = currentUser + "_passwords.json";  // 根据用户名加载特定文件
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        //QMessageBox::warning(this, "Error", "Could not open file for reading.");
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonArray passwordArray = doc.array();

    // 创建模型
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"网站名", "用户名", "密码", "URL"});

    // 将 JSON 数据添加到模型中
    for (const QJsonValue &value : passwordArray) {
        QJsonObject obj = value.toObject();
        QList<QStandardItem *> rowItems;

        QString name = obj["name"].toString();
        QString username = obj["username"].toString();
        QString password = obj["password"].toString();
        QString url = obj["url"].toString();

        rowItems.append(new QStandardItem(name));
        rowItems.append(new QStandardItem(username));
        rowItems.append(new QStandardItem(password));
        rowItems.append(new QStandardItem(url));

        model->appendRow(rowItems);
    }

    // 设置模型到 QTableView
    ui->tableView->setModel(model);

    // 设置列宽
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// 保存新密码
void MainWindow::savePasswordForUser(const QString &username, const QString &name, const QString &user, const QString &password, const QString &url) {
    QString fileName = username + "_passwords.json";  // 根据用户名存储密码
    QFile file(fileName);

    QJsonArray passwordArray;

    // 如果文件存在，读取现有数据
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(nullptr, "Error", "读取用户文件失败");
            return;
        }
        QByteArray fileData = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        passwordArray = doc.array();
        file.close();
    }

    // 新的密码对象
    QJsonObject passwordObject;
    passwordObject["name"] = name;
    passwordObject["username"] = user;
    passwordObject["password"] = password;  // 假设已经加密
    passwordObject["url"] = url;

    // 添加到 JSON 数组
    passwordArray.append(passwordObject);

    // 保存回文件
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "Error", "写入用户文件失败");
        return;
    }

    QJsonDocument doc(passwordArray);
    file.write(doc.toJson());
    file.close();

    // 保存后重新加载数据以更新视图
    loadPasswordsForUser(username);
}
void MainWindow::displayWelcomeMessage(const QString &username) {
    if (!currentUser.isEmpty()) {
        ui->welcomelabel->setText("当前登录用户: " + currentUser);
        qDebug() << "Welcome message displayed for user:" << currentUser;
    } else {
        ui->welcomelabel->setText("Welcome!");
        qDebug() << "Error: currentUser is empty!";
    }
}
void MainWindow::on_exitProcessButton_clicked()
{
    this->close();
}
void MainWindow::savePasswordsToFile() {
    QString fileName = currentUser + "_passwords.json";  // 以当前用户的用户名作为文件名
    QFile file(fileName);

    QJsonArray passwordArray;

    // 创建新的 JSON 数据
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    if (model) {
        for (int row = 0; row < model->rowCount(); ++row) {
            QJsonObject passwordObject;
            passwordObject["name"] = model->item(row, 0)->text();
            passwordObject["username"] = model->item(row, 1)->text();
            passwordObject["password"] = model->item(row, 2)->text();
            passwordObject["url"] = model->item(row, 3)->text();
            passwordArray.append(passwordObject);
        }
    }

    // 保存到文件
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "提示", "打开用户文件失败");
        return;
    }

    QJsonDocument doc(passwordArray);
    file.write(doc.toJson());
    file.close();
}


void MainWindow::on_deletepushButton_clicked()
{
    // 获取 QTableView 的选中模型
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    // 获取选中的索引列表
    QModelIndexList selectedIndexes = selectionModel->selectedRows();

    // 确保有选中的行
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有选择要删除的密码！");
        return;
    }

    // 确认删除操作
    if (QMessageBox::question(this, "确认删除", "确定要删除选中的密码吗？") != QMessageBox::Yes) {
        return;
    }

    // 获取模型
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    if (!model) {
        return;
    }

    // 删除选中的行
    foreach (const QModelIndex &index, selectedIndexes) {
        model->removeRow(index.row());
    }

    // 保存更新后的数据到文件
    savePasswordsToFile();
}


void MainWindow::on_RefreshButton_clicked()
{
    // 重新加载并更新密码数据
    loadPasswordsForUser(currentUser);
}


void MainWindow::on_exitButton_clicked()
{
    this->close();
    // 使用 new 动态创建 LoginWindow
    Loginwindow *loginWindow = new Loginwindow();
    loginWindow->show();
}

