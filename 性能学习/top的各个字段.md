https://www.cnblogs.com/xudong-bupt/p/8643094.html


linux ps top 命令 VSZ,RSS,TTY,STAT, VIRT,RES,SHR,DATA的含义
https://www.cnblogs.com/leijiangtao/p/4049076.html


Linux中ps与top命令
这两个命令都是查看系统进程信息的命令，但是用处有点儿不同
1.ps命令–提供系统过去信息的一次性快照
也就是说ps命令能够查看刚刚系统的进程信息  命令：ps aux或者ps lax
[root@Linux ~]# ps aux
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.1  0.1   2032   644 ?        Ss   21:55   0:01 init [3]
root         2  0.0  0.0      0     0 ?        S    21:55   0:00 [migration/0]
root         3  0.0  0.0      0     0 ?        SN   21:55   0:00 [ksoftirqd/0]
……
解释如下：
VSZ–进程的虚拟大小
RSS–驻留集的大小，可以理解为内存中页的数量
TTY–控制终端的ID
STAT–也就是当前进程的状态，其中S-睡眠，s-表示该进程是会话的先导进程，N-表示进程拥有比普通优先级更低的优先级，R-正在运行，D-短期等待，Z-僵死进程，T-被跟踪或者被停止等等
STRAT–这个很简单，就是该进程启动的时间
TIME–进程已经消耗的CPU时间，注意是消耗CPU的时间
COMMOND–命令的名称和参数
而]#ps lax  可以看到父进程，谦让值以及该进程正在等待的资源等待