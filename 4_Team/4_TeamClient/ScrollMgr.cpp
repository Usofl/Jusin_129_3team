#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f)
	, m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Main_Scroll_Lock(void)
{
	//if (0.f < m_fScrollX)
	//	m_fScrollX = 0.f;

	//if (0.f < m_fScrollY)
	//	m_fScrollY = 0.f;

	//if (WINCX - MAINTILECX * MAINTILEX > m_fScrollX)
	//	m_fScrollX = WINCX - MAINTILECX * MAINTILEX;

	//if (WINCY - MAINTILECY * MAINTILEY > m_fScrollY)
	//	m_fScrollY = WINCY - MAINTILECY * MAINTILEY;
}
