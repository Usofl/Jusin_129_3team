#include "stdafx.h"
#include "Fortress_TargetLine.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
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

	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	OldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)MyPen);
	
	for (int i = 0; 200 > i; ++i)
	{
		float fAngle = 0.f;
		float fX = vRenderArray[i].x;
		float fY = vRenderArray[i].y;
		/*if (!LINEMGR->Collision_JunLine(fX, fY, fAngle))
			continue;*/
		Ellipse(hDC, (int)vRenderArray[i].x + iScrollX - 2, (int)vRenderArray[i].y + iScrollY - 2, (int)vRenderArray[i].x + iScrollX + 2, (int)vRenderArray[i].y + iScrollY + 2);
	}
	SelectObject(hDC, OldPen);
	DeleteObject(MyPen);
}

void CFortress_TargetLine::Release(void)
{
}
