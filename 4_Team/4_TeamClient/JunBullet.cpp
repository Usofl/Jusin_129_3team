#include "stdafx.h"
#include "JunBullet.h"


CJunBullet::CJunBullet()
{
}


CJunBullet::~CJunBullet()
{
	Release();
}

void CJunBullet::Initialize(void)
{
	m_fSpeed = 0.f;
	vPoint[0] = { -20.f,-20.f,0.f };
	vPoint[1] = {  20.f, -20.f,0.f };
	vPoint[2] = {  20.f, 20.f,0.f };
	vPoint[3] = { -20.f, 20.f,0.f };
	vSu = { 1.f,0.f,0.f };
	m_fAngle = 0.f;
	m_fTempTime = 0.f;
	
	int i = 5;
}

const int CJunBullet::Update(void)
{
	vPoint[0] = { -20.f,-20.f,0.f };
	vPoint[1] = { 20.f, -20.f,0.f };
	vPoint[2] = { 20.f, 20.f,0.f };
	vPoint[3] = { -20.f, 20.f,0.f };
	
	m_fTempTime += 0.016f;
	Move();
	
	return 0;
}

void CJunBullet::Late_Update(void)
{

}

void CJunBullet::Render(HDC hDC)
{
	Ellipse(hDC, (int)m_tInfo.vPos.x - 10, (int)m_tInfo.vPos.y - 10, (int)m_tInfo.vPos.x + 10, (int)m_tInfo.vPos.y + 10);	
}

void CJunBullet::Release(void)
{

}

void CJunBullet::Move(void)
{
	
	/*	m_tInfo.vPos.x += iBulletDir * (m_fSpeed * cosf(m_fAngle) * m_fTempTime);
		m_tInfo.vPos.y -= (m_fSpeed * sinf(m_fAngle) * m_fTempTime) - (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
	*/

	m_tInfo.vPos += m_fSpeed* m_tInfo.vDir;
	//m_tInfo.vPos.x -= m_tInfo.vDir;
	m_tInfo.vPos.y += (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
}
