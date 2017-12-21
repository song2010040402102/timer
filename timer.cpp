// timer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "MyTimer.h"

#define TIMER_ID0 1000
#define TIMER_ID1 1001
#define TIMER_ID2 1002
#define TIMER_ID3 1003
#define TIMER_ID4 1004

void OnTimer(int id, DWORD dwUser)
{
	printf("[OnTimer] id: %d, dwUser: %d\n", id, dwUser);
}

void OnTimer1(int id, DWORD dwUser)
{
	printf("[OnTimer1] id: %d, dwUser: %d\n", id, dwUser);
}

void OnTimer2(int id, DWORD dwUser)
{
	printf("[OnTimer2] id: %d, dwUser: %d\n", id, dwUser);
}

int main()
{
	CMyTimer::SetTimerCallback(OnTimer);

	CMyTimer::SetTimer(TIMER_ID0, 500);
	CMyTimer::SetTimer(TIMER_ID1, 1000, 10);
	CMyTimer::SetTimer(TIMER_ID2, 2000, 20);

	CMyTimer::SetTimer(TIMER_ID3, 3000, 30, OnTimer1);
	CMyTimer::SetTimer(TIMER_ID4, 4000, 40, OnTimer2);	

	getch();
	CMyTimer::KillTimer(TIMER_ID0);
	getch();
	CMyTimer::KillTimer(TIMER_ID1);
	getch();
	CMyTimer::KillTimer(TIMER_ID2);
	getch();
	CMyTimer::KillTimer(TIMER_ID3);
	getch();
	CMyTimer::KillTimer(TIMER_ID4);
	getch();
	
	return 0;
} 
