
http://www.voidcn.com/article/p-uuiihfmf-mx.html
https://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index1.html
https://www.ibm.com/developerworks/cn/linux/l-ipc/part5/index2.html?ca=drs-
https://blog.csdn.net/liu0808/article/details/73821748

�� 4 ���� �����ڴ�
�����ڴ�������ipc��ʽ��ԭ���Ǽ��������ں˺��û��ռ�Ŀ���

#ȱʡ����� fork�������ӽ��̲����븸���̹��� �����ڴ�

mmap ������Ŀ��
1��ʹ����ͨ�ļ������ṩ�ڴ�ӳ��
2 ʹ�������ļ������ṩ�����ڴ�ӳ��
3 ʹ��shm_open���ṩ����Ե��ϵ�Ľ��̼��posix�����ڴ�

void * mmap() 

mmap��� �����ڴ��ָ��ĵ�ַ

�򿪹����ڴ� ��Ҫһ��fd


 munmap msync

����12.6��
����Ե��ϵ�� ���̼乲���ڴ��������ַ�����

open �ڴ�ӳ���ļ� ���򿪵����ļ���
shm_open �����ڴ������� ���򿪵ľ�����һ����־��
shm_open(const char *name ,int ,mode_t )
shm_unlink

int ftruncate(int fd ,off_t length)
�޸Ĺ����ڴ�����ļ��Ĵ�С 




int fstat()
��ȡ�����ڴ�Ķ���������Ϣ



ͬһ�����ڴ�ӳ�䵽��ͬ���̵ĵ�ַ�ռ�ʱ����ʼ��ַ���Բ�һ����


�����ڴ棬ʾ����
