tcpdum -s 0 -i  eth0   host  192.168.1.1  8080   -w  /home/1.cap

-s 大小  
-i 网卡名称
-w 文件路径
tcpdump -s 0 -i eth0  port 5098 -w 


如果是 本机到本机，一定要用回环地址。
不然抓不到包
