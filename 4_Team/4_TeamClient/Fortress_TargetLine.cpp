#include "stdafx.h"
#include "Fortress_TargetLine.h"
#include "ScrollMgr.h"

CFortress_TargetLine::CFortress_TargetLine():m_bRender(false)
{
	ZeroMemory(vRenderArray, sizeof(vRenderArray));
	Initialize();
}


CFortress_TargetLine::~CFortress_TargetLine()
{
	Release();
}

void CFortress_TargetLine::Initialize(void)
{
	m_eRender = RENDER_TARGETLINE;
}

const int CFortress_TargetLine::Update(void)
{
	return 0;
}

void CFortress_TargetLine::Late_Update(void)
{
}

void CFortress_TargetLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	
	for (int i = 0; 30 > i; ++i)
	{
		Ellipse(hDC, vRenderArray[i].x + iScrollX - 5, vRenderArray[i].y + iScrollY - 5, vRenderArray[i].x + iScrollX + 5, vRenderArray[i].y + iScrollY + 5);
	}

}

void CFortress_TargetLine::Release(void)
{
}
