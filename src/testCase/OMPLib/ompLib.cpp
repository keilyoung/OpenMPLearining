#include<iostream>
#include <time.h>
#include <omp.h>
#include <windows.h>

using namespace std;


 /*
 头文件：#include <omp.h>
 指令的格式为： 
	#pragma omp 指令[子句][子句]
	比如#pragma omp parallel private(i,i)中 parallel是指令，pravate是子句。
 
 常用的OpenMP的指令有：
	parallel：用在一个代码段之前，表示这段代码将被多个线程并行执行。
	for:用于for循环之前，表示将循环分配到多个线程中并行执行，必须保证每次循环没有相关性。
	parallel for:用于for循环之前，表示将循环分配到多个线程中并行执行，必须保证每次循环没有相关性。
	sections:用在可能会被并行执行的代码段之前。
	parallel sections：parallel和sections两个语句的结合
	critical：用在一段代码的临界区之前。
	single:用在一段只被单个线程执行的代码段之前，表示后面的代码都将被单线程执行。
	barrier：用于并行区内代码的线程同步，所有线程执行到 barrier 时要停止，直到所有线程都执行到 barrier 时才
继续往下执行。
	atomic：用于指定一块内存区域被自动更新
	master：用亍指定一段代码块由主线程执行
	ordered：用亍指定并行区域的循环按顺序执行
	threadprivate：用于指定一个变量是线程私有的。

常用的库函数有：
	omp_get_num_procs, 返回运行本线程的多处理机的处理器个数。
	omp_get_num_threads, 返回当前并行区域中的活动线程个数。
	omp_get_thread_num, 返回线程号
	omp_set_num_threads, 设置并行执行代码时的线程个数
	omp_init_lock, 刜始化一个简单锁
	omp_set_lock， 上锁操作
	omp_unset_lock， 解锁操作， 要和 omp_set_lock 函数配对使用。
	omp_destroy_lock， omp_init_lock 函数的配对操作函数，关闭一个锁

常用的子句有：
	private, 指定每个线程都有它自己的变量私有副本。
	firstprivate， 指定每个线程都有它自己的变量私有副本，并且变量要被继承主线程中的刜值。
	lastprivate， 主要是用来指定将线程中的私有变量的值在并行处理结束后复制回主线程中的对应变量。
	reduce， 用来指定一个戒多个变量是私有的，并且在并行处理结束后这些变量要执行指定的运算。
	nowait， 忽略指定中暗吨的等待
	num_threads， 指定线程的个数
	schedule， 指定如何调度 for 循环迭代
	shared， 指定一个戒多个变量为多个线程间的共享变量
	ordered， 用来指定 for 循环的执行要按顺序执行
	copyprivate， 用亍 single 指令中的指定变量为多个线程的共享变量
	copyin， 用来指定一个 threadprivate 的变量的值要用主线程的值迚行刜始化。
	default， 用来指定并行处理区域内的变量的使用方式，缺省是 shared
 */

