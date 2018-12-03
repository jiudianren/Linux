tcpdum -s 0 -i  eth0   host  192.168.1.1  8080   -w  /home/1.cap

-s 大小  
-i 网卡名称
-w 文件路径
tcpdump -s 0 -i eth0  port 5098 -w 


	如果是 本机到本机，一定要用回环地址。
	不然抓不到包

https://mp.weixin.qq.com/s/iUZWPBZGRIVnBWNcd6MAOw



#2、用 tcpdump 抓包

使用 tcpdump 抓包，需要管理员权限，因此下面的示例中绝大多数命令都是以 sudo 开头。

首先，先用 `tcpdump -D` 命令列出可以抓包的网络接口：

	$ sudo tcpdump -D
	1.eth0
	2.virbr0
	3.eth1
	4.any (Pseudo-device that captures on all interfaces)
	5.lo [Loopback]

如上所示，可以看到我的机器中所有可以抓包的网络接口。其中特殊接口 any 可用于抓取所有活动的网络接口的数据包。

我们就用如下命令先对 any 接口进行抓包：

 	tcpdump -i any
 	
tcpdump 会持续抓包直到收到中断信号。你可以按 Ctrl+C 来停止抓包。
正如上面示例所示，tcpdump 抓取了超过 9000 个数据包。在这个示例中，由于我是通过 ssh 连接到服务器，所以 tcpdump 也捕获了所有这类数据包。

-c 选项可以用于限制 tcpdump 抓包的数量：

	tcpdump -i any -c 5


如上所示，tcpdump 在抓取 5 个数据包后自动停止了抓包。
这在有些场景中十分有用 —— 比如你只需要抓取少量的数据包用于分析。当我们需要使用过滤规则抓取特定的数据包（如下所示）时，-c 的作用就十分突出了。

在上面示例中，tcpdump 默认是将 IP 地址和端口号解析为对应的接口名以及服务协议名称。
而通常在网络故障排查中，使用 IP 地址和端口号更便于分析问题；

	用 -n 选项显示 IP 地址，-nn 选项显示端口号：

	tcpdump -i any -c 5 -nn
	

如上所示，抓取的数据包中显示 IP 地址和端口号。

这样还可以阻止 tcpdump 发出 DNS 查找，有助于在网络故障排查中减少数据流量。

现在你已经会抓包了，让我们来分析一下这些抓包输出的含义吧。

#3、理解抓取的报文

tcpdump 能够抓取并解码多种协议类型的数据报文，如 TCP、UDP、ICMP 等等。

虽然这里我们不可能介绍所有的数据报文类型，但可以分析下 TCP 类型的数据报文，来帮助你入门。
更多有关 tcpdump 的详细介绍可以参考其 帮助手册。

tcpdump 抓取的 TCP 报文看起来如下：

	08:41:13.729687 IP 192.168.64.28.22 > 192.168.64.1.41916: Flags [P.], seq 196:568, ack 1, win 309, options [nop,nop,TS val 117964079 ecr 816509256], length 372

具体的字段根据不同的报文类型会有不同，但上面这个例子是一般的格式形式。

第一个字段 08:41:13.729687 是该数据报文被抓取的系统本地时间戳。
然后，IP 是网络层协议类型，这里是 IPv4，如果是 IPv6 协议，该字段值是 IP6。
192.168.64.28.22 是源 ip 地址和端口号，紧跟其后的是目的 ip 地址和其端口号，这里是 192.168.64.1.41916。

在源 IP 和目的 IP 之后，可以看到是 TCP 报文标记段 Flags [P.]。该字段通常取值如下：

	s  | syn |  connection start
	f  | fin |  connection finsh
	p  | push|  data push
	r  | rst |  connection rest
	.  | ack |  acknowledgement


该字段也可以是这些值的组合，例如 [S.] 代表 SYN-ACK 数据包。

接下来是该数据包中数据的序列号。
对于抓取的第一个数据包，该字段值是一个绝对数字，后续包使用相对数值，以便更容易查询跟踪。
例如此处 seq 196:568 代表该数据包包含该数据流的第 196 到 568 字节。

接下来是 ack 值：ack 1。
该数据包是数据发送方，ack 值为 1。
在数据接收方，该字段代表数据流上的下一个预期字节数据，例如，该数据流中下一个数据包的 ack 值应该是 568。

接下来字段是接收窗口大小 win 309，它表示接收缓冲区中可用的字节数，后跟 TCP 选项如 MSS（最大段大小）或者窗口比例值。
更详尽的 TCP 协议内容请参考 Transmission Control Protocol(TCP) Parameters。

最后，length 372 代表数据包有效载荷字节长度。这个长度和 seq 序列号中字节数值长度是不一样的。

现在让我们学习如何过滤数据报文以便更容易的分析定位问题。

#4、过滤数据包

正如上面所提，tcpdump 可以抓取很多种类型的数据报文，其中很多可能和我们需要查找的问题并没有关系。举个例子，假设你正在定位一个与 web 服务器连接的网络问题，就不必关系 SSH 数据报文，因此在抓包结果中过滤掉 SSH 报文可能更便于你分析问题。

