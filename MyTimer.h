// MyTimer.h: interface for the CMyTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTIMER_H__73C128D4_0852_44C4_BB92_569A5BA8681B__INCLUDED_)
#define AFX_MYTIMER_H__73C128D4_0852_44C4_BB92_569A5BA8681B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786)

#include <windows.h>
#include <map>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

typedef void(*pMyTimerProc)(int id, DWORD dwUser);

class CMyTimer  
{
private:
	int m_nId; //Timer Id
	pMyTimerProc m_pCusTimerProc; //Timer特定回调函数

	static pMyTimerProc m_pTimerProc; //Timer通用回调函数

	static bool m_bInitCS; //临界区是否初始化
	static CRITICAL_SECTION m_csMT; //Timer map临界区
	static map<int, CMyTimer*> m_mapTimers; //Timer map
private:
	//内部Timer回调函数
	static void CALLBACK TimeProc( 
					   UINT uID,       
					   UINT uMsg,     
					   DWORD dwUser,   
					   DWORD dw1,     
					   DWORD dw2       
					   );
public:
	CMyTimer();
	virtual ~CMyTimer();

	//设置Timer的通用回调函数
	static void SetTimerCallback(pMyTimerProc pProc = NULL) {m_pTimerProc = pProc;}

	//启动Timer
	static void SetTimer(int id, int nMillSec, DWORD dwUser = 0, pMyTimerProc pProc = NULL);

	//关闭Timer
	static void KillTimer(int id);
};

#endif // !defined(AFX_MYTIMER_H__73C128D4_0852_44C4_BB92_569A5BA8681B__INCLUDED_)