void simpleCaseCircle()
{
#pragma omp parallel for//指定后面的for循环变为并行执行
	for (int i = 0; i < 10; i++)
	{
		cout << "i=" << i << endl;
	}
}
void testcase()
{
	clock_t start = clock();

	clock_t end = clock();
	cout << "testcase0：time=" << end - start << endl;
}
 void testcase0()
 {
	 clock_t start = clock();
#pragma omp parallel for
	 for (int count = 0; count < 2; count++)
	 {
		 cout << "omp_get_num_threads:" << omp_get_num_procs() << endl;
		 int a = 0;
		 for (int i = 0; i < 10000000; i++)
		 {
			 a++;
		 }
	 }
	 clock_t end = clock();
	 cout << "testcase0：time=" << end - start << endl;
 }
 void testcase1()
 {
	 /*
	 parallel指令用来构造一个并行块，用大括号括起来
	 #pragma omp parallel [for | sections] [子句[子句]…]
		{
			代码
		}

	 */
	 clock_t start = clock();
#pragma omp parallel
	 {
		 cout << "当前线程：" << omp_get_thread_num() << endl;
	 }
	 cout << "---------------------------------" << endl;
	 //也可以指定使用多少个线程来执行，使用num_threads子句
#pragma omp parallel num_threads(10)
	 {
		 cout << "当前线程：" << omp_get_thread_num() << endl;
	 }
	 clock_t end = clock();
	 cout << "testcase0：time=" << end - start << endl;
 }
 void testcase2()
 {
	 /*
	 for指令则是用来将一个 for 循环分配到多个线程中执行。 for 指令一般可以和 parallel 指令合起来形成 parallel for
指令使用，也可以单独用在 parallel 语句的并行块中。
	#pragma omp [parallel] for [子句]
		for 循环语句
	 
	 */
	 clock_t start = clock();
	 //用法1
#pragma omp parallel for
	 for (int i=0;i<10;i++)
	 {
		 cout << "当前线程：" << omp_get_thread_num() << endl;
	 }
	 cout << "------------------------------------" << endl;
	 //用法2
#pragma omp parallel
	 {
#pragma omp for
		 for (int i = 0; i < 10; i++)
		 {
			 cout << "当前线程：" << omp_get_thread_num() << endl;
		 }
	 
	 }
	 cout << "------------------------------------" << endl;
	 //用法3
#pragma omp parallel
	 {
#pragma omp for
		 for (int i = 0; i < 10; i++)
		 {
			 cout << "当前线程：" << omp_get_thread_num() << endl;
		 }
		 cout << "------------------------------------" << endl;
#pragma omp for
		 for (int i = 0; i < 10; i++)
		 {
			 cout << "当前线程：" << omp_get_thread_num() << endl;
		 }

	 }
	 cout << "------------------------------------" << endl;

	 clock_t end = clock();
	 cout << "testcase0：time=" << end - start << endl;
 }
 void testcase3()
 {
  /*
  section语句
  section 语句是用在 sections 语句里用来将 sections 语句里的代码划分成几个不同的段，每段都并行执行。


  */
	 clock_t start = clock();
//#pragma omp parallel sections{
//#pragma omp section
//	 { std::cout << "section 1 ThreadId = " << omp_get_thread_num(); }	 
//#pragma omp section
//	 { std::cout << "section 2 ThreadId = " << omp_get_thread_num(); }	 
//#pragma omp section
//	 { std::cout << "section 3 ThreadId = " << omp_get_thread_num(); }	 
//#pragma omp section
//	 { std::cout << "section 4 ThreadId = " << omp_get_thread_num(); }
//}

	 clock_t end = clock();
	 cout << "testcase0：time=" << end - start << endl;
 }

 //OpenMP中数据处理子句
 void testcase4()
 {
	 /*
	 1、pravate子句
	 private 子句用于将一个或多个变量声明成线程私有的变量，变量声明成私有变量后，指定每个线程都有它自
己的变量私有副本，其他线程无法访问私有副本。即使在并行区域外有同名的共享变量，共享变量在并行区域内不
起任何作用，并且并行区域内不会操作到外面的共享变量。
	 */
	 int k = 100;
#pragma omp parallel for private(k)
	 for (k=0;k<10;k++)
	 {
		 cout << "k=" << k << endl;
	 }

	 cout << "last k=" << k << endl;//k还是等于100
	 cout << "---------------------------------------------" << endl;
	 /*
	 2、firstprivate 子句
	 private 声明的私有变量丌能继承同名变量的值，但实际情况中有时需要继承原有共享变量的值， OpenMP 提
供了 firstprivate 子句来实现这个功能。
	 */
	 int k2 = 100;
#pragma omp parallel for firstprivate(k2)
	 for (int i = 0; i < 4; i++)
	 {
		 k2 += i;
		 printf("k2=%d\n", k2);
	 }
	 printf("last k2=%d\n", k2);
	 cout << "---------------------------------------------" << endl;

	 /*
	 lastprivate 子句
	 有时在并行区域内的私有变量的值经过计算后，在退出并行区域时，需要将它的值赋给同名的共享变量，前面
的 private 和 firstprivate 子句在退出并行区域时都没有将私有变量的最后取值赋给对应的共享变量， lastprivate
子句就是用来实现在退出并行区域时将私有变量的值赋给共享变量。
	 */
	 int k3 = 100;
#pragma omp parallel for firstprivate(k3),lastprivate(k3)
	 for (int i = 0; i < 4; i++)
	 {
		 k3 += i;
		 printf("k3=%d\n", k3);
	 }
	 printf("last k3=%d\n", k3);


	 clock_t start = clock();

	 clock_t end = clock();
	 cout << "testcase4：time=" << end - start << endl;
 }

 //OpenMP中的任务调度
 /*
 Schedule子句用法
 格式：schedule(type[,size])
 type:表示调度类型，有四种调度类型
	 1、dynamic
	 2、guided
	 3、runtime
	 4、static
 其中runtime实际上是根据环境变量来选择前三种中的某种类型
 size：（可选）
	表示循环迭代次数，size参数必须是整数。static、 dynamic、 guided 三种调度方式都可以使用 size
参数，也可以丌使用 size 参数。当 type 参数类型为 runtime 时， size 参数是非法的（丌需要使用，如果使用的话
编译器会报错）。
 
 静态调度（static）
	当parallel for编译指导语句没有带schedule子句时，大部分系统中默认使用static调度方式。假设有n次循环迭代，
 t个线程，那么每个线程静态分配大约n/t次迭代计算。如果指定了size参数的话，那么可能相差一个size。
	当静态调度不使用size参数时，用法为：schedule(static)
	当使用size参数时，给每个线程分配size次连续的迭代计算，用法：schedule(static，size)
	见testcase5()。

 动态调度（dynamic）
	动态调度是动态地将迭代分配到各个线程，动态调度可以使用也可不用size参数，不使用size时是将迭代逐个分配到各个线程，
 使用size时，每次分配给线程的迭代次数为指定的size次。
 与静态调度的区别：当静态调度不指定size，会将连续的前n/t个分给线程0，依次分下去，而动态调度是逐个分
	见testcase6()。

 guided调度（guided）
	采用一种指导性的启发式自调度方法。开始每个线程会分到较大的迭代块，之后分到的迭代块会逐渐变小。迭代块的大小会按
 指数级下降到指定的size大小，如果没有指定size，那么会下降到1.
	见testcase7()。

 runtime调度：
	runtime 调度并丌是和前面三种调度方式似的真实调度方式，它是在运行时根据环境变量 OMP_SCHEDULE
 来确定调度类型，最终使用的调度类型仌然是上述三种调度方式中的某种。
 上述命令设置调度类型为劢态调度，劢态调度的迭代次数为 2。
 在 windows 环境中，可以在” 系统属性|高级|环境变量” 对话框中迚行设置环境变量。
 
 */

 void testcase5()
 {
	 int i;
#pragma omp  parallel for schedule(static,3)
	 for (i=0;i<8;i++)
	 {
		 cout << "i=" << i << ",thread_id=" << omp_get_thread_num() << endl;
		 Sleep(10);
	 }


	 clock_t start = clock();
	 clock_t end = clock();
	 cout << "testcase5：time=" << end - start << endl;
 }

 void testcase6()
 {
	 int i;
#pragma omp  parallel for schedule(dynamic,3)
	 for (i = 0; i < 8; i++)
	 {
		 cout << "i=" << i << ",thread_id=" << omp_get_thread_num() << endl;
		 Sleep(10);
	 }


	 clock_t start = clock();
	 clock_t end = clock();
	 cout << "testcase6：time=" << end - start << endl;
 }

 void testcase7()
 {
	 int i;
#pragma omp  parallel for schedule(guided,3)
	 for (i = 0; i < 30; i++)
	 {
		 cout << "i=" << i << ",thread_id=" << omp_get_thread_num() << endl;
		 Sleep(10);
	 }


	 clock_t start = clock();
	 clock_t end = clock();
	 cout << "testcase7：time=" << end - start << endl;
 }



int main1()
{
	//simpleCaseCircle();
	testcase6();

	system("pause");
	return 0;
}