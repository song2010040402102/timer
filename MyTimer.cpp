// MyTimer.cpp: implementation of the CMyTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyTimer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

pMyTimerProc CMyTimer::m_pTimerProc = NULL;
bool CMyTimer::m_bInitCS = false;
CRITICAL_SECTION CMyTimer::m_csMT;
map<int, CMyTimer*> CMyTimer::m_mapTimers;

CMyTimer::CMyTimer()
{
	m_nId = 0;
	m_pCusTimerProc = NULL;
}

CMyTimer::~CMyTimer()
{
	
}

void CALLBACK CMyTimer::TimeProc( 
					   UINT uID,       
					   UINT uMsg,     
					   DWORD dwUser,   
					   DWORD dw1,     
					   DWORD dw2       
					   ) 
{ 
	if(!m_bInitCS)
	{
		::InitializeCriticalSection(&m_csMT);
		m_bInitCS = true;
	}

	CMyTimer *pTimer = NULL;

	::EnterCriticalSection(&m_csMT);
	map<int, CMyTimer*>::iterator iter = m_mapTimers.find(uID);
	if(iter != m_mapTimers.end())
		pTimer = iter->second;
	::LeaveCriticalSection(&m_csMT);

	if(pTimer)
	{
		if(pTimer->m_pCusTimerProc)
			pTimer->m_pCusTimerProc(pTimer->m_nId, dwUser);
		else if(m_pTimerProc)
			m_pTimerProc(pTimer->m_nId, dwUser);
	}		
} 

void CMyTimer::SetTimer(int id, int nMillSec, DWORD dwUser, pMyTimerProc pProc)
{
	if(nMillSec <= 0 || (!pProc && !m_pTimerProc))
		return;

	KillTimer(id);

	CMyTimer *pTimer = new CMyTimer();
	if(!pTimer)
		return;

	pTimer->m_nId = id;
	pTimer->m_pCusTimerProc = pProc;
	int nId = ::timeSetEvent(nMillSec, id, TimeProc, dwUser, (UINT)TIME_PERIODIC); 

	if(!m_bInitCS)
	{
		::InitializeCriticalSection(&m_csMT);
		m_bInitCS = true;
	}
	::EnterCriticalSection(&m_csMT);
	m_mapTimers[nId] = pTimer;
	::LeaveCriticalSection(&m_csMT);
}

void CMyTimer::KillTimer(int id)
{
	int nId = 0;

	if(!m_bInitCS)
	{
		::InitializeCriticalSection(&m_csMT);
		m_bInitCS = true;
	}	
	::EnterCriticalSection(&m_csMT);
	for(map<int, CMyTimer*>::iterator iter = m_mapTimers.begin(); iter != m_mapTimers.end(); iter++)
	{
		CMyTimer *pTimer = iter->second;
		if(pTimer && pTimer->m_nId == id)		
		{
			nId = iter->first;
			delete pTimer, pTimer = NULL;
			m_mapTimers.erase(iter);
			break;
		}
	}
	::LeaveCriticalSection(&m_csMT);

	if(nId != 0)
		timeKillEvent(nId);
}
