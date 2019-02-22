

//g++ -g   -fpermissive -std=c++11 aa.cpp


#include <string>
#include <string.h>
#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory>
#include <vector>


#define SVSHM_MODE (SHM_R | SHM_W | SHM_R>>3 | SHM_R>>6)


/*说明
 *
 * top -p  PID
 *
 * 看一下几项
 *
 * 程序启动
 *
 * top - 10:01:48 up 20 days, 22:07,  4 users,  load average: 0.13, 0.04, 0.01
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.3 us,  0.3 sy,  0.0 ni, 98.3 id,  1.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem :  8086556 total,  1478224 free,  1701252 used,  4907080 buff/cache
KiB Swap:        0 total,        0 free,        0 used.  5543908 avail Mem

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
 6378 aaav81    20   0   13284   1572   1432 S   0.0  0.0   0:00.00 a.out


 申请内存，而不 memset
  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
 6378 aaav81    20   0  115688   1572   1432 S   0.0  0.0   0:00.00 a.out

申请并，memset
6378 aaav81    20   0  218092 105448   2988 S   0.0  1.3   0:00.05 a.out

共享内存：
程序启动：

6944 aaav81    20   0   13284   1536   1400 S   0.0  0.0   0:00.00 a.out
 *
申请而不 memset:
6944 aaav81    20   0   13284   1536   1400 S   0.0  0.0   0:00.00 a.out

attach ,而不使用：
6944 aaav81    20   0  115684   1536   1400 S   0.0  0.0   0:00.00 a.out


aaav81@ubuntu:~$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 0          root       644        80         2
0x00000000 32769      root       644        16384      2
0x00000000 65538      root       644        280        2
0x0052e2c1 98307      gitlab-psq 600        2144108544 13
0x00000000 229380     aaav81     666        104857600  2          dest
0x0000231c 819205     aaav81     666        104857600  1


memset 申请到的共享内存：
 6944 aaav81    20   0  218084 105416 105244 S   0.0  1.3   0:00.07 a.out

可以看到  RES-SHR大概等于程序使用 内存

新开进程 memset共享内存：

6944 aaav81    20   0  218084 105416 105244 S   0.0  1.3   0:00.07 a.out
 *
 *
 *
 *
 *结论 ：
 内存：

 申请而不使用 ，只能反馈在 VIRT上，

 申请并且使用则反馈在VIRT 和RES上。

 对于共享内存，申请而不使用： VIRT RES 和SHR 都不会有什么变化。

 申请且使用

VIRT RES SHR 都会变化

其他进程A只attach到共享内存，而不使用

未attach:
 7969 aaav81    20   0   13284   1648   1508 S   0.0  0.0   0:00.00 a.out

attach :
7969 aaav81    20   0  115684   1648   1508 S   0.0  0.0   0:00.00 a.out


aaav81@ubuntu:~$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 0          root       644        80         2
0x00000000 32769      root       644        16384      2
0x00000000 65538      root       644        280        2
0x0052e2c1 98307      gitlab-psq 600        2144108544 13
0x00000000 229380     aaav81     666        104857600  2          dest
0x0000231c 819205     aaav81     666        104857600  3
0x00002380 851974     aaav81     666        104857600  0
0x000023e4 884743     aaav81     666        104857600  0

 其他进程b memset这个共享内存：

 ，则进程a的内存使用情况， VIRT RES,SHR都不会变



 进程a memset 共享内存后， SHR会发生变化。




 结论：
 1 申请而不使用内存，则只会表现在 VIRT上，
 2 使用已申请但尚未填入内容的内存，则反映在 RES上。
 3 只创建共享内存，SHR不会变化，
 4 指attach内存，SHR不会变化。
 5 其他进程使用共享内存，原来进程的SHR不会变化。
 6 本进程使用共享内存，则 shr发生辩护

  */


