#include "stdafx.h"
#include "ScrollMgr.h"
#include "Obj.h"

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

void CScrollMgr::Scroll_Lock_Fortress(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (WINCX - 3000 > m_fScrollX)
		m_fScrollX = WINCX - 3000;

	if (WINCY - 768 > m_fScrollY)
		m_fScrollY = WINCY - 768;
}

const bool CScrollMgr::Fix_Cheak(const CObj* _pTarget)
{
	//int		iOffSetX = WINCX >> 1;
	//int		iOffSetY = WINCY >> 1;

	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//INFO	tTarget_Info = _pTarget->Get_Info();

	//int		iItvX = 200;
	//int		iItvY = 50;

	//if ((iOffSetX + iItvX < tTarget_Info.vPos.x + iScrollX) || (iOffSetX - iItvX > tTarget_Info.vPos.x + iScrollX)
	//	|| (iOffSetY - iItvY > tTarget_Info.vPos.y + iScrollY) || (iOffSetY + iItvY < tTarget_Info.vPos.y + iScrollY))
	//{
	//	return false;
	//}

	//return true;

	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	INFO	tTarget_Info = _pTarget->Get_Info();

	int		iItvX = 100;
	int		iItvY = 50;

	if (iOffSetX + iItvX < tTarget_Info.vPos.x + iScrollX)
	{
		return false;
	}

	if (iOffSetX - iItvX > tTarget_Info.vPos.x + iScrollX)
	{
		return false;
	}

	if (iOffSetY - iItvY > tTarget_Info.vPos.y + iScrollY)
	{
		return false;
	}
	
	return true;
}
