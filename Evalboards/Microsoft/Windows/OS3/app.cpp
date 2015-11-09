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
#define SHOW_CONSOLE
#include <graphics.h>
#include <math.h>
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
CPU_STK        Task3Stk[TASK_STK_SIZE];
CPU_STK        Task4Stk[TASK_STK_SIZE];
CPU_STK        Task5Stk[TASK_STK_SIZE];

CPU_INT32U line_end[5][4];
CPU_INT32U philisopher_pos[5][2];

OS_TCB         Task1TCB, Task2TCB, Task3TCB, Task4TCB, Task5TCB;                            /* Tasks TCBs                                    */
OS_SEM		   sem[5];
bool		   isClean[5];
/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/* Function prototypes of Startup task           */
static  void  Task1(void *p_arg);
static  void  Task2(void *p_arg);
static  void  Task3(void *p_arg);
static  void  Task4(void *p_arg);
static  void  Task5(void *p_arg);



/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

void initGraph()
{
	int x, y, x_c = 320, y_c = 240;
	int dis = 110;
	int radis = 20;
	int angle = 0;
	int delta = 360 / 5;
	char str[2];


	circle(320, 240, 150);
	for (int i = 0; i < 5; i++)
	{
		double s = sin(2 * PI  *angle / 360);
		double c = cos(2 * PI*angle / 360);
		angle += delta;
		x = x_c + dis*c;
		y = y_c + dis*s;
		philisopher_pos[i][0] = x_c + dis*c * 2;
		philisopher_pos[i][1] = y_c + dis*s * 2;

		str[0] = i + '1';
		str[1] = 0;
		outtextxy(x - 5, y - 10, str);
		circle(x, y, radis);
		delay_fps(1000 / 20);
	}

	angle = -35;
	for (int i = 0; i < 5; i++)
	{
		double s = sin(2 * PI  *angle / 360);
		double c = cos(2 * PI*angle / 360);
		angle += delta;
		line_end[i][0] = x_c + 0.8*dis*c;
		line_end[i][1] = y_c + 0.8*dis*s;
		line_end[i][2] = x_c + 1.1*dis*c;
		line_end[i][3] = y_c + 1.1*dis*s;
		line(line_end[i][0], line_end[i][1], line_end[i][2], line_end[i][3]);
		str[0] = i + '1';
		str[1] = 0;
		outtextxy(x_c + 1.2*dis*c, y_c + 1.2*dis*s, str);

		delay_fps(1000 / 20);
	}
}



void  main(void)
{
	OS_ERR  err;

	OSInit((OS_ERR *)&err);                                /* Initialize uC/OS-III                      */
	BSP_Init();                                            /* Initialize BSP functions                             */
	CPU_Init();                                            /* Initialize uC/CPU services                           */

	initgraph(640, 480);
	setcaption("1501210936 李今晖 第三次实验 哲学家就餐问题");

	OSSemCreate(&sem[0], "sem0", 1, &err);
	OSSemCreate(&sem[1], "sem1", 1, &err);
	OSSemCreate(&sem[2], "sem2", 1, &err);
	OSSemCreate(&sem[3], "sem3", 1, &err);
	OSSemCreate(&sem[4], "sem4", 1, &err);
	srand((int)OSTimeGet(&err));

	initGraph();




	delay_fps(1000 / 20);

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

	OSTaskCreate((OS_TCB     *)&Task3TCB,				   /* Create the App Start Task.                */
		(CPU_CHAR   *)"Task3",
		(OS_TASK_PTR)Task3,
		(void       *)0,
		(OS_PRIO)4,
		(CPU_STK    *)&Task3Stk[0],
		(CPU_STK_SIZE)0,
		(CPU_STK_SIZE)TASK_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void       *)0,
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err);

	OSTaskCreate((OS_TCB     *)&Task4TCB,				   /* Create the App Start Task.                */
		(CPU_CHAR   *)"Task4",
		(OS_TASK_PTR)Task4,
		(void       *)0,
		(OS_PRIO)4,
		(CPU_STK    *)&Task4Stk[0],
		(CPU_STK_SIZE)0,
		(CPU_STK_SIZE)TASK_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void       *)0,
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err);

	OSTaskCreate((OS_TCB     *)&Task5TCB,				   /* Create the App Start Task.                */
		(CPU_CHAR   *)"Task5",
		(OS_TASK_PTR)Task5,
		(void       *)0,
		(OS_PRIO)4,
		(CPU_STK    *)&Task5Stk[0],
		(CPU_STK_SIZE)0,
		(CPU_STK_SIZE)TASK_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void       *)0,
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err);


	OSStart((OS_ERR *)&err);                               /* Start multitasking                        */

	return;
}

/*
*********************************************************************************************************
*                                             Common Function
*********************************************************************************************************
*/

CPU_INT32U timeout = 2000;
OS_ERR tryGetSem(int semno)
{
	semno = semno % 5;
	CPU_TS ts;
	OS_ERR err;
	do
	{
		OSSemPend(&sem[semno], timeout, OS_OPT_PEND_BLOCKING, &ts, &err);
	} while (err != OS_ERR_NONE);
	return err;
}

