https://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/lsof.html


https://www.cnblogs.com/bonelee/p/7735479.html
lsof 可以查看进程所打开的端口
http://blog.fatedier.com/2016/07/18/stat-all-connection-info-of-special-process-in-linux/


简介
lsof(list open files)是一个列出当前系统打开文件的工具。在linux环境下，任何事物都以文件的形式存在，通过文件不仅仅可以访问常规数据，还可以访问网络连接和硬件。所以如传输控制协议 (TCP) 和用户数据报协议 (UDP) 套接字等，系统在后台都为该应用程序分配了一个文件描述符，无论这个文件的本质如何，该文件描述符为应用程序与基础操作系统之间的交互提供了通用接口。因为应用程序打开文件的描述符列表提供了大量关于这个应用程序本身的信息，因此通过lsof工具能够查看这个列表对系统监测以及排错将是很有帮助的。


https://www.cnblogs.com/sparkbj/p/7161669.html