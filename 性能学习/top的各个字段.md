https://www.cnblogs.com/xudong-bupt/p/8643094.html


linux ps top ���� VSZ,RSS,TTY,STAT, VIRT,RES,SHR,DATA�ĺ���
https://www.cnblogs.com/leijiangtao/p/4049076.html


Linux��ps��top����
����������ǲ鿴ϵͳ������Ϣ����������ô��е����ͬ
1.ps����C�ṩϵͳ��ȥ��Ϣ��һ���Կ���
Ҳ����˵ps�����ܹ��鿴�ո�ϵͳ�Ľ�����Ϣ  ���ps aux����ps lax
[root@Linux ~]# ps aux
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.1  0.1   2032   644 ?        Ss   21:55   0:01 init [3]
root         2  0.0  0.0      0     0 ?        S    21:55   0:00 [migration/0]
root         3  0.0  0.0      0     0 ?        SN   21:55   0:00 [ksoftirqd/0]
����
�������£�
VSZ�C���̵������С
RSS�Cפ�����Ĵ�С���������Ϊ�ڴ���ҳ������
TTY�C�����ն˵�ID
STAT�CҲ���ǵ�ǰ���̵�״̬������S-˯�ߣ�s-��ʾ�ý����ǻỰ���ȵ����̣�N-��ʾ����ӵ�б���ͨ���ȼ����͵����ȼ���R-�������У�D-���ڵȴ���Z-�������̣�T-�����ٻ��߱�ֹͣ�ȵ�
STRAT�C����ܼ򵥣����Ǹý���������ʱ��
TIME�C�����Ѿ����ĵ�CPUʱ�䣬ע��������CPU��ʱ��
COMMOND�C��������ƺͲ���
��]#ps lax  ���Կ��������̣�ǫ��ֵ�Լ��ý������ڵȴ�����Դ�ȴ