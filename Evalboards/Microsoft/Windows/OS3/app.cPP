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
	
	initgraph(800, 480);
	setbkcolor(WHITE);
	setfillcolor(WHITE);
	setfont(-30, 0, "微软雅黑");
	setcaption("1501210936 李今晖 第二次实验");
	outtextxy(220, 5, "信号量与消息队列实验 李今晖");
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
		(OS_PRIO)2,
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

void updateImg(PIMAGE& master, PIMAGE& slave, PIMAGE& cpu, int x1, int y1, int x2, int y2, int delta)
{
	putimage(x1, y1, master);
	putimage(x1 + delta, y1 + delta, cpu);
	putimage(x2, y2, slave);
}

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
	PIMAGE t1 = newimage();
	PIMAGE t2 = newimage();
	PIMAGE cpu = newimage();
	getimage(t1, ".//Task1.jpg");
	getimage(t2, ".//Task2.jpg");
	getimage(cpu, ".//cpu.jpg");
	
	
	srand((int)OSTimeGet(&err));
	for (;;) {
		
		updateImg(t1, t2, cpu, 20, 100, 380, 100, 70);
		delayTime = (CPU_INT32U)(rand() % 2000)+600;
		sprintf(buffer, "T1随机延时了%d毫秒    \n", delayTime);
		setcolor(GREEN);
		outtextxy(20, 50, buffer);
		delay_ms(delayTime);

		

		OSTaskSemPost(&Task2TCB, OS_OPT_POST_NONE, &err);
		updateImg(t1, t2, cpu, 20, 100, 380, 100, 70);
		outtextxy(20, 50, "T1通过信号量唤醒T2                                                              ");
		delay_ms(1000);

		outtextxy(20, 50, "T1等待消息队列                                                              ");
		delay_ms(1000);

		void* msgPtr=OSTaskQPend((OS_TICK)0, OS_OPT_PEND_BLOCKING, &msgSize, &ts, &err);
		updateImg(t1, t2, cpu, 20, 100, 380, 100, 70);
		sprintf(buffer, "T1通过MSGQ接收到T2发来的问候:%s                               \n", (char*)msgPtr);
		setcolor(GREEN);

		outtextxy(30, 380, buffer);
		delay_ms(1000);


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
	PIMAGE t1 = newimage();
	PIMAGE t2 = newimage();
	PIMAGE cpu = newimage();
	getimage(t1, ".//Task1.jpg");
	getimage(t2, ".//Task2.jpg");
	getimage(cpu, ".//cpu.jpg");
	

	for (;;) {
		
		

		OSTaskSemPend((OS_TICK)0, OS_OPT_PEND_BLOCKING, &ts, (OS_ERR  *)&err);
		updateImg(t2, t1, cpu, 380, 100, 20, 100, 80);
		setcolor(RED);
		outtextxy(380, 50, "T2被T1通过信号量唤醒");
		delay_ms(1000);

		OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		randIndex=rand()%7;
		outtextxy(380, 50, "T2发送随机问候消息至T1          ");
		delay_ms(1000);
		OSTaskQPost(&Task1TCB, (void*)&buffer[randIndex], msgSize, OS_OPT_POST_FIFO, (OS_ERR  *)&err);

		updateImg(t2, t1, cpu, 380, 100, 20, 100, 80);
		setcolor(RED);
		
		outtextxy(380, 50, "T2将等待信号量                 ");
		delay_ms(1000);
		
		
	}
}
