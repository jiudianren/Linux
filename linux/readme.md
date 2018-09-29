
centos minimal

# ssh服务
ps -aux|grep sshd


#网络类型
vm选择网络类型 VMnet8 
首先我们登录操作系统 用户名root 密码 123456
然后我们输入ip查询命名 ip addr
发现ens33 没有inet 这个属性，那么就没法通过IP地址连接虚拟机。

接着来查看ens33网卡的配置：vi /etc/sysconfig/network-scripts/ifcfg-ens33 注意vi后面加空格
从配置清单中可以发现 CentOS 7 默认是不启动网卡的（ONBOOT=no）。

把这一项改为YES（ONBOOT=yes）

然后重启网络服务： sudo service network restart

[root@promote ~]# ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 00:0c:29:11:d5:7b brd ff:ff:ff:ff:ff:ff
    inet 192.168.56.130/24 brd 192.168.56.255 scope global noprefixroute dynamic ens33
       valid_lft 1542sec preferred_lft 1542sec
    inet6 fe80::6f84:f63d:48b3:eeec/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
[root@promote ~]# 

192.168.56.130 就是ip了
# vi /etc/sysconfig/network-script/ifcfg-  之后按tab自动联想 修改对应的配置文件

设置为自动获取ip地址

ONBOOT=yes
MM_Controlled=no   我的没有这个设置
BOOTPROTO=dhcp

重启网络服务，命令：
service network restart
测试是否能联网，命令：
ping www.ahomepage.net

##ftp

## root e
sudo passwd root



## docker 安装
yum install -y docker
yum serach docker
which docker

## cmake 
yum install cmake


##gcc g++ gdb

使用yum安装gcc：yum install gcc
使用yum安装g++：yum install gcc-c++   
方法一：使用yum安装：yum install gdb

#SSH SERVER
http://jingyan.baidu.com/article/00a07f38a5c05482d128dc5f.html
http://www.linuxidc.com/Linux/2015-01/112033.htm

#更改字体
setterm -foreground green
setterm -store

#git

一.安装Git

$ yum install git
二. 生成SSH密钥
 $ ssh-keygen -t rsa -C “your email address”
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
