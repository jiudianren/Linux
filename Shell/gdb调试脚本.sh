#!bin/bash

if [ x"$1" = x ]
then
	echo "Please restart the script and ,Input your program name!! "
	exit
fi


#Get GDB Info
bGDB=`which gdb`
if [ x"$bGDB" = x ]
then
	echo "NO GDB in your config,and EXIT"
	exit
	
else
	echo "USE THE GDB: $bGDB"
fi



echo "your program is $1 "

iPNO=$(ps -ef|grep $1|grep -v grep | grep -v $0 |awk '{print $2}')

if [ x"$iPNO" = x ]
then
	echo "NO PROGRAM $1 "
	exit
else
	echo "PROGARM $1 's PNO : $iPNO"
fi

echo "   "
echo "   "
echo "   "

echo "gdb  PID $iPNO"
gdb  PID $iPNO


