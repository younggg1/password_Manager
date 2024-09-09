#ifndef CREATEPASSWORD_H
#define CREATEPASSWORD_H

#include <QWidget>
#include <QShortcut>
namespace Ui {
class CreatePassword;

}

class CreatePassword : public QWidget
{
    Q_OBJECT
public:
    explicit CreatePassword(QWidget *parent = nullptr, const QString &username = "");  // 构造函数接收用户名
    ~CreatePassword();
    //QString encryptPassword(const QString &password);
private slots:
    void on_cancelpushButton_clicked();
    void on_savepushButton_clicked();
private:
    Ui::CreatePassword *ui;
    QShortcut *enterShortcut;
    QString currentUser;
    void savePassword(const QString &name, const QString &url, const QString &username, const QString &password);
};

#endif // CREATEPASSWORD_H
