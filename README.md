# password_Manager
基于QT开发的简单功能密码管理软件


登录界面


![login](https://github.com/user-attachments/assets/a02e541d-e67d-4020-be47-1217a51075aa)


注册界面，注册后生成user.json文件，密码项使用SHA-256加密


注册成功后可点击登录按钮返回登录界面


![register](https://github.com/user-attachments/assets/59d6a275-baf9-4698-90e9-d875b3f75663)


登录成功后进入主界面，主界面各个按钮对应各种功能，展示JSON文件中已有的密码项


![mainwindow](https://github.com/user-attachments/assets/2afbafd8-7d1c-4adb-b8be-52e4dafb46fd)


创建新密码界面，创建密码后根据当前用户名生成对应的JSON文件，这里没有加密因为主界面展示需要解密，暂时没考虑这一项


![createpassword](https://github.com/user-attachments/assets/ca2df503-e8f4-4642-b097-c6c081b4de50)




