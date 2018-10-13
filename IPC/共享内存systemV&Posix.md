
http://www.voidcn.com/article/p-uuiihfmf-mx.html
https://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index1.html
https://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index2.html?ca=drs-
https://blog.csdn.net/liu0808/article/details/73821748

第 4 部分 共享内存
共享内存是最快的ipc形式，原因是减少了在内核和用户空间的拷贝

#缺省情况下 fork派生的子进程并不与父进程共享 共享内存

mmap 有三个目的
1，使用普通文件，以提供内存映射
2 使用特殊文件，以提供匿名内存映射
3 使用shm_open以提供无亲缘关系的进程间的posix共享内存

void * mmap() 

mmap获得 共享内存的指向的地址

打开共享内存 需要一个fd


 munmap msync

读到12.6节
无亲缘关系的 进程间共享内存区的两种方法：

open 内存映射文件 （打开的是文件）
shm_open 共享内存区对象 （打开的具名的一个标志）
shm_open(const char *name ,int ,mode_t )
shm_unlink

int ftruncate(int fd ,off_t length)
修改共享内存或者文件的大小 




int fstat()
获取共享内存的对象的相关信息



同一共享内存映射到不同进程的地址空间时，起始地址可以不一样。


共享内存，示例：