int main(int argc, char *argv[])
{

    std::string opts ;

    std::cout
    <<"1:men"
    <<" 2:creat shared mem"
    <<" 3:attach mem"
    <<" 4:show info"
    <<" 5:shm_write"
    <<" 6:end"
    <<std::endl;


    long memsize = 1024*1024*100;


    //for shared mem
    std::string path("/lpf/testRESAndSHR");
    int ftokId = 0;
    std::vector<int> vecshmid;

    //for mem
    int mtime = 0 ;

    int  pid = getpid();
    std::cout <<"this  PID:" <<  pid << std::endl;

    long long base_key = 8888;
    long long  step  =  100;
    while( std::getline(std::cin, opts))
    {
        if(opts.compare("1") ==0 )
        {
            mtime++;

            void * p =  malloc(memsize);
            std::cout << "  if you  want to memset this  mem ,please input 11:" << std::endl;
            std::getline(std::cin, opts);

            int opt = atoi(opts.c_str());
            if(opt == 11 )
            {
                memset(p ,0 ,memsize);
            }
            std::cout << "  mem time :" << mtime;
        }
        else  if(opts.compare("2") == 0)
        {
            if(0)
            {
                ftokId += 1;
                path += "_";
                path += std::to_string(ftokId);
                std::cout << "  ftokId:" << ftokId;
                std::cout << "  path:" << path;
                //key_t key = ftok(path.c_str(), ftokId);
            }

            base_key += step;
            int shmid = shmget(base_key, memsize, IPC_CREAT| 0666);
            if(shmid == -1)
            {
                perror("shmget error:");
            }
            std::cout << "  id :" << std::to_string(base_key) ;
            std::cout << "  shmid :" << shmid;
            vecshmid.push_back(shmid);
        }
        else if(opts.compare("3") == 0)
        {

            std::cout << "attach this program created shm ,please input : self" << std::endl;
            std::cout << "else attch shmid:  " << std::endl;

            std::getline(std::cin, opts);
            if (opts.compare("self") == 0)
            {
                for(auto it : vecshmid)
                  {
                      void *   ptr = shmat(it, NULL ,0 );
                      if(ptr == NULL)
                      {
                          std::cout << "  check the id " << std::endl;
                      }
                      else
                      {
                          std::cout << "shmat ok  " << std::endl;
                      }
                  }
            }
            else
            {
                std::cout << "  please give me a shm id" << std::endl;
                std::getline(std::cin, opts);

                int shmid = atoi(opts.c_str());
                std::cout << "  id is " <<   shmid << std::endl;
                void *   ptr = shmat(shmid, NULL, 0 );
                if(ptr == NULL)
                {
                    std::cout << "  check the id " << std::endl;
                }
                else
                {
                    std::cout << "shmat ok  " << std::endl;
                }

            }

        }
        else  if(opts.compare("4")  ==0 )
        {
            int  pid = getpid();
            std::cout <<"this  PID:" <<  pid << std::endl;
            std::cout << "shared mem id: ";
            for(auto it : vecshmid)
            {
                std::cout << " ," << std::to_string(it);
            }
            std::cout<<std::endl;
        }
        else if(opts.compare("5")  ==0 )
        {
            std::cout << "  please give me a shm id" << std::endl;
            std::getline(std::cin, opts);

            int shmid = atoi(opts.c_str());
            std::cout << "  id is " <<   shmid << std::endl;

            void * ptr = shmat(shmid, NULL, 0);
            if(ptr == NULL)
            {
                std::cout << "  check the id " << std::endl;
            }
            else
            {
                shmid_ds buff;
                shmctl(shmid, IPC_STAT, &buff );
                std::cout << "  memsize" << buff.shm_segsz << std::endl;
                std::flush(std::cout);

                char *  cptr = ptr;
                memset(cptr, '1', memsize);
                std::cout << "  memset the shm ok" << std::endl;
            }
        }
        else  if(opts.compare("6")  ==0 )
        {
            exit(0);
        }
        else
        {
            std::cout << "  no choose to deal this command"  << opts << std::endl;

            std::cout
            <<"1:men"
            <<" 2:creat shared mem"
            <<" 3:attach mem"
            <<" 4:getpid"
            <<" 5:end"
            <<" 6:shm_write"
            <<std::endl;

            std::cout << "  chose again" << std::endl;
        }
        opts.clear();
    }
    return 0;
}


