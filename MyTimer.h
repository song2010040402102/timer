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
	pMyTimerProc m_pCusTimerProc; //Timer�ض��ص�����

	static pMyTimerProc m_pTimerProc; //Timerͨ�ûص�����

	static bool m_bInitCS; //�ٽ����Ƿ��ʼ��
	static CRITICAL_SECTION m_csMT; //Timer map�ٽ���
	static map<int, CMyTimer*> m_mapTimers; //Timer map
private:
	//�ڲ�Timer�ص�����
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

	//����Timer��ͨ�ûص�����
	static void SetTimerCallback(pMyTimerProc pProc = NULL) {m_pTimerProc = pProc;}

	//����Timer
	static void SetTimer(int id, int nMillSec, DWORD dwUser = 0, pMyTimerProc pProc = NULL);

	//�ر�Timer
	static void KillTimer(int id);
};

#endif // !defined(AFX_MYTIMER_H__73C128D4_0852_44C4_BB92_569A5BA8681B__INCLUDED_)
