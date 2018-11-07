pstack命令可显示每个进程的栈跟踪，
pstack $pid即可，pstack命令须由$pid进程的属主或者root运行。

这次出现cpu占比100%的情况，但看memory占比，并无异常，怀疑是某个地方死循环了。经同事提醒，用pstack命令查看相关进程，通过运行多次pstack，发现代码栈总是停在同一个位置。具体看代码，发现就是这个地方写错了。

pstack 排查程序 死循环，或者死锁

https://www.cnblogs.com/shenlinken/p/8157204.html