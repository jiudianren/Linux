
http://www.voidcn.com/article/p-uuiihfmf-mx.html
https://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index1.html
https://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index2.html?ca=drs-
https://blog.csdn.net/liu0808/article/details/73821748

第 4 部分 共享内存
共享内存是最快的ipc形式，原因是减少了在内核和用户空间的拷贝


mmap 有三个目的
1，使用普通文件，以提供内存映射
2 使用特殊文件，以提供匿名内存映射
3 使用shm_open以提供无亲缘关系的进程间的posix共享内存

mmap munmap msync

读到12.6节
