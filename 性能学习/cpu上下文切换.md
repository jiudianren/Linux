cpu上下文切换包括
  
    进程上下文切换和中断上下文切换
    
    
cpu特权等级
    ring 0 --ring 3
    
    用户态到内核态的转换，需要系统调用来完成
    
  系统调用也有上下文切换
  
区别：
  	
		进程上下文切换时在进程之间的
		系统调用的是在同一进程的上下文切换
		
		


vmstat 主要分析系统的内存使用情况

	man vmstat:
	  
	  cs: The number of context switches per second.  每秒上下文切换次数
	  in: The number of interrupts per second, including the clock. 每秒终端次数
	  
	  r: The number of runnable processes (running or waiting for run time). 
	  			就绪队列长度，正在等待cpu或者运行的进程数
       b: The number of processes in uninterruptible sleep.
       			不可终端睡眠的进程数
       			
      
查看进程的上下文切换次数：
	
	man pidstat
	
	
	pidstat -w 5
	
	  cswch/s
                     Total number of voluntary context switches the task made per second. 
                      A voluntary context  switch  occurs  
                      when  a task blocks because it requires a resource that is unavailable.
	每秒任务所做的自愿上下文切换的总数。 
	当任务阻塞时会发生自愿上下文切换，
	因为它需要一个不可用的资源。



              nvcswch/s
                     Total number of non voluntary context switches the task made per second. 
                      A involuntary context switch takes place   
                         when a task executes for the duration of its time slice 
                         and then is forced to relinquish the processor.
	 
	 每秒任务所做的非自愿上下文切换的总数。
	  当任务在其时间片的持续时间内执行时，
	  发生非自愿的上下文切换，然后被迫放弃处理器。
	

#sysbench
	
	sysbench 是一个多线程的基准测试工具，一般用来评估不同系统参数下的数据库负载情况
	
	
	
	sysbench --test=threads  --num-threads=10  --max-time=300 run
	
	pidstat -wt 1

	vmstat  1 2
	

查看中断信息：

	# -d 参数表示高亮显示变化的区域
	$ watch -d cat /proc/interrupts
	           CPU0       CPU1
	...
	RES:    2450431    5279697   Rescheduling interrupts


观察一段时间，你可以发现，变化速度最快的是重调度中断（RES），
这个中断类型表示，唤醒空闲状态的 CPU 来调度新的任务运行。这是多处理器系统（SMP）中，
调度器用来分散任务到不同 CPU 的机制，
通常也被称为处理器间中断（Inter-Processor Interrupts，IPI）


这时，你还需要根据上下文切换的类型，再做具体分析。比方说：

 自愿上下文切换变多了，说明进程都在等待资源，有可能发生了 I/O 等其他问题； 
 非自愿上下文切换变多了，说明进程都在被强制调度，也就是都在争抢 CPU，说明 CPU 的确成了瓶颈；
  中断次数变多了，说明 CPU 被中断处理程序占用，还需要通过查看 /proc/interrupts 文件来分析具体的中断类型。
  
  
  


	# 每隔 1 秒输出一组数据（需要 Ctrl+C 才结束）
	# -wt 参数表示输出线程的上下文切换指标
	$ pidstat -wt 1
	08:14:05      UID      TGID       TID   cswch/s nvcswch/s  Command
	...
	08:14:05        0     10551         -      6.00      0.00  sysbench
	08:14:05        0         -     10551      6.00      0.00  |__sysbench
	08:14:05        0         -     10552  18911.00 103740.00  |__sysbench
	08:14:05        0         -     10553  18915.00 100955.00  |__sysbench
	08:14:05        0         -     10554  18827.00 103954.00  |__sysbench
	...
	
	
#查看中断


	# -d 参数表示高亮显示变化的区域
	$ watch -d cat /proc/interrupts
	           CPU0       CPU1
	...
	RES:    2450431    5279697   Rescheduling interrupts
	...
	
	
现在再回到最初的问题，每秒上下文切换多少次才算正常呢？ 

这个数值其实取决于系统本身的 CPU 性能。在我看来，如果系统的上下文切换次数比较稳定，那么从数百到一万以内，都应该算是正常的。  
但当上下文切换次数超过一万次，或者切换次数出现数量级的增长时，就很可能已经出现了性能问题。 

这时，你还需要根据上下文切换的类型，再做具体分析。
	
	比方说： 
		自愿上下文切换变多了，
			说明进程都在等待资源，有可能发生了 I/O 等其他问题； 
			
		非自愿上下文切换变多了，
			说明进程都在被强制调度，也就是都在争抢 CPU，说明 CPU 的确成了瓶颈； 
			
		中断次数变多了，
			说明 CPU 被中断处理程序占用，还需要通过查看 /proc/interrupts 文件来分析具体的中断类型

	