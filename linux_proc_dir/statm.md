http://man7.org/linux/man-pages/man5/proc.5.html

https://blog.csdn.net/dutsoft/article/details/51250374



原因：
cat /proc/1/statm 
180024 1241 1046 35 0 171703 0

参数 解释 /proc/[pid]/status
Size (pages) 任务虚拟地址空间的大小 VmSize/4
Resident(pages) 应用程序正在使用的物理内存的大小 VmRSS/4
Shared(pages) 共享页数 0
Trs(pages) 程序所拥有的可执行虚拟内存的大小 VmExe/4
Lrs(pages) 被映像到任务的虚拟内存空间的库的大小 VmLib/4
Drs(pages) 程序数据段和用户态的栈的大小 （VmData+ VmStk ）4

/proc/[pid]/status里的数值实际是按page来统计的，第二列为Resident(pages)—— 应用程序正在使用的物理内存的大小 VmRSS/4，为实际使用内存数值的四分之一
