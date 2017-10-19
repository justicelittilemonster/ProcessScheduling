#include<stdio.h>
#include<stdlib.h>
#include"process.h"

extern ListNode *set_pcb();   //将文件内的进程信息导入到结构体
extern void create_time();//创建时间片
extern void print_process(ListNode *p);//输出队列进程信息
extern void time_peace_schedul(ListNode *p);//时间片调度
extern ListNode *ready;             //就绪队列
extern ListNode *run;               //运行队列
extern ListNode *finish;			 //完成队列
extern ListNode *ready_in(ListNode *ready,ListNode *q);//用尾插法将进程q压入就绪队列
extern ListNode *ready_out(ListNode *ready); //从就绪队列取出首进程为进程q
extern ListNode *initial_duilie(ListNode *p);//初始化队列



int main()
{
	ListNode *s;
	ListNode *tmp,*tmp2;
	int i = 0;
	create_time();
	initial_duilie(ready);
	s=set_pcb();
	tmp = ready_out(s);
	ready_in(ready, tmp);
		print_process(ready);
	//tmp2= ready_out(s);
	//ready_in(ready,s->next->next);
	//time_peace_schedul(s);
	
	print_process(s);
	system("pause");
	getchar();
	

}