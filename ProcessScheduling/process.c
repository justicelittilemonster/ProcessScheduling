#include<stdio.h>
#include<stdlib.h>
#include"process.h"


ListNode *ready;             //��������
ListNode *run;               //���ж���
ListNode *finish;			 //��ɶ���






int time_peace;

ListNode *initial_duilie(ListNode *p)//��ʼ������
{
	p= (ListNode*)malloc(sizeof(ListNode));
	p->next = NULL;
	return p;
}

ListNode *set_pcb()                  //�����ļ��ڵĽ�����Ϣ
{
	int i=0;
	ListNode *q,*r;
	ListNode *p;				 //������̶���
	FILE *fp;
	p=(ListNode*)malloc(sizeof(ListNode));
	
	p->next = NULL;
	r=p;
	fp=fopen("process.txt","r");//process.txt�ļ��ڰ���������Ϣ
	if(fp == NULL)
		return 0;
	
	while(!feof(fp) && i<PRO_NUM)
	{
		q=(ListNode*)malloc(sizeof(ListNode));
		fscanf(fp, "%d%s%d%d%d%d%lf",&q->Process_Id,q->Process_Name, &q->Time_Arrive, &q->Time_Serve,  &q->Time_wait, &q->Time_Finish,  &q->Response);
		q->next=r->next; 
		
		r->next=q;
		r=q;
		i++;
	}
	r->next=NULL;
	fclose(fp);
	return p;
}


void create_time()  //����ʱ��Ƭ      BUG:������Ϊһ���ַ���ʱ������ַ��������е���ʾ����Ӱ������ʹ�á�
{
	printf("������ʱ��Ƭ�ĳ��ȣ�");
	while(1)        //�ж������Ƿ�Ϸ�
	{
		if(scanf("%d",&time_peace) == 1) //ͨ��scanf����ֵ�ж������Ƿ�Ϊ����
		{
			if(time_peace <=0 || time_peace > 65535) //�ж����뷶Χ�Ƿ�Ϸ�
			{
				printf("����ʱ��Ƭ����\n");
				continue;
			}
			else  //�����ȷ������
			{
				break;
			}
		}
		
		else	 //������Ƿ�����
		{
			printf("��������ȷ��ʱ��Ƭ\n");
			getchar();           //getchar���ջس�
		}	               
	}
}



ListNode *ready_in(ListNode *ready,ListNode *q) //��β�巨������qѹ���������
{
	ListNode *tmp,*p;
	p= (ListNode*)malloc(sizeof(ListNode));
	tmp=(ListNode*)malloc(sizeof(ListNode));
	tmp=ready->next;
	
	p=(ListNode*)malloc(sizeof(ListNode));
	p=q->next;
	if(!tmp)//���readyΪNULL
	{
		tmp=p;
		tmp->next=NULL;
	}
	else
	{
		while(tmp->next)
		{
			tmp=tmp->next;
		}
	
		p->next=tmp->next;
		tmp->next=p;
		//tmp=p;
		//tmp->next=NULL;
	}
	
}


ListNode *ready_out(ListNode *ready) //�Ӿ�������ȡ���׽���
{
	ListNode *q,*tmp;
	q= (ListNode*)malloc(sizeof(ListNode));
	//q = ready;
	if(ready->next)
	{
		
		tmp=ready->next;
		//tmp = q->next;
		ready->next = ready->next->next;
		tmp->next = NULL;
		//ready=ready->next;
		//ready = NULL;//���¶���ͷ���
	}
	else
	{
		printf("����Ϊ��\n");
	}
	q->next = tmp;
	q->next->next = NULL;
	return q;
}



void print_process(ListNode *p)//���������Ľ�����Ϣ
{
	ListNode *tmp;
	//tmp=(ListNode*)malloc(sizeof(ListNode));
	if(p->next == NULL)
	{
		printf("����Ϊ��!\n");
		system("pause");
		exit(0);
	}
	else
	{
		tmp=p->next;
		while(tmp)
		{
			printf("����ID��%d		�������ƣ�%s	����ʱ�䣺%d	����ʱ�䣺%d	�ȴ�ʱ�䣺%d	���ʱ�䣺%d	��Ӧ�ȣ�%.1lf	\n"
				,tmp->Process_Id,tmp->Process_Name,tmp->Time_Arrive,tmp->Time_Serve,tmp->Time_wait,tmp->Time_Finish,tmp->Response);
			//getchar();
			tmp=tmp->next;
		}
	}
	
}



void time_peace_schedul(ListNode *p)  //ʱ��Ƭ����
{
	int i=0;
	ListNode *tmp,*tmp_min,*tmp_min_pre;  //tmp_min���浽��ʱ����С�Ľ���,tmp_min_preΪ��С���̵�ǰһ������ ѭ���Ĵ�
	tmp=p->next;
	
	while(i<PRO_NUM-1)//����ѭ���ҵ����̶����е���ʱ����С�Ľ��̣�ѹ���������
	{
		tmp_min_pre=p;//tmp_min_pre����ʼ��Ϊ����ͷ�ڵ�
		tmp_min=tmp;
		while(tmp->next) //���ѭ���ҵ���ǰ���е���ʱ����С�Ľ���
		{
			if(tmp_min->Time_Arrive > tmp->next->Time_Arrive)
			{
				tmp_min_pre=tmp;
				tmp_min=tmp->next;
				
			}
			tmp=tmp->next;
		}
		if(!tmp_min->next)//���ɾ�����Ƕ������һ��
			tmp_min_pre->next=NULL;
		else
			tmp_min_pre->next=tmp_min_pre->next->next;//�ӽ��̶�����ɾ���ý���

		ready_in(ready,tmp_min);//���������
		tmp=p->next;//�ӽ��̶��п�ʼ������ѭ��
		i++;
	}
	tmp=p->next;//ʣ���һ������ֱ�������
	ready_in(ready,tmp);
	
}