OS_ERR tryPostSem(int semno)
{
	semno = semno % 5;
	CPU_TS ts;
	OS_ERR err;
	OSSemPost(&sem[semno], OS_OPT_PEND_BLOCKING, &err);
	return err;
}

void thinking(OS_ERR* err)
{
	/*char buffer[20];
	sprintf(buffer, "%s is thinking", OSTCBCurPtr->NamePtr);
	printf("%s\n", buffer);
	CPU_INT32U thinkingTime = rand() % 5;
	OSTimeDlyHMSM(0, 0, thinkingTime,0, OS_OPT_TIME_DLY, (OS_ERR  *)err);*/
}


void eating(OS_ERR* err)
{
	char buffer[20];
	int index = OSTCBCurPtr->NamePtr[4] - '1';
	setcolor(GREEN);
	circle(philisopher_pos[index][0], philisopher_pos[index][1], 30);
	delay_fps(1000 / 20);

	sprintf(buffer, "%s is eating", OSTCBCurPtr->NamePtr);
	printf("%s\n", buffer);
	CPU_INT32U eatingTime = rand() % 5 + 3;
	OSTimeDlyHMSM(0, 0, eatingTime, 0, OS_OPT_TIME_DLY, (OS_ERR  *)err);


	setcolor(BLACK);
	circle(philisopher_pos[index][0], philisopher_pos[index][1], 30);
	delay_fps(1000 / 20);
}

void getTwoForks(int left, int right)
{
	OS_ERR    err;
	char buffer[40];
	err = tryGetSem(left);
	if (err != OS_ERR_NONE)
	{
		fprintf(stderr, "Get Sem Failed");
	}
	setcolor(BLACK);
	sprintf(buffer, "%s gets %d fork", OSTCBCurPtr->NamePtr, left);
	printf("%s\n", buffer);
	line(line_end[left][0], line_end[left][1], line_end[left][2], line_end[left][3]);
	delay_fps(1000 / 50);

	//OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)err);
	err = tryGetSem(right);
	if (err != OS_ERR_NONE)
	{
		fprintf(stderr, "Get Sem Failed");
	}
	sprintf(buffer, "%s gets %d fork", OSTCBCurPtr->NamePtr, right);
	printf("%s\n", buffer);

	setcolor(BLACK);
	line(line_end[right][0], line_end[right][1], line_end[right][2], line_end[right][3]);
	delay_fps(1000 / 50);


}

void giveUpTwoForks(int left, int right)
{
	OS_ERR    err;

	setcolor(WHITE);
	line(line_end[left][0], line_end[left][1], line_end[left][2], line_end[left][3]);
	delay_fps(1000 / 50);

	err = tryPostSem(left);
	if (err != OS_ERR_NONE)
	{
		fprintf(stderr, "POST Sem Failed\n");
	}

	setcolor(WHITE);
	line(line_end[right][0], line_end[right][1], line_end[right][2], line_end[right][3]);
	delay_fps(1000 / 50);

	err = tryPostSem(right);
	if (err != OS_ERR_NONE)
	{
		fprintf(stderr, "POST Sem Failed\n");
	}



}




/*
*********************************************************************************************************
*                                             TASKS
*********************************************************************************************************
*/


void  Task1(void *p_arg)
{
	p_arg = p_arg;
	OS_ERR    err;
	CPU_TS	ts;
	int left = 0;
	int right = (left + 1) % 5;
	for (;;) {
		thinking(&err);
		getTwoForks(left, right);
		eating(&err);
		giveUpTwoForks(left, right);
	}
}

void  Task2(void *p_arg)
{
	p_arg = p_arg;
	OS_ERR    err;
	CPU_TS	ts;
	int left = 1;
	int right = (left + 1) % 5;
	for (;;) {
		thinking(&err);
		getTwoForks(left, right);
		eating(&err);
		giveUpTwoForks(left, right);
	}
}

void  Task3(void *p_arg)
{
	p_arg = p_arg;
	OS_ERR    err;
	CPU_TS	ts;
	int left = 2;
	int right = (left + 1) % 5;
	for (;;) {
		thinking(&err);
		getTwoForks(left, right);
		eating(&err);
		giveUpTwoForks(left, right);
	}
}

void  Task4(void *p_arg)
{
	p_arg = p_arg;
	OS_ERR    err;
	CPU_TS	ts;
	int left = 3;
	int right = (left + 1) % 5;
	for (;;) {
		thinking(&err);
		getTwoForks(left, right);
		eating(&err);
		giveUpTwoForks(left, right);
	}
}

void  Task5(void *p_arg)
{
	p_arg = p_arg;
	OS_ERR    err;
	CPU_TS	ts;
	int left = 4;
	int right = (left + 1) % 5;
	for (;;) {
		thinking(&err);
		getTwoForks(right, left);
		eating(&err);
		giveUpTwoForks(right, left);
	}
}

