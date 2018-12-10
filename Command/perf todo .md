#perf 安装

http://www.voidcn.com/article/p-ttwwedfy-qb.html

apt install linux-tools-common


https://www.cnblogs.com/arnoldlu/p/6241297.html 

安装 perf 非常简单, 只要内核版本高于2.6.31的, perf已经被内核支持. 首先安装内核源码:
apt-get install linux-source
那么在 /usr/src 目录下就已经下载好了内核源码, 我们对源码包进行解压, 然后进入 tools/perf 目录然后敲入下面两个命令即可：

make
make install



安装 perf 非常简单, 只要内核版本高于2.6.31的, perf已经被内核支持. 首先安装内核源码:
apt-get install linux-source
那么在 /usr/src 目录下就已经下载好了内核源码, 我们对源码包进行解压, 然后进入 tools/perf 目录然后敲入下面两个命令即可：

make
make install
可能因为系统原因, 需要提前安装下面的开发包:
apt-get install -y binutils-dev
apt-get install -y libdw-dev
apt-get install -y python-dev
apt-get install -y libnewt-dev

http://blog.chinaunix.net/uid-10540984-id-3854969.html


为什么呢？因为 GDB 调试程序的过程会中断程序运行，这在线上环境往往是不允许的。
所以，GDB 只适合用在性能分析的后期，当你找到了出问题的大致函数后，
线下再借助它来进一步调试函数内部的问题。 那么哪种工具适合在第一时间分析进程的 CPU 问题呢？我的推荐是 perf。

perf 是 Linux 2.6.31 以后内置的性能分析工具。
它以性能事件采样为基础，不仅可以分析系统的各种事件和内核性能，还可以用来分析指定应用程序的性能问题。 
使用 perf 分析 CPU 性能问题，我来说两种最常见、也是我最喜欢的用法。


https://blog.csdn.net/trochiluses/article/details/10261339