tcpdump 有很多参数选项可以设置数据包过滤规则，例如根据源 IP 以及目的 IP 地址，端口号，协议等等规则来过滤数据包。下面就介绍一些最常用的过滤方法。

##协议

在命令中指定协议便可以按照协议类型来筛选数据包。比方说用如下命令只要抓取 ICMP 报文：

	$ sudo tcpdump -i any -c5 icmp
	tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
	listening on any, link-type LINUX_SLL (Linux cooked), capture size 262144 bytes

然后再打开一个终端，去 ping 另一台机器：

	$ ping opensource.com
	PING opensource.com (54.204.39.132) 56(84) bytes of data.
	64 bytes from ec2-54-204-39-132.compute-1.amazonaws.com (54.204.39.132): icmp_seq=1 ttl=47 time=39.6 ms

回到运行 tcpdump 命令的终端中，可以看到它筛选出了 ICMP 报文。这里 tcpdump 并没有显示有关 opensource.com 的域名解析数据包：



##主机

用 host 参数只抓取和特定主机相关的数据包：

	tcpdump -i any -c5 -nn host 54.204.39.132


如上所示，只抓取和显示与 54.204.39.132 有关的数据包。

#端口号
	
	tcpdump -i any -c5 -nn  port 8080
tcpdump 可以根据服务类型或者端口号来筛选数据包。例如，抓取和 HTTP 服务相关的数据包：


##IP 地址/主机名

同样，你也可以根据源 IP 地址或者目的 IP 地址或者主机名来筛选数据包。例如抓取源 IP 地址为 192.168.122.98 的数据包：


	tcpdump -i any -c5 -nn  src 192.168.122.98 
注意此处示例中抓取了来自源 IP 地址 192.168.122.98 的 53 端口以及 80 端口的数据包，它们的应答包没有显示出来因为那些包的源 IP 地址已经变了。

	tcpdump -i any -c5 -nn  dst 192.168.122.98
相对的，使用 dst 就是按目的 IP/主机名来筛选数据包。



#多条件筛选

当然，可以使用多条件组合来筛选数据包，使用 and 以及 or 逻辑操作符来创建过滤规则。

例如，筛选来自源 IP 地址 192.168.122.98 的 HTTP 数据包：

	tcpdump -i any -c5 -nn  src 10.11.10.1 and port 80

你也可以使用括号来创建更为复杂的过滤规则，但在 shell 中请用引号包含你的过滤规则以防止被识别为 shell 表达式：

	tcpdump -i any -c5 -nn  "port 80 and (src 10.45.18.121 or src 10.45.18.122)" 

该例子中我们只抓取了来自源 IP 为 192.168.122.98 或者 54.204.39.132 的 HTTP （端口号80）的数据包。使用该方法就很容易抓取到数据流中交互双方的数据包了。

#5、检查数据包内容

在以上的示例中，我们只按数据包头部的信息来建立规则筛选数据包，例如源地址、目的地址、端口号等等。有时我们需要分析网络连接问题，可能需要分析数据包中的内容来判断什么内容需要被发送、什么内容需要被接收等。tcpdump 提供了两个选项可以查看数据包内容，-X 以十六进制打印出数据报文内容，-A 打印数据报文的 ASCII 值。

例如，HTTP 请求报文内容如下：


	tcpdump -i any -c5 -nn  -A port 80 


Found

The document has moved here.



这对定位一些普通 HTTP 调用 API 接口的问题很有用。当然如果是加密报文，这个输出也就没多大用了。

6、保存抓包数据

tcpdump 提供了保存抓包数据的功能以便后续分析数据包。例如，你可以夜里让它在那里抓包，然后早上起来再去分析它。同样当有很多数据包时，显示过快也不利于分析，将数据包保存下来，更有利于分析问题。

使用 -w 选项来保存数据包而不是在屏幕上显示出抓取的数据包：

	$ sudo tcpdump -i any -c10 -nn -w webserver.pcap port 80
	[sudo] password for ricardo:
	tcpdump: listening on any, link-type LINUX_SLL (Linux cooked), capture size 262144 bytes
	10 packets captured
	10 packets received by filter
	0 packets dropped by kernel

该命令将抓取的数据包保存到文件 webserver.pcap。后缀名 pcap 表示文件是抓取的数据包格式。

正如示例中所示，保存数据包到文件中时屏幕上就没有任何有关数据报文的输出，其中 -c10 表示抓取到 10 个数据包后就停止抓包。如果想有一些反馈来提示确实抓取到了数据包，可以使用 -v 选项。

tcpdump 将数据包保存在二进制文件中，所以不能简单的用文本编辑器去打开它。使用 -r 选项参数来阅读该文件中的报文内容：

	tcpdump -nn -r xxx.pcap


这里不需要管理员权限 sudo 了，因为此刻并不是在网络接口处抓包。

你还可以使用我们讨论过的任何过滤规则来过滤文件中的内容，就像使用实时数据一样。 例如，通过执行以下命令从源 IP 地址 54.204.39.132 检查文件中的数据包：

