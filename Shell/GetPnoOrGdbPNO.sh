#!bin/bash

export program=""
export scriptName=""

function CheckProgramName
{
	if [ x"$program" = x ]
	then
		echo "Please restart the script and ,Input your program name!! "
		exit
	fi
}

function  GetPNO 
{
	CheckProgramName
	ps -aux|grep $program |grep -v grep | grep -v $scriptName
}

function CheckGDB
{
	#Get GDB Info
	bGDB=`which gdb`
	
	if [ x"$bGDB" = x ]
	then
		echo "NO GDB in your config,and EXIT"
		exit
		
	else
		echo "USE THE GDB: $bGDB"
	fi
}

function ExeGDB
{
	iPNO=$(ps -aux|grep $program|grep -v grep | grep -v $scriptName | grep -v Zl |awk '{print $2}')

	if [ x"$iPNO" = x ]
	then
		echo "NO PROGRAM $program "
		exit
	else
		echo "PROGARM $program 's PNO : $iPNO"
	fi
	
	echo "   "
	echo "   "
	echo "gdb  PID $iPNO"
	echo "   "
	
	gdb  PID $iPNO
	
}


function Tips
{
		echo " -h :help "
		echo " -n : get the programe PNO "
		echo " -g : gdb your progrrame "
		echo "for example:"
		echo "bash ./gdb.sh -n SM-SR "
		echo "bash ./gdb.sh -g SM-SR "

}


scriptName=$0
if [ x"$1" = x ]
then
	
	echo "Please restart the script and ,Input your program name!! "
	Tips
	exit
else
	
	if [ "$1" = "-h" ]
	then 
		Tips
	elif [ "$1" = "-n" ]
	then
		program="$2"
		GetPNO
	
	elif  [ "$1" = "-g" ]
	then
		program="$2"
		ExeGDB
	else
		echo " Please give the -n or -g"
	fi
fi









