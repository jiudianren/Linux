#perf ��װ

http://www.voidcn.com/article/p-ttwwedfy-qb.html

apt install linux-tools-common


https://www.cnblogs.com/arnoldlu/p/6241297.html 

��װ perf �ǳ���, ֻҪ�ں˰汾����2.6.31��, perf�Ѿ����ں�֧��. ���Ȱ�װ�ں�Դ��:
apt-get install linux-source
��ô�� /usr/src Ŀ¼�¾��Ѿ����غ����ں�Դ��, ���Ƕ�Դ������н�ѹ, Ȼ����� tools/perf Ŀ¼Ȼ������������������ɣ�

make
make install



��װ perf �ǳ���, ֻҪ�ں˰汾����2.6.31��, perf�Ѿ����ں�֧��. ���Ȱ�װ�ں�Դ��:
apt-get install linux-source
��ô�� /usr/src Ŀ¼�¾��Ѿ����غ����ں�Դ��, ���Ƕ�Դ������н�ѹ, Ȼ����� tools/perf Ŀ¼Ȼ������������������ɣ�

make
make install
������Ϊϵͳԭ��, ��Ҫ��ǰ��װ����Ŀ�����:
apt-get install -y binutils-dev
apt-get install -y libdw-dev
apt-get install -y python-dev
apt-get install -y libnewt-dev

http://blog.chinaunix.net/uid-10540984-id-3854969.html


Ϊʲô�أ���Ϊ GDB ���Գ���Ĺ��̻��жϳ������У��������ϻ��������ǲ�����ġ�
���ԣ�GDB ֻ�ʺ��������ܷ����ĺ��ڣ������ҵ��˳�����Ĵ��º�����
�����ٽ���������һ�����Ժ����ڲ������⡣ ��ô���ֹ����ʺ��ڵ�һʱ��������̵� CPU �����أ��ҵ��Ƽ��� perf��

perf �� Linux 2.6.31 �Ժ����õ����ܷ������ߡ�
���������¼�����Ϊ�������������Է���ϵͳ�ĸ����¼����ں����ܣ���������������ָ��Ӧ�ó�����������⡣ 
ʹ�� perf ���� CPU �������⣬����˵���������Ҳ������ϲ�����÷���


https://blog.csdn.net/trochiluses/article/details/10261339