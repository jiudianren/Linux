https://blog.csdn.net/sduliulun/article/details/7732906


内容	描述
使用未初始化的内存	Use of uninitialised memory
使用已经释放了的内存	Reading/writing memory after it has been free’d
使用超过 malloc分配的内存空间	Reading/writing off the end of malloc’d blocks
对堆栈的非法访问	Reading/writing inappropriate areas on the stack
申请的空间是否有释放	Memory leaks – where pointers to malloc’d blocks are lost forever
malloc/free/new/delete申请和释放内存的匹配	Mismatched use of malloc/new/new [] vs free/delete/delete []
src和dst的重叠	Overlapping src and dst pointers in memcpy() and related functions
