https://blog.csdn.net/zhouhong1026/article/details/8151235

利用函数dup，我们可以复制一个描述符。传给该函数一个既有的描述符，它就会返回一
个新的描述符，这个新的描述符是传给它的描述符的拷贝。这意味着，这两个描述符共享同一
个数据结构。