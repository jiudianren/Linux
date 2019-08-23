
http://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html


1. __attribute__

GNU C的一大特色（却不被初学者所知）就是__attribute__机制。

__attribute__可以设置函数属性(Function Attribute)、变量属性(Variable Attribute)和类型属性(Type Attribute)

__attribute__前后都有两个下划线，并且后面会紧跟一对原括弧，括弧里面是相应的__attribute__参数

__attribute__语法格式为：

__attribute__ ( ( attribute-list ) )

函数属性（Function Attribute），函数属性可以帮助开发者把一些特性添加到函数声明中，从而可以使编译器在错误检查方面的功能更强大。

__attribute__机制也很容易同非GNU应用程序做到兼容。

GNU CC需要使用 –Wall，这是控制警告信息的一个很好的方式。下面介绍几个常见的属性参数。

# finstrument-functions

该参数可以使程序在编译时，在函数的入口和出口处生成instrumentation调用。恰好在函数入口之后并恰好在函数出口之前，将使用当前函数的地址和调用地址来调用下面的profiling函数。（在一些平台上，__builtin_return_address不能在超过当前函数范围之外正常工作，所以调用地址信息可能对profiling函数是无效的）

void  __cyg_profile_func_enter( void  *this_fn，void  *call_site );

void  __cyg_profile_func_exit( void  *this_fn，void  *call_site );

其中，第一个参数this_fn是当前函数的起始地址，可在符号表中找到；第二个参数call_site是调用处地址。


# instrumentation

也可用于在其它函数中展开的内联函数。从概念上来说，profiling调用将指出在哪里进入和退出内联函数。这就意味着这种函数必须具有可寻址形式。如果函数包含内联，而所有使用到该函数的程序都要把该内联展开，这会额外地增加代码长度。如果要在C 代码中使用extern inline声明，必须提供这种函数的可寻址形式。
可对函数指定no_instrument_function属性，在这种情况下不会进行 instrumentation操作。例如，可以在以下情况下使用no_instrument_function属性：上面列出的profiling函数、高优先级的中断例程以及任何不能保证profiling正常调用的函数。

no_instrument_function

如果使用了-finstrument-functions，将在绝大多数用户编译的函数的入口和出口点调用profiling函数。使用该属性，将不进行instrument操作。


#  const

该属性只能用于带有数值类型参数的函数上，当重复调用带有数值参数的函数时，由于返回值是相同的。所以此时编译器可以进行优化处理，除第一次需要运算外， 其它只需要返回第一次的结果。

该属性主要适用于没有静态状态（static state）和副作用的一些函数，并且返回值仅仅依赖输入的参数。为了说明问题，下面举个非常“糟糕”的例子，该例子将重复调用一个带有相同参数值的函数，具体如下：

extern int  square( int  n ) __attribute__ ( (const) );

for (i = 0; i < 100; i++ )                 

{      

       total += square (5) + i;            

}

添加__attribute__((const))声明，编译器只调用了函数一次，以后只是直接得到了相同的一个返回值。

事实上，const参数不能用在带有指针类型参数的函数中，因为该属性不但影响函数的参数值，同样也影响到了参数指向的数据，它可能会对代码本身产生严重甚至是不可恢复的严重后果。并且，带有该属性的函数不能有任何副作用或者是静态的状态，类似getchar（）或time（）的函数是不适合使用该属性。


# . 和非GNU编译器的兼容性

__attribute__设计的非常巧妙，很容易作到和其它编译器保持兼容。也就是说，如果工作在其它的非GNU编译器上，可以很容易的忽略该属性。即使__attribute__使用了多个参数，也可以很容易的使用一对圆括弧进行处理，例如：

 /* 如果使用的是非GNU C, 那么就忽略__attribute__ */

#ifndef __GNUC__

      #define     __attribute__(x)     /* NOTHING * /

#endif

需要说明的是，__attribute__适用于函数的声明而不是函数的定义。所以，当需要使用该属性的函数时，必须在同一个文件里进行声明，例如：

/* 函数声明 */

void  die( const char *format， ... ) __attribute__( (noreturn) )   __attribute__( ( format(printf，1，2) ) );

void  die( const char *format，... )

{   /* 函数定义 */  }

更多属性参考

# constructor-destructor

　若函数被设定为constructor属性，则该函数会在main（）函数执行之前被自动的执行。类似的，若函数被设定为destructor属性，则该函数会在main（）函数执行之后或者exit（）被调用后被自动的执行。
 
 可以看到全局类的构造过程发生在before_main()函数前面,而析构也发生在after_main()前面.
 
   #include <stdio.h>
  #include <stdlib.h>
  static int * g_count = NULL;
  __attribute__((constructor)) void load_file()
  {
      printf("Constructor is called.\n");
      g_count = (int *)malloc(sizeof(int));
      if (g_count == NULL)
      {
      fprintf(stderr, "Failed to malloc memory.\n");
      }
  }
  __attribute__((destructor)) void unload_file()
  {
      printf("destructor is called.\n");
      if (g_count)
      free(g_count);
  }
  int main()
  {
      return 0;
  }



https://www.jianshu.com/p/e2dfccc32c80


以下情况不宜使用内联：

（1）如果函数体内的代码比较长，使用内联将导致内存消耗代价较高。

（2）如果函数体内出现循环，那么执行函数体内代码的时间要比函数调用的开销大。

一个好的编译器将会根据函数的定义体，自动地取消不值得的内联

# cleanup


  void clean_up_func() {
       printf("my clean_up_func\n");
  }

  void test_clean_up() {

      int __attribute__((cleanup(clean_up_func)))  iMy =10;
  }
  
#  packed

使用该属性可以使得变量或者结构体成员使用最小的对齐方式，即对变量是一字节对齐，对域（field）是位对齐。使用该属性对struct或者union类型进行定义，设定其类型的每一个变量的内存约束。当用在enum类型定义时，暗示了应该使用最小完整的类型 （it indicates that the smallest integral type should be used）。

下面的例子中，x成员变量使用了该属性，则其值将紧放置在a的后面：

struct  test

{

      char  a;

      int  x[2] __attribute__ ((packed));

};

下面的例子中，my-packed-struct类型的变量数组中的值将会紧紧的靠在一起，但内部的成员变量s不会被“pack”，如果希望内部的成员变量也被packed，my-unpacked-struct也需要使用packed进行相应的约束。

struct my_packed_struct

{

        char  c;

        int  i;

        struct  my_unpacked_struct  s;

}__attribute__ ( (__packed__) );

其它可选的属性值还可以是：cleanup，common，nocommon，deprecated，mode，section，shared， tls_model，transparent_union，unused，vector_size，weak，dllimport，dlexport等。
  
# noreturn
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
