https://www.jianshu.com/p/e2dfccc32c80


以下情况不宜使用内联：

（1）如果函数体内的代码比较长，使用内联将导致内存消耗代价较高。

（2）如果函数体内出现循环，那么执行函数体内代码的时间要比函数调用的开销大。

一个好的编译器将会根据函数的定义体，自动地取消不值得的内联

noreturn
cleanup


  void clean_up_func() {
       printf("my clean_up_func\n");
  }

  void test_clean_up() {

      int __attribute__((cleanup(clean_up_func)))  iMy =10;
  }
  
  

void myexit(int)__attribute__((noreturn));
  
  /* no return */
void myexit(int r)  {
    do
    {
        printf("my exit %d \n",r);
    }
    while(0);
}
int test_noreturn(int n)
{
    if ( n > 0 )
    {
        myexit(n);
        /* 程序不可能到达这里*/
    }
    else
    {

        return 0;
    }
}
