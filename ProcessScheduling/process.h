#pragma once

/*****************����ṹ������*****************/
#define PRO_NUM 5     //���̸���



 struct  PCB //����PCB���ݽṹ
{
	int Process_Id;
	char Process_Name[10];
	int Time_Arrive;
	int Time_Serve;
	int Time_wait;
	int Time_Finish;
	double Response;
	struct PCB *next;
};

typedef struct PCB ListNode;




