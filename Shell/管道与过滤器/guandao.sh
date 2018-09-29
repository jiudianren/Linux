#!/bin/bash

#管道命令操作符是：”|”,它仅能处理经由前面一个指令传出的正确输出信息，
#也就是 standard output 的信息，
#对于 stdandard error 信息没有直接处理能力。
#然后，传递给下一个命令，作为标准的输入 standard input.

#https://www.cnblogs.com/pengliangcheng/p/5211786.html


#读出test.sh文件内容，通过管道转发给grep 作为输入内
cat test.sh | grep -n 'echo'


cat test.sh test1.sh | grep -n 'echo'
#cat: test1.sh: 没有那个文件或目录
#cat test1.sh不存在，错误输出打印到屏幕，正确输出通过管道发送给grep


cat testpipe.txt | sh testpipe.sh
 
sh testpipe.sh testpipe.txt  