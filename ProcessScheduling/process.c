#include<stdio.h>
#include<stdlib.h>
#include"process.h"


ListNode *ready;             //就绪队列
ListNode *run;               //运行队列
ListNode *finish;			 //完成队列






int time_peace;

ListNode *initial_duilie(ListNode *p)//初始化队列
{
	p= (ListNode*)malloc(sizeof(ListNode));
	p->next = NULL;
	return p;
}

ListNode *set_pcb()                  //导入文件内的进程信息
{
	int i=0;
	ListNode *q,*r;
	ListNode *p;				 //定义进程队列
	FILE *fp;
	p=(ListNode*)malloc(sizeof(ListNode));
	
	p->next = NULL;
	r=p;
	fp=fopen("process.txt","r");//process.txt文件内包含进程信息
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


void create_time()  //创建时间片      BUG:当输入为一串字符串时会出现字符串长度行的提示，不影响正常使用。
{
	printf("请输入时间片的长度：");
	while(1)        //判断输入是否合法
	{
		if(scanf("%d",&time_peace) == 1) //通过scanf返回值判断输入是否为数字
		{
			if(time_peace <=0 || time_peace > 65535) //判断输入范围是否合法
			{
				printf("输入时间片错误！\n");
				continue;
			}
			else  //获得正确的输入
			{
				break;
			}
		}
		
		else	 //输入的是非数字
		{
			printf("请输入正确的时间片\n");
			getchar();           //getchar吸收回车
		}	               
	}
}



ListNode *ready_in(ListNode *ready,ListNode *q) //用尾插法将进程q压入就绪队列
{
	ListNode *tmp,*p;
	p= (ListNode*)malloc(sizeof(ListNode));
	tmp=(ListNode*)malloc(sizeof(ListNode));
	tmp=ready->next;
	
	p=(ListNode*)malloc(sizeof(ListNode));
	p=q->next;
	if(!tmp)//如果ready为NULL
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


ListNode *ready_out(ListNode *ready) //从就绪队列取出首进程
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
		//ready = NULL;//更新队列头结点
	}
	else
	{
		printf("进程为空\n");
	}
	q->next = tmp;
	q->next->next = NULL;
	return q;
}



void print_process(ListNode *p)//输出队列里的进程信息
{
	ListNode *tmp;
	//tmp=(ListNode*)malloc(sizeof(ListNode));
	if(p->next == NULL)
	{
		printf("队列为空!\n");
		system("pause");
		exit(0);
	}
	else
	{
		tmp=p->next;
		while(tmp)
		{
			printf("进程ID：%d		进程名称：%s	到达时间：%d	服务时间：%d	等待时间：%d	完成时间：%d	响应比：%.1lf	\n"
				,tmp->Process_Id,tmp->Process_Name,tmp->Time_Arrive,tmp->Time_Serve,tmp->Time_wait,tmp->Time_Finish,tmp->Response);
			//getchar();
			tmp=tmp->next;
		}
	}
	
}



void time_peace_schedul(ListNode *p)  //时间片调度
{
	int i=0;
	ListNode *tmp,*tmp_min,*tmp_min_pre;  //tmp_min保存到达时间最小的进程,tmp_min_pre为最小进程的前一个进程 循环四次
	tmp=p->next;
	
	while(i<PRO_NUM-1)//依次循环找到进程队列中到达时间最小的进程，压入就绪队列
	{
		tmp_min_pre=p;//tmp_min_pre都初始化为队列头节点
		tmp_min=tmp;
		while(tmp->next) //这个循环找到当前队列到达时间最小的进程
		{
			if(tmp_min->Time_Arrive > tmp->next->Time_Arrive)
			{
				tmp_min_pre=tmp;
				tmp_min=tmp->next;
				
			}
			tmp=tmp->next;
		}
		if(!tmp_min->next)//如果删除的是队列最后一个
			tmp_min_pre->next=NULL;
		else
			tmp_min_pre->next=tmp_min_pre->next->next;//从进程队列中删除该进程

		ready_in(ready,tmp_min);//入就绪队列
		tmp=p->next;//从进程队列开始处重新循环
		i++;
	}
	tmp=p->next;//剩最后一个进程直接入队列
	ready_in(ready,tmp);
	
}