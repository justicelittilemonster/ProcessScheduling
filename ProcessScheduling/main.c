#include<stdio.h>
#include<stdlib.h>
#include"process.h"

extern ListNode *set_pcb();   //���ļ��ڵĽ�����Ϣ���뵽�ṹ��
extern void create_time();//����ʱ��Ƭ
extern void print_process(ListNode *p);//������н�����Ϣ
extern void time_peace_schedul(ListNode *p);//ʱ��Ƭ����
extern ListNode *ready;             //��������
extern ListNode *run;               //���ж���
extern ListNode *finish;			 //��ɶ���
extern ListNode *ready_in(ListNode *ready,ListNode *q);//��β�巨������qѹ���������
extern ListNode *ready_out(ListNode *ready); //�Ӿ�������ȡ���׽���Ϊ����q
extern ListNode *initial_duilie(ListNode *p);//��ʼ������



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