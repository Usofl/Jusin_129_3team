#include "stdafx.h"
#include "Fortress_HPBar.h"


CFortress_HPBar::CFortress_HPBar()
{
}


CFortress_HPBar::~CFortress_HPBar()
{
	Release();
}

void CFortress_HPBar::Initialize(void)
{
	m_eRender = RENDER_UI;

	m_tInfo.vPos = { 100.f, 658.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_vHPPoint[0] = { 50.f, 638.f, 0.f };
	m_vHPPoint[1] = { 50.f, 678.f, 0.f };
	m_vHPPoint[2] = { 250.f, 678.f, 0.f };
	m_vHPPoint[3] = { 250.f, 638.f, 0.f };
}

const int CFortress_HPBar::Update(void)
{
	return OBJ_NOEVENT;
}

void CFortress_HPBar::Late_Update(void)
{
	
}

void CFortress_HPBar::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vHPPoint[0].vPos.x, (int)m_vHPPoint[0].vPos.y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vHPPoint[i].vPos.x, (int)m_vHPPoint[i].vPos.y);
	}
	LineTo(hDC, (int)m_vHPPoint[0].vPos.x, (int)m_vHPPoint[0].vPos.y);
}

void CFortress_HPBar::Release(void)
{
}
