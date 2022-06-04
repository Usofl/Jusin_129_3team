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

}

void CFortress_HPBar::Release(void)
{
}
