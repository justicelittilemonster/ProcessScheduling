#pragma once

/*****************定义结构体类型*****************/
#define PRO_NUM 5     //进程个数



 struct  PCB //定义PCB数据结构
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




