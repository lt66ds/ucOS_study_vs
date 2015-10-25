/*
************************************************************************************************************************
*                                                      uC/OS-III
*                                                 The Real-Time Kernel
*
*                                  (c) Copyright 2009-2011; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*
* File    : Taskm.c
* By      : 0B702
************************************************************************************************************************
*/
extern "C"
{
#include <includes.h>
}
//#define SHOW_CONSOLE
#include <graphics.h>
/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/
#define  TASK_STK_SIZE                 128       /* Size of each task's stacks (# of WORDs)            */
#define  APP_TYPE_EN                    1u       /* Enable (1) or Disable (0) for App Type             */


/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/


CPU_STK        Task1Stk[TASK_STK_SIZE];        /* Tasks stacks                                  */
CPU_STK        Task2Stk[TASK_STK_SIZE];


OS_TCB         Task1TCB, Task2TCB;                                 /* Tasks TCBs                                    */


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/* Function prototypes of Startup task           */
static  void  Task1(void *p_arg);
static  void  Task2(void *p_arg);



/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

void  main(void)
{
	OS_ERR  err;

	OSInit((OS_ERR *)&err);                                /* Initialize uC/OS-III                      */
	BSP_Init();                                            /* Initialize BSP functions                             */
	CPU_Init();                                            /* Initialize uC/CPU services                           */
	
	initgraph(640, 480);
	setcaption("1501210936 李今晖 第二次实验");
//#if OS_CFG_STAT_TASK_EN > 0u
//	OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
//#endif
	OSTaskCreate((OS_TCB     *)&Task1TCB,				   /* Create the App Start Task.                */
		(CPU_CHAR   *)"Task1",
		(OS_TASK_PTR)Task1,
		(void       *)0,
		(OS_PRIO)2,
		(CPU_STK    *)&Task1Stk[0],
		(CPU_STK_SIZE)0,
		(CPU_STK_SIZE)TASK_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void       *)0,
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err);

	OSTaskCreate((OS_TCB     *)&Task2TCB,				   /* Create the App Start Task.                */
		(CPU_CHAR   *)"Task2",
		(OS_TASK_PTR)Task2,
		(void       *)0,
		(OS_PRIO)4,
		(CPU_STK    *)&Task2Stk[0],
		(CPU_STK_SIZE)0,
		(CPU_STK_SIZE)TASK_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void       *)0,
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err);

	OSStart((OS_ERR *)&err);                               /* Start multitasking                        */

		return ;
}



/*
*********************************************************************************************************
*                                             TASKS
*********************************************************************************************************
*/


/*PC_DispStr(0, 0, "0B702/2015H2: Task Management", 2);
PC_DispStr(0, 1, "Edit BY 李今晖 1501210936", 2);
PC_DispStr(0, 1 + y, "Task1 is running ", 0);
PC_DispStr(0, 2 + y, "Task2 is delaying", 0);*/

void  Task1(void *p_arg)
{
	OS_ERR    err;
	CPU_INT16U  y;
	CPU_TS	ts;
	OS_MSG_SIZE msgSize;
	CPU_INT32U delayTime;
	char buffer[20];
	p_arg = p_arg;
	y = 0;
	
	srand((int)OSTimeGet(&err));
	for (;;) {
		delay_fps(20);
		//delayTime = (CPU_INT32U)(rand() % 3000000);
		delayTime = (CPU_INT32U)(rand() % 3);
		sprintf(buffer, "T1延时了%d秒\n", delayTime);
		OSTimeDlyHMSM(0, 0, delayTime, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		
		setcolor(GREEN);
		outtextxy(0, y, buffer);
		y = y + 20;
		OSTaskSemPost(&Task2TCB, OS_OPT_POST_NONE, &err);
		void* msgPtr=OSTaskQPend((OS_TICK)0, OS_OPT_PEND_BLOCKING, &msgSize, &ts, &err);
		sprintf(buffer, "T1接收到T2发来的问候:%s\n", (char*)msgPtr);
		setcolor(GREEN);
		outtextxy(0, y, buffer);
		y = (y + 20)%480;
		
		printf("%d %d\n", 0, y);
		

	}
}

void  Task2(void *p_arg)
{
	OS_ERR    err;
	CPU_INT16U  y;
	CPU_INT32U randIndex;
	CPU_TS	ts;
	OS_MSG_SIZE msgSize=10;
	p_arg = p_arg;
	char buffer[][20] = { "hello", "你好", "Hola", "Bonjour", "Guten morgen", "こんにちは", "a niang ha sai you" };
	y = 0;
	for (;;) {
		
		delay_fps(20);
		OSTaskSemPend((OS_TICK)0, OS_OPT_PEND_BLOCKING, &ts, (OS_ERR  *)&err);
		setcolor(RED);
		outtextxy(300, y, "T2被T1通过信号量唤醒");
		y = (y + 20) % 480;
		OSTimeDlyHMSM(0, 0, 0, 400, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		randIndex=rand()%7;
		OSTaskQPost(&Task1TCB, (void*)&buffer[randIndex], msgSize, OS_OPT_POST_FIFO, (OS_ERR  *)&err);
		setcolor(RED);
		outtextxy(300, y, "T2发出问候");
		y = (y + 20) % 480;
		if (0 == y) cleardevice();
	}
}
