#include "stdafx.h"
#include "JunBullet.h"


CJunBullet::CJunBullet()
{
}


CJunBullet::~CJunBullet()
{
}

void CJunBullet::Initialize(void)
{
}

const int CJunBullet::Update(void)
{
	return 0;
}

void CJunBullet::Late_Update(void)
{

}

void CJunBullet::Render(HDC hDC)
{
	Ellipse(hDC, (int)m_tInfo.vPos.x - 50, (int)m_tInfo.vPos.y - 50, (int)m_tInfo.vPos.x + 50, (int)m_tInfo.vPos.x + 50);
}

void CJunBullet::Release(void)
{

}
