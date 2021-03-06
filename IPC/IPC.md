# 随内核持续性 
# 随进程持续性


#POSIX IPC

#SYSTEM V IPC


linux上面的IPC大多都是从UNIX上面继承而来。
        最初Unix IPC包括：管道、FIFO、信号。
        System V IPC包括：System V消息队列、System V信号灯、System V共享内存区。
        由于Unix版本的多样性，电子电气工程协会（IEEE）开发了一个独立的Unix标准，这个新的ANSI Unix标准被称为计算机环境的可移植性操作系统界面（PSOIX）。
        
        现有大部分Unix和流行版本都是遵循POSIX标准的，而Linux从一开始就遵循POSIX标准。
  Posix IPC包括： Posix消息队列、Posix信号灯、Posix共享内存区。 所以目前linux上面支持的IPC主要包括四类：
1. UNIX早期IPC：管道、FIFO、信号；
2. system V IPC：System V消息队列、System V信号灯、System V共享内存区；
3. Posix IPC： Posix消息队列、Posix信号灯、Posix共享内存区；
4. 基于socket的IPC；

        我们这一系列没有讲述信号灯相关内容，是因为信号灯是进程间以及同一进程不同线程之间的一种同步方式，我们这一系列把精力主要放在进程之间信息的交互上面，而同步与互斥的内容放在另一个系列，这样更便于知识的细化归类，各个击破。其实同步与互斥是进程间通信的一个很重要的内容，所以我们会立即在下一个系列详细讲解同步与互斥的内容。
下面分析一下我们这一系列文章各种IPC的特点：

1. socket
        a、使用socket通信的方式实现起来简单，可以使用因特网域和UNIX域来实现，使用因特网域可以实现不同主机之间的进出通信。
        b、该方式自身携带同步机制，不需要额外的方式来辅助实现同步。
        c、随进程持续。
2. 共享内存
        a、最快的一种通信方式，多个进程可同时访问同一片内存空间，相对其他方式来说具有更少的数据拷贝，效率较高。
        b、需要结合信号灯或其他方式来实现多个进程间同步，自身不具备同步机制。
        c、随内核持续，相比于随进程持续生命力更强。
3. 管道
        a、较早的一种通信方式，缺点明显：只能用于有亲缘关系进程之间的通信；只支持单向数据流，如果要双向通信需要多创建一个管道来实现。
        b、自身具备同步机制。
        c、随进程持续。
4. FIFO
        a、是有名管道，所以支持没有亲缘关系的进程通信。和共享内存类似，提供一个路径名字将各个无亲缘关系的进程关联起来。但是也需要创建两个描述符来实现双向通信。
        b、自身具备同步机制。
        c、随进程持续。
5. 信号
        a、这种通信可携带的信息极少。不适合需要经常携带数据的通信。
        b、不具备同步机制，类似于中断，什么时候产生信号，进程是不知道的。
        
6. 消息队列
        a、与共享内存和FIFO类似，使用一个路径名来实现各个无亲缘关系进程之间的通信。消息队列相比于其他方式有很多优点：它提供有格式的字节流，减少了开发人员的工作量；消息具有类型（system V）或优先级（posix）。其他方式都没有这些优点。
        b、具备同步机制。
        c、随内核持续。