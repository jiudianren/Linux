

apt-get install vsftpd

sudo apt-get install vsftpd
ftp的配置文件在

/etc/vsftpd.conf
可以使用下列命令来打开，关闭，重启ftp服务

sudo /etc/init.d/vsftpd start
sudo /etc/init.d/vsftpd stop
sudo /etc/init.d/vsftpd restart
使用下列命令，可以看到系统中多了ftp用户组和ftp用户

cat /etc/group
cat /etc/passwd

-----------------------------
	编辑/etc/vsftpd.conf文件:

	// 允许匿名用户登录
	anonymous_enable=YES

	// 允许本地用户登录
	local_enable=YES

	// 开启全局上传
	write_enable=YES

	// 允许匿名用户上传文件
	anon_upload_enable=YES  

	// 充许匿名用户新建文件夹
	anon_mkdir_write_enable=YES


----------------------------

https://www.cnblogs.com/jiqing9006/p/8955559.html


# root ftp enable

默认情况下vsftp是不允许root用户登录的，可以通过修改限制来解决这个问题。
首先找到vsftp的配置目录
[root@localhost vsftpd]# pwd
/etc/vsftpd
[root@localhost vsftpd]# ls
chroot_list  ftpusers  user_list  vsftpd.conf  vsftpd_conf_migrate.sh
[root@localhost vsftpd]#
修改
[root@localhost vsftpd]# cat ftpusers
# Users that are not allowed to login via ftp
#root
bin ....
修改
[root@localhost vsftpd]# cat user_list

# vsftpd userlist

# If userlist_deny=NO, only allow users in this file

# If userlist_deny=YES (default), never allow users in this file, and

# do not even prompt for a password.
# Note that the default vsftpd pam config also checks /etc/vsftpd/ftpusers
# for users that are denied.
#root

bin .......

上面这个两个就是默认情况下vsftp不允许使用的账号列表，讲文件中root删除，或者前面加个#号 重启一下vsftpd 服务 即可
