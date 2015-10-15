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
CPU_STK        Task3Stk[TASK_STK_SIZE];
CPU_STK        Task4Stk[TASK_STK_SIZE];
CPU_STK        Task5Stk[TASK_STK_SIZE];
CPU_STK        TaskStartStk[TASK_STK_SIZE];

OS_TCB 	       TaskStartTCB;                                 /* Tasks TCBs                                    */
OS_TCB         Task1TCB, Task2TCB, Task3TCB, Task4TCB, Task5TCB;



/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/


static  void  TaskStart(void *p_arg);                        /* Function prototypes of Startup task           */
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

void  main(void)
{
	OS_ERR  err;

	OSInit((OS_ERR *)&err);                                /* Initialize uC/OS-III                      */
	BSP_Init();                                                 /* Initialize BSP functions                             */
	CPU_Init();                                                 /* Initialize uC/CPU services                           */


	
	
	
	//closegraph();

	OSTaskCreate((OS_TCB     *)&TaskStartTCB,              /* Create the App Start Task.                */
		(CPU_CHAR   *)"TaskStart",
		(OS_TASK_PTR)TaskStart,
		(void       *)0,
		(OS_PRIO)5,
		(CPU_STK    *)&TaskStartStk[0],
		(CPU_STK_SIZE)TASK_STK_SIZE / 10,
		(CPU_STK_SIZE)TASK_STK_SIZE,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void       *)0,
		(OS_OPT)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err);

	OSStart((OS_ERR *)&err);                               /* Start multitasking                        */


		
		return ;
	

}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/

void  TaskStart(void *p_arg)
{
	OS_ERR      err;
	CPU_INT16S  key;


	p_arg = p_arg;                                         /* Prevent compiler warning                 */
	
#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif




	OSTaskCreate((OS_TCB     *)&Task1TCB,              /* Create the App Start Task.                */
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

	OSTaskCreate((OS_TCB     *)&Task2TCB,              /* Create the App Start Task.                */
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

	OSTaskCreate((OS_TCB     *)&Task3TCB,              /* Create the App Start Task.                */
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

	OSTaskCreate((OS_TCB     *)&Task4TCB,              /* Create the App Start Task.                */
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

	OSTaskCreate((OS_TCB     *)&Task5TCB,              /* Create the App Start Task.                */
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

	int current = 1;
	while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */
		OSTimeDlyHMSM(0, 0, 2, 0,
			OS_OPT_TIME_DLY,
			&err);
		switch (current)
		{
			case 1:OSTaskResume(&Task1TCB, &err); break;
			case 2:OSTaskResume(&Task2TCB, &err); break;
			case 3:OSTaskResume(&Task3TCB, &err); break;
			case 4:OSTaskResume(&Task4TCB, &err); break;
			case 5:OSTaskResume(&Task5TCB, &err); break;
		}
		current = current % 5 + 1;
		//APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet(&err)));
	}
}


/*
*********************************************************************************************************
*                                             TASKS
*********************************************************************************************************
*/




void  Task1(void *p_arg)
{
	OS_ERR    err;
	CPU_INT08U  y;

	p_arg = p_arg;


	
	y = 1;
	for (;;) {
		OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		/*PC_DispStr(0, 0, "0B702/2015H2: Task Management", 2);
		PC_DispStr(0, 1, "Edit BY Àî½ñêÍ 1501210936", 2);
		PC_DispStr(0, 1 + y, "Task1 is running ", 0);
		PC_DispStr(0, 2 + y, "Task2 is delaying", 0);*/
		initgraph(640, 480);
		setcolor(GREEN);
		line(100, 100, 500, 200);
		y = y + 6;
		OSTaskSuspend((OS_TCB *)0, &err);
	}
}

void  Task2(void *p_arg)
{
	OS_ERR    err;
	CPU_INT08U  y;

	p_arg = p_arg;

	


	y = 2;
	for (;;) {

		OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		//PC_DispStr(21, 1 + y, "Task1 is suspending", 1);
		//PC_DispStr(21, 2 + y, "Task2", 1);
		initgraph(640, 480);
		setcolor(RED);
		line(200, 100, 700, 200);
		y = y + 6;
		//OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		OSTaskSuspend((OS_TCB *)0, &err);
	}
}


void  Task3(void *p_arg)
{
	OS_ERR    err;
	CPU_INT08U  y;

	p_arg = p_arg;

	y = 4;
	for (;;) {

		OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		//PC_DispStr(31, 1 + y, "Task3", 1);
		//PC_DispStr(21, 2 + y, "Task3 is running   ", 1);

		y = y + 6;
		//OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		OSTaskSuspend((OS_TCB *)0, &err);
	}
}


void  Task4(void *p_arg)
{
	OS_ERR    err;
	CPU_INT08U  y;

	p_arg = p_arg;

	y = 5;
	for (;;) {

		OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		//PC_DispStr(41, 1 + y, "Task4", 1);
		//PC_DispStr(21, 2 + y, "Task2 is running   ", 1);

		y = y + 6;
		//OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		OSTaskSuspend((OS_TCB *)0, &err);
	}
}


void  Task5(void *p_arg)
{
	OS_ERR    err;
	CPU_INT08U  y;

	p_arg = p_arg;

	y = 6;
	for (;;) {

		OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		//PC_DispStr(51, 1 + y, "Task5", 1);
		//PC_DispStr(21, 2 + y, "Task2 is running   ", 1);

		y = y + 6;
		//OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_DLY, (OS_ERR  *)&err);
		OSTaskSuspend((OS_TCB *)0, &err);
		

	}
}