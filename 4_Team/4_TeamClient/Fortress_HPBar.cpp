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
}

const int CFortress_HPBar::Update(void)
{
	return 0;
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
