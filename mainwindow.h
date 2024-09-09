#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <createpassword.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &username = "");
    void displayWelcomeMessage(const QString &username);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    //CreatePassword createwindow;
    void loadPasswordsForUser(const QString &username);
    void savePasswordForUser(const QString &username, const QString &name, const QString &user, const QString &password, const QString &url);
     // 显示欢迎信息
    QString currentUser;  // 当前登录用户
    void savePasswordsToFile();
private slots:
    void on_createpushButton_clicked();
    void on_exitProcessButton_clicked();
    void on_deletepushButton_clicked();
    void on_RefreshButton_clicked();
    void on_exitButton_clicked();
};

#endif // MAINWINDOW_H
