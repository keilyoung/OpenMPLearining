#include<iostream>
#include <time.h>
#include <omp.h>
#include <windows.h>

using namespace std;


 /*
 ͷ�ļ���#include <omp.h>
 ָ��ĸ�ʽΪ�� 
	#pragma omp ָ��[�Ӿ�][�Ӿ�]
	����#pragma omp parallel private(i,i)�� parallel��ָ�pravate���Ӿ䡣
 
 ���õ�OpenMP��ָ���У�
	parallel������һ�������֮ǰ����ʾ��δ��뽫������̲߳���ִ�С�
	for:����forѭ��֮ǰ����ʾ��ѭ�����䵽����߳��в���ִ�У����뱣֤ÿ��ѭ��û������ԡ�
	parallel for:����forѭ��֮ǰ����ʾ��ѭ�����䵽����߳��в���ִ�У����뱣֤ÿ��ѭ��û������ԡ�
	sections:���ڿ��ܻᱻ����ִ�еĴ����֮ǰ��
	parallel sections��parallel��sections�������Ľ��
	critical������һ�δ�����ٽ���֮ǰ��
	single:����һ��ֻ�������߳�ִ�еĴ����֮ǰ����ʾ����Ĵ��붼�������߳�ִ�С�
	barrier�����ڲ������ڴ�����߳�ͬ���������߳�ִ�е� barrier ʱҪֹͣ��ֱ�������̶߳�ִ�е� barrier ʱ��
��������ִ�С�
	atomic������ָ��һ���ڴ������Զ�����
	master����ءָ��һ�δ���������߳�ִ��
	ordered����ءָ�����������ѭ����˳��ִ��
	threadprivate������ָ��һ���������߳�˽�еġ�

���õĿ⺯���У�
	omp_get_num_procs, �������б��̵߳Ķദ����Ĵ�����������
	omp_get_num_threads, ���ص�ǰ���������еĻ�̸߳�����
	omp_get_thread_num, �����̺߳�
	omp_set_num_threads, ���ò���ִ�д���ʱ���̸߳���
	omp_init_lock, �_ʼ��һ������
	omp_set_lock�� ��������
	omp_unset_lock�� ���������� Ҫ�� omp_set_lock �������ʹ�á�
	omp_destroy_lock�� omp_init_lock ��������Բ����������ر�һ����

���õ��Ӿ��У�
	private, ָ��ÿ���̶߳������Լ��ı���˽�и�����
	firstprivate�� ָ��ÿ���̶߳������Լ��ı���˽�и��������ұ���Ҫ���̳����߳��еĄ_ֵ��
	lastprivate�� ��Ҫ������ָ�����߳��е�˽�б�����ֵ�ڲ��д���������ƻ����߳��еĶ�Ӧ������
	reduce�� ����ָ��һ������������˽�еģ������ڲ��д����������Щ����Ҫִ��ָ�������㡣
	nowait�� ����ָ���а��ֵĵȴ�
	num_threads�� ָ���̵߳ĸ���
	schedule�� ָ����ε��� for ѭ������
	shared�� ָ��һ����������Ϊ����̼߳�Ĺ������
	ordered�� ����ָ�� for ѭ����ִ��Ҫ��˳��ִ��
	copyprivate�� ��ء single ָ���е�ָ������Ϊ����̵߳Ĺ������
	copyin�� ����ָ��һ�� threadprivate �ı�����ֵҪ�����̵߳�ֵމ�Є_ʼ����
	default�� ����ָ�����д��������ڵı�����ʹ�÷�ʽ��ȱʡ�� shared
 */

