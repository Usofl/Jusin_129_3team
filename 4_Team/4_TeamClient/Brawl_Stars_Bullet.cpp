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
	m_tInfo.vPos = { 100.f ,100, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_tInfo_Bullet_Local[0].vPos = { -10.f , -10.f , 0.f };
	m_tInfo_Bullet_Local[1].vPos = { +10.f , -10.f , 0.f };
	m_tInfo_Bullet_Local[2].vPos = { +10.f , +10.f , 0.f };
	m_tInfo_Bullet_Local[3].vPos = { -10.f , +10.f , 0.f };

	m_fSpeed = 20.f;

	m_bDead = false;
}

const int CBrawl_Stars_Bullet::Update(void)
{
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}

	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matScale * m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_tInfo_Bullet_World[i].vPos, &m_tInfo_Bullet_Local[i].vPos, &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);


	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;


	return 0;
}

void CBrawl_Stars_Bullet::Late_Update(void)
{
	/*for (int i = 0; i < 4; ++i)
	{
		if (WINCX < m_tInfo_Bullet_World[i].vPos.x || WINCX < m_tInfo_Bullet_World[i].vPos.y)
		{
			m_bDead = true;
		}
	}*/

	if (WINCX <= m_tInfo.vPos.x || WINCY <= m_tInfo.vPos.y || 0 > m_tInfo.vPos.x || 0 > m_tInfo.vPos.y	)
	{
		m_bDead = true;
	}
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
