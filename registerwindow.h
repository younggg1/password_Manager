#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>

namespace Ui {
class RegisterWindow;
}
class Loginwindow;
class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private:
    Ui::RegisterWindow *ui;
    void registerUser(const QString& username, const QString& password);
public slots:
    void registerSlot();
signals:
    void registerSignal();
private slots:
    void on_submitButton_clicked();
};
#endif // REGISTERWINDOW_H
