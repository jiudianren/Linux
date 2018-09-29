#git

一.安装Git

$ yum install git
二. 生成SSH密钥
 $ ssh-keygen -t rsa -C "648087012@qq.com"
连续按3个回车（密码默认为空），得到 id_rsa 和 id_rsa.pub 文件，在/root/.ssh 下说明生成成功

三.添加密钥到Github
打开 Github，登录自己的账号后
点击自己的头像->settings->SSH And GPG Keys->New SSH key
将本地 id_rsa.pub 中的内容粘贴到 Key 文本框中，随意输入一个 title(不要有中文)，点击 Add Key 即可

四.测试
在命令行中输入

$ ssh git@github.com
会出现如下询问：
Are you sure you want to continue connecting (yes/no)?
键入yes后回车，如果出现
Hi xxx! You’ve successfully authenticated, but GitHub does not provide shell accessConnection to github.com closed.
则说明验证成功，否则可能是上述步骤中的其中几步出错了，需重新来过