void simpleCaseCircle()
{
#pragma omp parallel for//ָ�������forѭ����Ϊ����ִ��
	for (int i = 0; i < 10; i++)
	{
		cout << "i=" << i << endl;
	}
}
void testcase()
{
	clock_t start = clock();

	clock_t end = clock();
	cout << "testcase0��time=" << end - start << endl;
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
	 cout << "testcase0��time=" << end - start << endl;
 }
 void testcase1()
 {
	 /*
	 parallelָ����������һ�����п飬�ô�����������
	 #pragma omp parallel [for | sections] [�Ӿ�[�Ӿ�]��]
		{
			����
		}

	 */
	 clock_t start = clock();
#pragma omp parallel
	 {
		 cout << "��ǰ�̣߳�" << omp_get_thread_num() << endl;
	 }
	 cout << "---------------------------------" << endl;
	 //Ҳ����ָ��ʹ�ö��ٸ��߳���ִ�У�ʹ��num_threads�Ӿ�
#pragma omp parallel num_threads(10)
	 {
		 cout << "��ǰ�̣߳�" << omp_get_thread_num() << endl;
	 }
	 clock_t end = clock();
	 cout << "testcase0��time=" << end - start << endl;
 }
 void testcase2()
 {
	 /*
	 forָ������������һ�� for ѭ�����䵽����߳���ִ�С� for ָ��һ����Ժ� parallel ָ��������γ� parallel for
ָ��ʹ�ã�Ҳ���Ե������� parallel ���Ĳ��п��С�
	#pragma omp [parallel] for [�Ӿ�]
		for ѭ�����
	 
	 */
	 clock_t start = clock();
	 //�÷�1
#pragma omp parallel for
	 for (int i=0;i<10;i++)
	 {
		 cout << "��ǰ�̣߳�" << omp_get_thread_num() << endl;
	 }
	 cout << "------------------------------------" << endl;
	 //�÷�2
#pragma omp parallel
	 {
#pragma omp for
		 for (int i = 0; i < 10; i++)
		 {
			 cout << "��ǰ�̣߳�" << omp_get_thread_num() << endl;
		 }
	 
	 }
	 cout << "------------------------------------" << endl;
	 //�÷�3
#pragma omp parallel
	 {
#pragma omp for
		 for (int i = 0; i < 10; i++)
		 {
			 cout << "��ǰ�̣߳�" << omp_get_thread_num() << endl;
		 }
		 cout << "------------------------------------" << endl;
#pragma omp for
		 for (int i = 0; i < 10; i++)
		 {
			 cout << "��ǰ�̣߳�" << omp_get_thread_num() << endl;
		 }

	 }
	 cout << "------------------------------------" << endl;

	 clock_t end = clock();
	 cout << "testcase0��time=" << end - start << endl;
 }
 void testcase3()
 {
  /*
  section���
  section ��������� sections ����������� sections �����Ĵ��뻮�ֳɼ�����ͬ�ĶΣ�ÿ�ζ�����ִ�С�


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
	 cout << "testcase0��time=" << end - start << endl;
 }

 //OpenMP�����ݴ����Ӿ�
 void testcase4()
 {
	 /*
	 1��pravate�Ӿ�
	 private �Ӿ����ڽ�һ�����������������߳�˽�еı���������������˽�б�����ָ��ÿ���̶߳�������
���ı���˽�и����������߳��޷�����˽�и�������ʹ�ڲ�����������ͬ���Ĺ����������������ڲ��������ڲ�
���κ����ã����Ҳ��������ڲ������������Ĺ��������
	 */
	 int k = 100;
#pragma omp parallel for private(k)
	 for (k=0;k<10;k++)
	 {
		 cout << "k=" << k << endl;
	 }

	 cout << "last k=" << k << endl;//k���ǵ���100
	 cout << "---------------------------------------------" << endl;
	 /*
	 2��firstprivate �Ӿ�
	 private ������˽�б���آ�ܼ̳�ͬ��������ֵ����ʵ���������ʱ��Ҫ�̳�ԭ�й��������ֵ�� OpenMP ��
���� firstprivate �Ӿ���ʵ��������ܡ�
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
	 lastprivate �Ӿ�
	 ��ʱ�ڲ��������ڵ�˽�б�����ֵ������������˳���������ʱ����Ҫ������ֵ����ͬ���Ĺ��������ǰ��
�� private �� firstprivate �Ӿ����˳���������ʱ��û�н�˽�б��������ȡֵ������Ӧ�Ĺ�������� lastprivate
�Ӿ��������ʵ�����˳���������ʱ��˽�б�����ֵ�������������
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
	 cout << "testcase4��time=" << end - start << endl;
 }

 //OpenMP�е��������
 /*
 Schedule�Ӿ��÷�
 ��ʽ��schedule(type[,size])
 type:��ʾ�������ͣ������ֵ�������
	 1��dynamic
	 2��guided
	 3��runtime
	 4��static
 ����runtimeʵ�����Ǹ��ݻ���������ѡ��ǰ�����е�ĳ������
 size������ѡ��
	��ʾѭ������������size����������������static�� dynamic�� guided ���ֵ��ȷ�ʽ������ʹ�� size
������Ҳ����آʹ�� size �������� type ��������Ϊ runtime ʱ�� size �����ǷǷ��ģ�آ��Ҫʹ�ã����ʹ�õĻ�
�������ᱨ����
 
 ��̬���ȣ�static��
	��parallel for����ָ�����û�д�schedule�Ӿ�ʱ���󲿷�ϵͳ��Ĭ��ʹ��static���ȷ�ʽ��������n��ѭ��������
 t���̣߳���ôÿ���߳̾�̬�����Լn/t�ε������㡣���ָ����size�����Ļ�����ô�������һ��size��
	����̬���Ȳ�ʹ��size����ʱ���÷�Ϊ��schedule(static)
	��ʹ��size����ʱ����ÿ���̷߳���size�������ĵ������㣬�÷���schedule(static��size)
	��testcase5()��

 ��̬���ȣ�dynamic��
	��̬�����Ƕ�̬�ؽ��������䵽�����̣߳���̬���ȿ���ʹ��Ҳ�ɲ���size��������ʹ��sizeʱ�ǽ�����������䵽�����̣߳�
 ʹ��sizeʱ��ÿ�η�����̵߳ĵ�������Ϊָ����size�Ρ�
 �뾲̬���ȵ����𣺵���̬���Ȳ�ָ��size���Ὣ������ǰn/t���ָ��߳�0�����η���ȥ������̬�����������
	��testcase6()��

 guided���ȣ�guided��
	����һ��ָ���Ե�����ʽ�Ե��ȷ�������ʼÿ���̻߳�ֵ��ϴ�ĵ����飬֮��ֵ��ĵ�������𽥱�С��������Ĵ�С�ᰴ
 ָ�����½���ָ����size��С�����û��ָ��size����ô���½���1.
	��testcase7()��

 runtime���ȣ�
	runtime ���Ȳ�آ�Ǻ�ǰ�����ֵ��ȷ�ʽ�Ƶ���ʵ���ȷ�ʽ������������ʱ���ݻ������� OMP_SCHEDULE
 ��ȷ���������ͣ�����ʹ�õĵ������́�Ȼ���������ֵ��ȷ�ʽ�е�ĳ�֡�
 �����������õ�������Ϊ۽̬���ȣ�۽̬���ȵĵ�������Ϊ 2��
 �� windows �����У������ڡ� ϵͳ����|�߼�|���������� �Ի�����މ�����û���������
 
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
	 cout << "testcase5��time=" << end - start << endl;
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
	 cout << "testcase6��time=" << end - start << endl;
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
	 cout << "testcase7��time=" << end - start << endl;
 }



int main1()
{
	//simpleCaseCircle();
	testcase6();

	system("pause");
	return 0;
}