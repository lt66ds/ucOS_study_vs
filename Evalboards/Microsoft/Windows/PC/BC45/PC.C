#include <PC.H>
#include <conio.h>
#include <windows.h>

void    PC_DispChar(CPU_INT08U x, CPU_INT08U y, CPU_INT08U c, CPU_INT08U color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | BACKGROUND_BLUE);
	SetConsoleCursorPosition(hStdOut, coord);
	printf("%c", c);
}




void    PC_DispClrCol(CPU_INT08U x, CPU_INT08U bgnd_color);
void    PC_DispClrRow(CPU_INT08U y, CPU_INT08U bgnd_color);
void    PC_DispClrScr(CPU_INT08U bgnd_color);
void    PC_DispStr(CPU_INT08U x, CPU_INT08U y, CPU_INT08U *s, CPU_INT08U color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	switch (color)
	{
		case 0:SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | BACKGROUND_BLUE); break;
		case 1:SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_INTENSITY); break;
		case 2:SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY); break;
	}
	SetConsoleCursorPosition(hStdOut, coord);
	printf("%s\n", s);
}

void    PC_DOSReturn(void);
void    PC_DOSSaveReturn(void);

void    PC_ElapsedInit(void);
void    PC_ElapsedStart(void);
CPU_INT16U  PC_ElapsedStop(void);

void    PC_GetDateTime(char *s);
CPU_BOOLEAN PC_GetKey(CPU_INT16S *c);

void    PC_SetTickRate(CPU_INT16U freq);

void   *PC_VectGet(CPU_INT08U vect);
void    PC_VectSet(CPU_INT08U vect, void(*isr)(void));