

CPU 使用率
在上一期我曾提到，Linux 作为一个多任务操作系统，将每个 CPU 的时间划分为很短
的时间片，再通过调度器轮流分配给各个任务使用，因此造成多任务同时运行的错觉。
为了维护 CPU 时间，Linux 通过事先定义的节拍率（内核中表示为 HZ），触发时间
中断，并使用全局变量 Jiffies 记录了开机以来的节拍数。每发生一次时间中断，Jiffies
的值就加 1。
节拍率 HZ 是内核的可配选项，可以设置为 100、250、1000 等。不同的系统可能设
置不同数值，你可以通过查询 /boot/config 内核选项来查看它的配置值。比如在我的
系统中，节拍率设置成了 250，也就是每秒钟触发 250 次时间中断。



	pidstat 1 5



	# 只保留各个 CPU 的数据
	$ cat /proc/stat | grep ^cpu
	cpu  280580 7407 286084 172900810 83602 0 583 0 0 0
	cpu0 144745 4181 176701 86423902 52076 0 301 0 0 0
	cpu1 135834 3226 109383 86476907 31525 0 282 0 0 0



当然，这里每一列的顺序并不需要你背下来。你只要记住，有需要的时候，查询 man
proc 就可以。不过，你要清楚 man proc 文档里每一列的涵义，它们都是 CPU 使用
率相关的重要指标，你还会在很多其他的性能工具中看到它们。下面，我来依次解读一
下。
	
	user（通常缩写为 us），代表用户态 CPU 时间。注意，它不包括下面的 nice 时
	间，但包括了 guest 时间。
	nice（通常缩写为 ni），代表低优先级用户态 CPU 时间，也就是进程的 nice 值被
	调整为 1-19 之间时的 CPU 时间。这里注意，nice 可取值范围是 -20 到 19，数值
	越大，优先级反而越低。
	system（通常缩写为 sys），代表内核态 CPU 时间。
	idle（通常缩写为 id），代表空闲时间。注意，它不包括等待 I/O 的时间
	（iowait）。
	iowait（通常缩写为 wa），代表等待 I/O 的 CPU 时间。
	irq（通常缩写为 hi），代表处理硬中断的 CPU 时间。
	softirq（通常缩写为 si），代表处理软中断的 CPU 时间。
	steal（通常缩写为 st），代表当系统运行在虚拟机中的时候，被其他虚拟机占用的
	CPU 时间。
	guest（通常缩写为 guest），代表通过虚拟化运行其他操作系统的时间，也就是运
	行虚拟机的 CPU 时间。
	guest_nice（通常缩写为 gnice），代表以低优先级运行虚拟机的时间。





比如，下面的 pidstat 命令，就间隔 1 秒展示了进程的 5 组 CPU 使用率，包括： 
	
	用户态 CPU 使用率 （%usr）； 
	内核态 CPU 使用率（%system）；
	 运行虚拟机 CPU 使用率（%guest）； 
	 等待 CPU 使用率（%wait）； 
	 以及总的 CPU 使用率（%CPU）。



perf 性能分析工具 可以看到函数级别的



第一种常见用法是 perf top，类似于 top，它能够实时显示占用 CPU 时钟最多的函数
或者指令，因此可以用来查找热点函数，使用界面如下所示：


	$ perf top
	Samples: 833  of event 'cpu-clock', Event count (approx.): 97742399
	Overhead  Shared Object       Symbol
	   7.28%  perf                [.] 0x00000000001f78a4
	   4.72%  [kernel]            [k] vsnprintf
	   4.32%  [kernel]            [k] module_get_kallsym
	   3.65%  [kernel]            [k] _raw_spin_unlock_irqrestore
	...


输出结果中，第一行包含三个数据，分别是采样数（Samples）、事件类型（event）
和事件总数量（Event count）。比如这个例子中，perf 总共采集了 833 个 CPU 时钟
事件，而总事件数则为 97742399。
另外，采样数需要我们特别注意。如果采样数过少（比如只有十几个），那下面的排序
和百分比就没什么实际参考价值了。

再往下看是一个表格式样的数据，每一行包含四列，分别是：
	
	第一列 Overhead ，是该符号的性能事件在所有采样中的比例，用百分比来表示。
	第二列 Shared ，是该函数或指令所在的动态共享对象（Dynamic Shared
	Object），如内核、进程名、动态链接库名、内核模块名等。
	第三列 Object ，是动态共享对象的类型。比如 [.] 表示用户空间的可执行程序、或
	者动态链接库，而 [k] 则表示内核空间。
	最后一列 Symbol 是符号名，也就是函数名。当函数名未知时，用十六进制的地址
	来表示。
还是以上面的输出为例，我们可以看到，占用 CPU 时钟最多的是 perf 工具自身，不
过它的比例也只有 7.28%，说明系统并没有 CPU 性能问题。 perf top 的使用你应该
很清楚了吧



	[/proc/sys/kernel/kptr_restrict](https://blog.csdn.net/gatieme/article/details/78311841)
		https://jackyu.cn/tech/set-kernel-kptr-restrict-equal-to-1/
	
	$ perf record # 按 Ctrl+C 终止采样
	[ perf record: Woken up 1 times to write data ]
	[ perf record: Captured and wrote 0.452 MB perf.data (6093 samples) ]
	
	$ perf report # 展示类似于 perf top 的报告
	
	
	

	
	
	
	
	ab（apache bench）是一个常用的 HTTP 服务性能测试工具，这里用来模拟 Ngnix 的客户端




top  查看 具体的cpu 消耗 进程

perf 查看 cpu消耗较高的进程的  具体的函数使用





小结
CPU 使用率是最直观和最常用的系统性能指标，更是我们在排查性能问题时，通常会
关注的第一个指标。所以我们更要熟悉它的含义，尤其要弄清楚用户（%user）、
Nice（%nice）、系统（%system） 、等待 I/O（%iowait） 、中断（%irq）以及软
中断（%softirq）这几种不同 CPU 的使用率。比如说：

	用户 CPU 和 Nice CPU 高，说明用户态进程占用了较多的 CPU，所以应该着重排查进程的性能问题。
	
	系统 CPU 高，说明内核态占用了较多的 CPU，所以应该着重排查内核线程或者系统调用的性能问题。

	I/O 等待 CPU 高，说明等待 I/O 的时间比较长，所以应该着重排查系统存储是不是出现了 I/O 问题。

	软中断和硬中断高，说明软中断或硬中断的处理程序占用了较多的 CPU，所以应该着重排查内核中的中断服务程序。
	
碰到 CPU 使用率升高的问题，你可以借助 top、pidstat 等工具，确认引发 CPU 性能
问题的来源；再使用 perf 等工具，排查出引起性能问题的具体函数。



系统的 CPU 使用率很高，但为啥却找不到高 CPU 的应用？
短时进程



