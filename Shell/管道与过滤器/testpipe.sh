#!/bin/sh
  
 if [ $# -gt 0 ];then
     exec 0<$1;
#判断是否传入参数：文件名，如果传入，将该文件绑定到标准输入
 fi
  
 while read line
 do
     echo $line;
 done<&0;
#通过标准输入循环读取内容
 exec 0&-;
#解除标准输入绑定