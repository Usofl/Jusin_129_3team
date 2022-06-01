#include "stdafx.h"
#include "Brawl_Stars_Bullet.h"


CBrawl_Stars_Bullet::CBrawl_Stars_Bullet()
{
}


CBrawl_Stars_Bullet::~CBrawl_Stars_Bullet()
{
	Release();
}

void CBrawl_Stars_Bullet::Initialize(void)
{
	m_tInfo.vPos = { 400.f ,300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_tInfo_Bullet_Local[0].vPos = { -10.f , -10.f , 0.f };
	m_tInfo_Bullet_Local[1].vPos = { +10.f , -10.f , 0.f };
	m_tInfo_Bullet_Local[2].vPos = { +10.f , +10.f , 0.f };
	m_tInfo_Bullet_Local[3].vPos = { -10.f , +10.f , 0.f };

	m_fSpeed = 10.f;
}

const int CBrawl_Stars_Bullet::Update(void)
{
	D3DXMATRIX matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matTrans;

		D3DXVec3TransformCoord(&m_tInfo_Bullet_World[i].vPos, &m_tInfo_Bullet_Local[i].vPos, &m_tInfo.matWorld);

	}
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);

	for (int i = 0; i < 4; ++i)
	{
		m_tInfo_Bullet_World[i].vPos += m_tInfo.vDir * m_fSpeed;
	}

	return 0;
}

void CBrawl_Stars_Bullet::Late_Update(void)
{
}

void CBrawl_Stars_Bullet::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_tInfo_Bullet_World[0].vPos.x, (int)m_tInfo_Bullet_World[0].vPos.y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Bullet_World[i].vPos.x, (int)m_tInfo_Bullet_World[i].vPos.y);
	}
	LineTo(hDC, (int)m_tInfo_Bullet_World[0].vPos.x, (int)m_tInfo_Bullet_World[0].vPos.y);
}

void CBrawl_Stars_Bullet::Release(void)
{
}

void CBrawl_Stars_Bullet::Key_Input(void)
{
}
