在Ubuntu上安装Docker
 https://www.cnblogs.com/ksir16/p/6530433.html
 
 这里记录的是社区版安装方式，由于平时只做开发使用所以不需要安装企业版，如果想了解企业版安装方式请参照官方文档。 
 
配置CE环境
配置apt允许以 HTTPS方式拉取镜像安装:

$ sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    software-properties-common
 

添加Docker官方 GPG key:

$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
 

校验 9DC8 5822 9FC7 DD38 854A E2D8 8D81 803C 0EBF CD88.

$ sudo apt-key fingerprint 0EBFCD88
 

利用如下命令配置稳定镜像
$ sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"
 

 安装Docker
更新apt包索引
$ sudo apt-get update
 

安装最新版Docker
sudo apt-get install docker-ce
 

验证Docker是否已经安装成功
$ sudo docker run hello-world
此命令会下载一个测试镜像，并且启动一个container来运行该镜像，打印一些信息后退出。

至此，Docker在Ubuntu上已经安装成功！