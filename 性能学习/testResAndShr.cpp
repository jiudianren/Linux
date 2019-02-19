

//g++ -g  -std=c++11 aa.cpp


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





int main(int argc, char *argv[])
{

    std::string opts ;

    std::cout
    <<"1:men"
    <<" 2:creat shared mem"
    <<" 3:attach mem"
    <<" 4:getpid"
    <<" 5:end"
    <<" 6:shm_write"
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

    while( std::getline(std::cin, opts))
    {
        if(opts.compare("1") ==0 )
        {
            mtime++;

            void * p =  malloc(memsize);
            memset(p ,0 ,memsize);

            std::cout << "  mem time :" << mtime;
        }
        else  if(opts.compare("2") == 0)
        {
            ftokId += 1;
            path += "_";
            path += std::to_string(ftokId);
            std::cout << "  ftokId:" << ftokId;
            std::cout << "  path:" << path;


            key_t key = ftok(path.c_str(), ftokId);

            int shmid = shmget(key , memsize, IPC_CREAT);
            std::cout << "  id :" << std::to_string(key) ;
            std::cout << "  shmid :" << shmid;
            vecshmid.push_back(shmid);

        }
        else if(opts.compare("3") == 0)
        {
            key_t key = ftok(path.c_str(), ftokId);
            int shmid = shmget(key , 0, SVSHM_MODE);

            int id = atoi(opts.c_str());
            void *   ptr = shmat(shmid, NULL ,0 );
            if(ptr == NULL)
            {
                std::cout << "  check the id " << std::endl;
            }
            else
            {
                std::cout << "shmat ok  " << std::endl;
            }

        }
        else if(opts.compare("6")  ==0 )
        {
            int shmid =0 ;
            if(0)
            {
                std::cout << "  please give me a shm id" << std::endl;
                std::getline(std::cin, opts);

                shmid = atoi(opts.c_str());
                std::cout << "  id is " <<   shmid << std::endl;
            }

            key_t key = ftok(path.c_str(), ftokId);
            shmid = shmget(key, 0, SVSHM_MODE);


            void *   ptr = shmat(shmid, NULL , 0);
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
                for (int i =0 ;i <  buff.shm_segsz;i ++)
                {
                    *cptr = i/256;
                }
                std::cout << "  memset the shm ok" << std::endl;
            }
        }
        else  if(opts.compare("4")  ==0 )
        {
            int  pid = getpid();
            std::cout <<"this  PID:" <<  pid << std::endl;
        }
        else  if(opts.compare("5")  ==0 )
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


