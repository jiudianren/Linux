
#ipcs

查看进程间通讯的相关内容 
ipcs -m 查看共享内存

## 查看共享内存 使用的进程
ipcs -m 查看共享内存 id
lsof id 查看使用的进程 


#查看进程间关系--pstree

通过pstree命令可以看到进程间的父子关系，它以树形结构显示这些信息：

pstree
systemd─┬─ModemManager─┬─{gdbus}
        │              └─{gmain}
        ├─NetworkManager─┬─dhclient
        │                ├─dnsmasq
        │                ├─{gdbus}
        │                └─{gmain}
        ├─accounts-daemon─┬─{gdbus}
        │                 └─{gmain}
        ├─acpid
        ├─atd
        ├─avahi-daemon───avahi-daemon
        ├─bluetoothd
        ├─colord─┬─{gdbus}
        │        └─{gmain}
        ├─cron
        ├─cups-browsed─┬─{gdbus}
        │              └─{gmain}
        ├─cupsd───3*[dbus]
        ├─dbus-daemon
        ├─gnome-keyring-d─┬─{gdbus}
        │                 ├─{gmain}
        │                 └─{timer}
(仅显示部分内容)

总结

实际上，前面所提到的很多相关命令信息都是从系统文件中获取的，例如/proc/meminfo保存了内存相关信息，/proc/net/dev保存网络流量相关信息。只是，它们都是静态数值，但是我们可以结合watch命令来动态地观察这些信息，例如：

watch -n 1 cat /proc/meminfo 
watch -n 1 cat /proc/net/dev

上面的命令表示，每隔一秒执行一次cat /proc/meminfo或cat /proc/net/dev，因此我们可以看到内存信息或网卡流量信息在实时刷新。

本文仅介绍这些命令的经典使用，更多使用可通过man 命令查看。通过前面这些系统自带命令，我们可以比较方便地监控系统状态，从而帮助我们维护系统或定位问题。欢迎留言补充或更正。
