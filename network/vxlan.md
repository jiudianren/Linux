
在 Linux 上配置 VXLAN
https://zhuanlan.zhihu.com/p/53038354


http://just4coding.com/2017/05/21/vxlan/
VXLAN规范要求BUM流量使用IP组播进行洪泛，将数据包发送到除源VTEP外的所有VTEP。目标VTEP发送回响应数据包时，源VTEP从中学习MAC地址、VNI和VTEP的映射关系，并添加到转发表中。后续VTEP再次发送数据包给该MAC地址时，VTEP会从转发表中直接确定目标VTEP，从而只发送单播数据到目标VTEP。
